mod types;
mod lifter;
mod optimizer;
mod entry_hunter;

use crate::entry_hunter::*;
use crate::lifter::*;
use crate::optimizer::*;
use crate::types::*;

use dashmap::DashMap;
use fnv::{FnvHashMap, FnvHashSet};
use memmap2::Mmap;
use object::{File, Object, ObjectSection, SectionKind};
use rayon::prelude::*;
use std::fs::File as StdFile;
use std::sync::atomic::{AtomicUsize, Ordering};

const CHUNK_SIZE: usize = 16 * 1024;

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: deepbleed <path_to_pe_file> [--output <ir.json>]");
        std::process::exit(1);
    }

    let path = &args[1];
    println!("╔══════════════════════════════════════════════════════╗");
    println!("║  DEEP_BLEED v0.4.0 — Aggressive Decompilation Engine ║");
    println!("║  Mode: IR Lifting + SSA + DCE + ConstProp            ║");
    println!("║  Hyper-Parallel: ENABLED (Rayon + FnvHash)           ║");
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

    // ━━━ Build external library signatures ━━━
    let external_names = build_external_set(&obj);
    println!("[+] Known external symbols: {}", external_names.len());

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

    println!("[*] Code chunks for parallel execution: {}", code_chunks.len());

    // ━━━ PHASE 1: Parallel CFG analysis (burn the CPU) ━━━
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

    println!("[!] CFG analysis complete: {} instructions scanned", total_inst.load(Ordering::SeqCst));

    // ━━━ PHASE 2: Entry Point & main() detection ━━━
    println!("\n[*] PHASE 2: Entry Point Hunting...");
    let entry_info = find_entry_and_main(
        &obj, &mmap, machine_mode, stack_width,
        text_base, text_offset, text_size,
    );

    // ━━━ PHASE 3: Function discovery ━━━
    println!("\n[*] PHASE 3: Function Discovery & Classification...");
    let unique_leaders: FnvHashSet<u64> = leaders_map.iter().map(|e| *e.key()).collect();
    let call_targets_fnv: FnvHashMap<u64, u32> = call_targets_map.iter()
        .map(|e| (*e.key(), *e.value())).collect();

    let functions = discover_functions(
        &call_targets_fnv, &entry_info, &external_names, &unique_leaders,
    );

    let user_funcs = functions.iter().filter(|f| f.kind != FunctionKind::ExternalLib).count();
    let ext_funcs = functions.iter().filter(|f| f.kind == FunctionKind::ExternalLib).count();
    println!("[+] Total functions: {} (USER: {}, EXTERNAL_LIB: {})", functions.len(), user_funcs, ext_funcs);

    // ━━━ PHASE 4: Parallel IR Lifting + Optimization ━━━
    println!("\n[*] PHASE 4: Parallel IR Lifting + SSA + DCE + ConstProp...");
    let global_dce = AtomicUsize::new(0);
    let global_constprop = AtomicUsize::new(0);
    let global_nops = AtomicUsize::new(0);
    let global_ir_insns = AtomicUsize::new(0);
    let global_blocks = AtomicUsize::new(0);

    // Only lift USER functions (skip EXTERNAL_LIB)
    let user_functions: Vec<&FunctionInfo> = functions.iter()
        .filter(|f| f.kind != FunctionKind::ExternalLib)
        .collect();

    let json_functions: Vec<JsonFunction> = user_functions.par_iter().map(|func| {
        let mut json_blocks = Vec::new();
        let mut cfg_links = Vec::new();
        let mut all_ssa_vars = Vec::new();

        for &block_addr in &func.block_addrs {
            // Find the chunk containing this block
            for chunk in &code_chunks {
                if block_addr >= chunk.address && block_addr < chunk.address + chunk.size as u64 {
                    let end = chunk.offset + chunk.size;
                    if let Some(raw_code) = mmap.get(chunk.offset..end) {
                        let block_lifter = BlockLifter::new(machine_mode, stack_width, chunk.address);
                        let mut block = block_lifter.lift_basic_block(raw_code, block_addr);

                        // Optimize: SSA + ConstProp + DCE
                        let (ssa_vars, stats) = optimize_block(&mut block);
                        all_ssa_vars.extend(ssa_vars);

                        global_dce.fetch_add(stats.dce_eliminated, Ordering::Relaxed);
                        global_constprop.fetch_add(stats.constants_propagated, Ordering::Relaxed);
                        global_nops.fetch_add(stats.nops_removed, Ordering::Relaxed);
                        global_ir_insns.fetch_add(block.ir_instructions.len(), Ordering::Relaxed);
                        global_blocks.fetch_add(1, Ordering::Relaxed);

                        // Build CFG edges
                        let block_id = format!("bb_{:X}", block.start_addr);
                        for edge in &block.edges {
                            let edge_type = if block.ir_instructions.iter().any(|i| matches!(i, IRInsn::Call { .. })) {
                                "call"
                            } else if block.ir_instructions.iter().any(|i| matches!(i, IRInsn::CondJump { .. })) {
                                "branch"
                            } else {
                                "fallthrough"
                            };
                            cfg_links.push(CfgEdge {
                                from: block_id.clone(),
                                to: format!("bb_{:X}", edge),
                                edge_type: edge_type.to_string(),
                            });
                        }

                        // Convert to JSON instructions
                        let json_insns: Vec<JsonInstruction> = block.ir_instructions.iter()
                            .filter(|i| !matches!(i, IRInsn::Label { .. }))
                            .map(|i| ir_to_json_instruction(i, block.start_addr))
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

        // Deduplicate SSA vars
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

    // ━━━ Build final JSON ━━━
    let file_name = std::path::Path::new(path).file_name()
        .unwrap_or_default().to_string_lossy().to_string();

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
    };

    // ━━━ Print summary ━━━
    println!();
    println!("╔══════════════════════════════════════════════════════╗");
    println!("║             DEEP_BLEED ANALYSIS RESULTS              ║");
    println!("╠══════════════════════════════════════════════════════╣");
    println!("║ Total Functions:         {:>28} ║", json_output.stats.total_functions);
    println!("║ User Functions:          {:>28} ║", json_output.stats.user_functions);
    println!("║ External (skipped):      {:>28} ║", json_output.stats.external_functions);
    println!("║ Total Basic Blocks:      {:>28} ║", json_output.stats.total_blocks);
    println!("║ Total IR Instructions:   {:>28} ║", json_output.stats.total_ir_instructions);
    println!("║ DCE Eliminated:          {:>28} ║", json_output.stats.dce_eliminated);
    println!("║ Constants Propagated:    {:>28} ║", json_output.stats.constants_propagated);
    println!("║ NOPs Removed:            {:>28} ║", json_output.stats.nops_removed);
    println!("╚══════════════════════════════════════════════════════╝");

    // ━━━ Write JSON ━━━
    let output_path = if args.len() > 2 && args[2] == "--output" {
        args.get(3).cloned().unwrap_or_else(|| format!("{}.ir.json", path))
    } else {
        format!("{}.ir.json", path)
    };

    let json_str = serde_json::to_string_pretty(&json_output)?;
    std::fs::write(&output_path, &json_str)?;
    println!("\n[*] IR JSON written to: {}", output_path);
    println!("[*] JSON size: {} bytes", json_str.len());
    println!("[*] Ready for LLM consumption.");

    Ok(())
}

/// Convert an IR instruction to JSON format
fn ir_to_json_instruction(insn: &IRInsn, block_addr: u64) -> JsonInstruction {
    let addr_str = format!("0x{:X}", block_addr);

    match insn {
        IRInsn::Assign { dst, src } => JsonInstruction {
            addr: addr_str, op: "assign".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: try_ascii_metadata(src),
        },
        IRInsn::Add { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "add".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Sub { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "sub".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Mul { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "mul".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Div { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "div".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::And { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "and".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Or { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "or".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Xor { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "xor".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Not { dst, src } => JsonInstruction {
            addr: addr_str, op: "not".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Shl { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "shl".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Shr { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "shr".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Sar { dst, lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "sar".into(),
            dst: Some(dst.to_string()), src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::Load { dst, src } => JsonInstruction {
            addr: addr_str, op: "load".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Store { dst, src } => JsonInstruction {
            addr: addr_str, op: "store".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Lea { dst, src } => JsonInstruction {
            addr: addr_str, op: "lea".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Call { target } => JsonInstruction {
            addr: addr_str, op: "call".into(),
            dst: None, src: vec![target.to_string()],
            metadata: None,
        },
        IRInsn::Jump { target } => JsonInstruction {
            addr: addr_str, op: "jump".into(),
            dst: None, src: vec![format!("0x{:X}", target)],
            metadata: None,
        },
        IRInsn::CondJump { target, condition } => JsonInstruction {
            addr: addr_str, op: "cond_jump".into(),
            dst: None, src: vec![format!("0x{:X}", target), condition.clone()],
            metadata: None,
        },
        IRInsn::Return => JsonInstruction {
            addr: addr_str, op: "ret".into(),
            dst: None, src: vec![],
            metadata: None,
        },
        IRInsn::Push { src } => JsonInstruction {
            addr: addr_str, op: "push".into(),
            dst: None, src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Pop { dst } => JsonInstruction {
            addr: addr_str, op: "pop".into(),
            dst: Some(dst.to_string()), src: vec![],
            metadata: None,
        },
        IRInsn::Cmp { lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "cmp".into(),
            dst: None, src: vec![lhs.to_string(), rhs.to_string()],
            metadata: try_ascii_metadata(rhs),
        },
        IRInsn::Test { lhs, rhs } => JsonInstruction {
            addr: addr_str, op: "test".into(),
            dst: None, src: vec![lhs.to_string(), rhs.to_string()],
            metadata: None,
        },
        IRInsn::SetCC { dst, condition } => JsonInstruction {
            addr: addr_str, op: format!("set{}", condition.to_lowercase()),
            dst: Some(dst.to_string()), src: vec![],
            metadata: None,
        },
        IRInsn::Movzx { dst, src } => JsonInstruction {
            addr: addr_str, op: "movzx".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Movsx { dst, src } => JsonInstruction {
            addr: addr_str, op: "movsx".into(),
            dst: Some(dst.to_string()), src: vec![src.to_string()],
            metadata: None,
        },
        IRInsn::Movabs { dst, src } => JsonInstruction {
            addr: addr_str, op: "movabs".into(),
            dst: Some(dst.to_string()), src: vec![format!("0x{:X}", src)],
            metadata: try_ascii_u64(*src),
        },
        IRInsn::Unknown { asm, addr } => JsonInstruction {
            addr: format!("0x{:X}", addr), op: "unknown".into(),
            dst: None, src: vec![asm.clone()],
            metadata: None,
        },
        _ => JsonInstruction {
            addr: addr_str, op: "nop".into(),
            dst: None, src: vec![],
            metadata: None,
        },
    }
}

/// Try to extract ASCII representation from immediate values
fn try_ascii_metadata(op: &Operand) -> Option<InsnMetadata> {
    match op {
        Operand::UImm(val) => try_ascii_u64(*val),
        Operand::Imm(val) => try_ascii_u64(*val as u64),
        _ => None,
    }
}

fn try_ascii_u64(val: u64) -> Option<InsnMetadata> {
    if val == 0 { return None; }
    let bytes = val.to_le_bytes();
    let ascii: String = bytes.iter()
        .take_while(|&&b| b != 0)
        .filter(|&&b| b >= 0x20 && b <= 0x7E)
        .map(|&b| b as char)
        .collect();
    if ascii.len() >= 2 {
        Some(InsnMetadata {
            ascii: Some(ascii),
            constant_value: Some(format!("0x{:X}", val)),
        })
    } else {
        None
    }
}
