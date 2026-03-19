mod types;
mod lifter;
mod optimizer;
mod entry_hunter;
mod resolver;
mod codegen;
mod signatures;
mod structurer;

use crate::entry_hunter::*;
use crate::lifter::*;
use crate::optimizer::*;
use crate::resolver::*;
use crate::codegen::*;
use crate::types::*;

use dashmap::DashMap;
use fnv::{FnvHashMap, FnvHashSet};
use memmap2::Mmap;
use object::{File, Object, ObjectSection, SectionKind};
use rayon::prelude::*;
use std::collections::BTreeMap;
use std::fs::File as StdFile;
use std::sync::atomic::{AtomicUsize, Ordering};

const CHUNK_SIZE: usize = 16 * 1024;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: deepbleed <path_to_pe_file> [--output <base_name>]");
        std::process::exit(1);
    }

    let path = &args[1];
    println!("╔══════════════════════════════════════════════════════╗");
    println!("║  DEEP_BLEED v0.5.0 — Aggressive Decompilation Engine ║");
    println!("║  Mode: IR + SSA + DCE + ConstProp + Strings + C Gen  ║");
    println!("║  Output: .ir.json + .decompiled.c                    ║");
    println!("╚══════════════════════════════════════════════════════╝");
    println!();

    let file = StdFile::open(path)?;
    let mmap = unsafe { Mmap::map(&file)? };
    let obj = File::parse(&*mmap)?;

    let (machine_mode, stack_width) = match obj.architecture() {
        object::Architecture::X86_64 => (zydis::MachineMode::LONG_64, zydis::StackWidth::_64),
        object::Architecture::I386 => (zydis::MachineMode::LEGACY_32, zydis::StackWidth::_32),
        _ => return Err("Unsupported arch. x86/x64 only.".into()),
    };

    let arch_str = format!("{:?}", obj.architecture());
    println!("[+] Architecture: {}", arch_str);

    // ━━━ PHASE 0: Resolve ALL data (strings, imports, exports) ━━━
    println!("\n[*] PHASE 0: Extracting strings, imports, exports...");
    let resolved = build_resolved_data(&mmap, &obj);

    // ━━━ Build external library signatures ━━━
    let external_names = build_external_set(&obj);
    println!("[+] Known external symbol patterns: {}", external_names.len());

    // ━━━ Find executable sections ━━━
    let exec_sections: Vec<_> = obj.sections()
        .filter(|s| s.kind() == SectionKind::Text)
        .collect();

    let mut text_base: u64 = 0;
    let mut text_offset: usize = 0;
    let mut text_size: usize = 0;

    let mut code_chunks = Vec::new();
    for sec in &exec_sections {
        let sec_data = sec.data()?;
        let sec_addr = sec.address();
        let sec_name = sec.name().unwrap_or("?");
        let file_offset = sec.file_range().unwrap_or((0, 0)).0 as usize;

        if sec_name == ".text" || text_base == 0 {
            text_base = sec_addr;
            text_offset = file_offset;
            text_size = sec_data.len();
        }

        let mut pos = 0;
        while pos < sec_data.len() {
            let chunk_len = (sec_data.len() - pos).min(CHUNK_SIZE);
            code_chunks.push(CodeChunk {
                name: format!("{}:chunk_{:0X}", sec_name, pos),
                address: sec_addr + pos as u64,
                offset: file_offset + pos,
                size: chunk_len,
            });
            pos += chunk_len;
        }
    }

    println!("[*] Code chunks: {}", code_chunks.len());

    // ━━━ PHASE 1: Parallel CFG analysis ━━━
    println!("\n[*] PHASE 1: Parallel CFG Analysis...");
    let total_inst = AtomicUsize::new(0);
    let leaders_map: DashMap<u64, (), fnv::FnvBuildHasher> = DashMap::with_hasher(Default::default());
    let call_targets_map: DashMap<u64, u32, fnv::FnvBuildHasher> = DashMap::with_hasher(Default::default());
    let control_flow_map: DashMap<u64, ControlFlowInfo, fnv::FnvBuildHasher> = DashMap::with_hasher(Default::default());

    code_chunks.par_iter().for_each(|chunk| {
        let end = chunk.offset + chunk.size;
        if let Some(raw_code) = mmap.get(chunk.offset..end) {
            let result = analyze_chunk(raw_code, chunk.address, machine_mode, stack_width);
            total_inst.fetch_add(result.instructions, Ordering::Relaxed);
            for leader in result.leaders { leaders_map.insert(leader, ()); }
            for target in result.call_targets {
                call_targets_map.entry(target).and_modify(|c| *c += 1).or_insert(1);
            }
            for cf in result.control_flow { control_flow_map.insert(cf.addr, cf); }
        }
    });

    println!("[!] CFG: {} instructions scanned", total_inst.load(Ordering::SeqCst));

    // ━━━ PHASE 2: Entry Point & main() ━━━
    println!("\n[*] PHASE 2: Entry Point Hunting...");
    let entry_info = find_entry_and_main(
        &obj, &mmap, machine_mode, stack_width,
        text_base, text_offset, text_size,
    );

    // ━━━ PHASE 3: Function discovery ━━━
    println!("\n[*] PHASE 3: Function Discovery...");
    let unique_leaders: FnvHashSet<u64> = leaders_map.iter().map(|e| *e.key()).collect();
    let call_targets_fnv: FnvHashMap<u64, u32> = call_targets_map.iter()
        .map(|e| (*e.key(), *e.value())).collect();

    let mut functions = discover_functions(
        &call_targets_fnv, &entry_info, &external_names, &unique_leaders,
    );

    // Rename functions using exports
    for func in &mut functions {
        if let Some(export_name) = resolved.exports.get(&func.address) {
            func.name = export_name.clone();
        }
    }

    let user_funcs = functions.iter().filter(|f| f.kind != FunctionKind::ExternalLib).count();
    let ext_funcs = functions.iter().filter(|f| f.kind == FunctionKind::ExternalLib).count();
    println!("[+] Functions: {} (USER: {}, EXTERNAL_LIB: {})", functions.len(), user_funcs, ext_funcs);

    // ━━━ PHASE 4: Parallel IR Lifting + Optimization ━━━
    println!("\n[*] PHASE 4: Parallel IR Lifting + Optimization...");
    let global_dce = AtomicUsize::new(0);
    let global_constprop = AtomicUsize::new(0);
    let global_nops = AtomicUsize::new(0);
    let global_ir_insns = AtomicUsize::new(0);
    let global_blocks = AtomicUsize::new(0);

    let user_functions: Vec<&FunctionInfo> = functions.iter()
        .filter(|f| f.kind != FunctionKind::ExternalLib)
        .collect();

    let json_functions: Vec<JsonFunction> = user_functions.par_iter().map(|func| {
        let mut json_blocks = Vec::new();
        let mut cfg_links = Vec::new();
        let mut all_ssa_vars = Vec::new();

        for &block_addr in &func.block_addrs {
            for chunk in &code_chunks {
                if block_addr >= chunk.address && block_addr < chunk.address + chunk.size as u64 {
                    let end = chunk.offset + chunk.size;
                    if let Some(raw_code) = mmap.get(chunk.offset..end) {
                        let block_lifter = BlockLifter::new(machine_mode, stack_width, chunk.address);
                        let mut block = block_lifter.lift_basic_block(raw_code, block_addr);

                        let (ssa_vars, stats) = optimize_block(&mut block);
                        all_ssa_vars.extend(ssa_vars);

                        global_dce.fetch_add(stats.dce_eliminated, Ordering::Relaxed);
                        global_constprop.fetch_add(stats.constants_propagated, Ordering::Relaxed);
                        global_nops.fetch_add(stats.nops_removed, Ordering::Relaxed);
                        global_ir_insns.fetch_add(block.ir_instructions.len(), Ordering::Relaxed);
                        global_blocks.fetch_add(1, Ordering::Relaxed);

                        let block_id = format!("bb_{:X}", block.start_addr);
                        for edge in &block.edges {
                            let edge_type = if block.ir_instructions.iter().any(|i| matches!(i, IRInsn::Call { .. })) {
                                "call"
                            } else if block.ir_instructions.iter().any(|i| matches!(i, IRInsn::CondJump { .. })) {
                                "branch"
                            } else { "fallthrough" };
                            cfg_links.push(CfgEdge {
                                from: block_id.clone(),
                                to: format!("bb_{:X}", edge),
                                edge_type: edge_type.to_string(),
                            });
                        }

                        let json_insns: Vec<JsonInstruction> = block.ir_instructions.iter()
                            .filter(|i| !matches!(i, IRInsn::Label { .. }))
                            .map(|i| ir_to_json_instruction(i, block.start_addr, &resolved))
                            .collect();

                        json_blocks.push(JsonBlock {
                            id: block_id,
                            address: format!("0x{:X}", block.start_addr),
                            instructions: json_insns,
                        });
                    }
                    break;
                }
            }
        }

        let mut seen_ssa: FnvHashSet<String> = FnvHashSet::default();
        all_ssa_vars.retain(|v| seen_ssa.insert(v.name.clone()));

        JsonFunction {
            address: format!("0x{:X}", func.address),
            name: func.name.clone(),
            kind: format!("{}", func.kind),
            blocks: json_blocks,
            cfg_links,
            ssa_vars: all_ssa_vars,
        }
    }).collect();

    // ━━━ Build JSON ━━━
    let file_name = std::path::Path::new(path).file_name()
        .unwrap_or_default().to_string_lossy().to_string();

    // Build resolution tables for JSON
    let imports_table: BTreeMap<String, String> = resolved.imports.iter()
        .map(|(k, v)| (format!("0x{:X}", k), v.clone())).collect();
    let exports_table: BTreeMap<String, String> = resolved.exports.iter()
        .map(|(k, v)| (format!("0x{:X}", k), v.clone())).collect();
    let strings_table: BTreeMap<String, String> = resolved.strings.iter()
        .filter(|(_, v)| v.len() >= 4 && v.len() <= 256) // Only meaningful strings
        .map(|(k, v)| (format!("0x{:X}", k), v.clone())).collect();

    let json_output = JsonOutput {
        binary_info: BinaryInfo {
            file: file_name,
            arch: arch_str,
            image_base: format!("0x{:X}", entry_info.image_base),
            entry_point: format!("0x{:X}", entry_info.entry_va),
            main_address: entry_info.main_candidate.map(|a| format!("0x{:X}", a)),
        },
        functions: json_functions,
        stats: AnalysisStats {
            total_functions: functions.len(),
            user_functions: user_funcs,
            external_functions: ext_funcs,
            total_blocks: global_blocks.load(Ordering::SeqCst),
            total_ir_instructions: global_ir_insns.load(Ordering::SeqCst),
            dce_eliminated: global_dce.load(Ordering::SeqCst),
            constants_propagated: global_constprop.load(Ordering::SeqCst),
            nops_removed: global_nops.load(Ordering::SeqCst),
        },
        imports: imports_table,
        exports: exports_table,
        strings: strings_table,
    };

    // ━━━ Print summary ━━━
    println!();
    println!("╔══════════════════════════════════════════════════════╗");
    println!("║             DEEP_BLEED v0.5.0 RESULTS                ║");
    println!("╠══════════════════════════════════════════════════════╣");
    println!("║ Functions:       {:>6} user / {:>6} external        ║", json_output.stats.user_functions, json_output.stats.external_functions);
    println!("║ Basic Blocks:    {:>35} ║", json_output.stats.total_blocks);
    println!("║ IR Instructions: {:>35} ║", json_output.stats.total_ir_instructions);
    println!("║ DCE Eliminated:  {:>35} ║", json_output.stats.dce_eliminated);
    println!("║ ConstProp:       {:>35} ║", json_output.stats.constants_propagated);
    println!("║ NOPs Removed:    {:>35} ║", json_output.stats.nops_removed);
    println!("║ Strings Found:   {:>35} ║", resolved.strings.len());
    println!("║ Imports Resolved:{:>35} ║", resolved.imports.len());
    println!("║ Exports Resolved:{:>35} ║", resolved.exports.len());
    println!("╚══════════════════════════════════════════════════════╝");

    // ━━━ Write JSON ━━━
    let base_output = if args.len() > 2 && args[2] == "--output" {
        args.get(3).cloned().unwrap_or_else(|| path.clone())
    } else {
        path.clone()
    };

    let json_path = format!("{}.ir.json", base_output);
    let json_str = serde_json::to_string_pretty(&json_output)?;
    std::fs::write(&json_path, &json_str)?;
    println!("\n[*] IR JSON: {} ({} bytes)", json_path, json_str.len());

    // ━━━ PHASE 5: Generate C pseudocode (large-stack thread for deep recursion) ━━━
    println!("[*] PHASE 5: Generating C pseudocode...");
    let c_code = {
        let json_ref = &json_output;
        let res_ref  = &resolved;
        let sig_db   = signatures::SignatureDatabase::new();
        std::thread::scope(|s| {
            std::thread::Builder::new()
                .stack_size(128 * 1024 * 1024) // 128 MB stack
                .spawn_scoped(s, move || generate_c(json_ref, res_ref, &sig_db))
                .expect("spawn")
                .join()
                .expect("codegen thread")
        })
    };


    let c_path = format!("{}.decompiled.c", base_output);
    std::fs::write(&c_path, &c_code)?;
    println!("[*] C output: {} ({} bytes)", c_path, c_code.len());

    println!("[*] Done. Ready for LLM consumption.");

    Ok(())
}

/// Convert an IR instruction to JSON, with resolved names and string references
fn ir_to_json_instruction(insn: &IRInsn, block_addr: u64, resolved: &ResolvedData) -> JsonInstruction {
    let addr_str = format!("0x{:X}", block_addr);

    // Helper: resolve an operand, extracting string refs and import names
    let resolve_op = |op: &Operand| -> (String, Option<String>, Option<String>) {
        let text = op.to_string();
        match op {
            Operand::GlobalVar(addr) => {
                let name = resolved.resolve_addr(*addr).map(|s| s.to_string());
                let string = resolved.resolve_string(*addr).map(|s| s.to_string());
                (text, name, string)
            }
            Operand::UImm(val) => {
                let name = resolved.resolve_addr(*val).map(|s| s.to_string());
                let string = resolved.resolve_string(*val).map(|s| s.to_string());
                (text, name, string)
            }
            _ => (text, None, None),
        }
    };

    match insn {
        IRInsn::Call { target } => {
            let (text, name, string) = resolve_op(target);
            JsonInstruction {
                addr: addr_str, op: "call".into(), dst: None,
                src: vec![text], resolved_name: name, string_ref: string, metadata: None,
            }
        }
        IRInsn::Assign { dst, src } => {
            let (src_text, name, string) = resolve_op(src);
            let (dst_text, _, _) = resolve_op(dst);
            JsonInstruction {
                addr: addr_str, op: "assign".into(), dst: Some(dst_text),
                src: vec![src_text], resolved_name: name, string_ref: string, metadata: None,
            }
        }
        IRInsn::Push { src } => {
            let (text, name, string) = resolve_op(src);
            JsonInstruction {
                addr: addr_str, op: "push".into(), dst: None,
                src: vec![text], resolved_name: name, string_ref: string, metadata: None,
            }
        }
        IRInsn::Lea { dst, src } => {
            let (src_text, name, string) = resolve_op(src);
            JsonInstruction {
                addr: addr_str, op: "lea".into(), dst: Some(dst.to_string()),
                src: vec![src_text], resolved_name: name, string_ref: string, metadata: None,
            }
        }
        IRInsn::Cmp { lhs, rhs } => {
            let (lhs_text, _, _) = resolve_op(lhs);
            let (rhs_text, name, string) = resolve_op(rhs);
            JsonInstruction {
                addr: addr_str, op: "cmp".into(), dst: None,
                src: vec![lhs_text, rhs_text], resolved_name: name, string_ref: string, metadata: None,
            }
        }
        // For all other ops, use the generic handler
        _ => ir_to_json_generic(insn, addr_str),
    }
}

fn ir_to_json_generic(insn: &IRInsn, addr_str: String) -> JsonInstruction {
    let mk = |op: &str, dst: Option<String>, src: Vec<String>| JsonInstruction {
        addr: addr_str.clone(), op: op.into(), dst, src,
        resolved_name: None, string_ref: None, metadata: None,
    };
    match insn {
        IRInsn::Add { dst, lhs, rhs } => mk("add", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Sub { dst, lhs, rhs } => mk("sub", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Mul { dst, lhs, rhs } => mk("mul", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Div { dst, lhs, rhs } => mk("div", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::And { dst, lhs, rhs } => mk("and", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Or  { dst, lhs, rhs } => mk("or",  Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Xor { dst, lhs, rhs } => mk("xor", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Not { dst, src } => mk("not", Some(dst.to_string()), vec![src.to_string()]),
        IRInsn::Shl { dst, lhs, rhs } => mk("shl", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Shr { dst, lhs, rhs } => mk("shr", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Sar { dst, lhs, rhs } => mk("sar", Some(dst.to_string()), vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::Load { dst, src } => mk("load", Some(dst.to_string()), vec![src.to_string()]),
        IRInsn::Store { dst, src } => mk("store", Some(dst.to_string()), vec![src.to_string()]),
        IRInsn::Jump { target } => mk("jump", None, vec![format!("0x{:X}", target)]),
        IRInsn::CondJump { target, condition } => mk("cond_jump", None, vec![format!("0x{:X}", target), condition.clone()]),
        IRInsn::Return => mk("ret", None, vec![]),
        IRInsn::Pop { dst } => mk("pop", Some(dst.to_string()), vec![]),
        IRInsn::Test { lhs, rhs } => mk("test", None, vec![lhs.to_string(), rhs.to_string()]),
        IRInsn::SetCC { dst, condition } => mk(&format!("set{}", condition.to_lowercase()), Some(dst.to_string()), vec![]),
        IRInsn::Movzx { dst, src } => mk("movzx", Some(dst.to_string()), vec![src.to_string()]),
        IRInsn::Movsx { dst, src } => mk("movsx", Some(dst.to_string()), vec![src.to_string()]),
        IRInsn::Movabs { dst, src } => mk("movabs", Some(dst.to_string()), vec![format!("0x{:X}", src)]),
        IRInsn::Unknown { asm, addr } => {
            JsonInstruction {
                addr: format!("0x{:X}", addr), op: "unknown".into(), dst: None,
                src: vec![asm.clone()], resolved_name: None, string_ref: None, metadata: None,
            }
        }
        _ => mk("nop", None, vec![]),
    }
}
