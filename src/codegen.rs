use crate::resolver::ResolvedData;
use crate::signatures::{SignatureDatabase, CallingConvention};
use crate::structurer::*;
use crate::types::*;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED CODEGEN v2 — Structured C Pseudocode Generator
//  Aggressive: if/else/while/do-while, no goto, no CMP/TEST exposed,
//  prologue/epilogue suppressed, call args inferred, types guessed.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

const INDENT: &str = "    ";

pub fn generate_c_header(output: &JsonOutput) -> String {
    let mut c = String::with_capacity(1024 * 1024);

    // ─── File header ───
    c.push_str("/*\n");
    c.push_str(" * ═══════════════════════════════════════════════════\n");
    c.push_str(" *  DEEP_BLEED Decompilation Output\n");
    c.push_str(&format!(" *  Binary:  {}\n", output.binary_info.file));
    c.push_str(&format!(" *  Arch:    {}\n", output.binary_info.arch));
    c.push_str(&format!(" *  Base:    {}\n", output.binary_info.image_base));
    c.push_str(&format!(" *  Entry:   {}\n", output.binary_info.entry_point));
    if let Some(ref main) = output.binary_info.main_address {
        c.push_str(&format!(" *  main():  {}\n", main));
    }
    c.push_str(&format!(" *  Functions: {} (user: {}, external: {})\n",
        output.stats.total_functions,
        output.stats.user_functions,
        output.stats.external_functions));
    c.push_str(" * ═══════════════════════════════════════════════════\n");
    c.push_str(" */\n\n");
    c.push_str("#include <windows.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n#include <stdint.h>\n#include <stdbool.h>\n\n");

    // ─── Imports as extern declarations ───
    if !output.imports.is_empty() {
        c.push_str("/* ═══ Imported Functions ═══ */\n");
        for (addr, name) in &output.imports {
            let cname = sanitize_c_ident(name);
            c.push_str(&format!("extern void* {}; /* IAT @ {} */\n", cname, addr));
        }
        c.push('\n');
    }

    // ─── String constants ───
    if !output.strings.is_empty() {
        c.push_str("/* ═══ String References ═══ */\n");
        for (addr, s) in &output.strings {
            if s.len() < 4 { continue; }
            let _hex = addr.trim_start_matches("0x");
            c.push_str(&format!("/* {} = \"{}\" */\n", addr, escape_c_string(&truncate(s, 80))));
        }
        c.push('\n');
    }

    // ─── Forward declarations ───
    c.push_str("/* ═══ Forward Declarations ═══ */\n");
    c
}

pub fn generate_c_forward_decls(output: &JsonOutput, resolved: &ResolvedData, sig_db: &SignatureDatabase) -> String {
    let mut c = String::new();
    for func in &output.functions {
        let fname = resolve_func_name(&func.name, &func.address, resolved);
        let (ret_type, params) = if let Some(sig) = sig_db.lookup(&fname) {
            let pstr = if sig.parameters.is_empty() { "void".to_string() }
                      else { sig.parameters.iter().map(|p| format!("{} {}", p.ptype, p.name)).collect::<Vec<_>>().join(", ") };
            (sig.ret_type.as_str(), pstr)
        } else {
            let rt = infer_return_type(&func.name, &fname);
            let ps = infer_params(func, resolved);
            (rt, ps)
        };
        c.push_str(&format!("{} {}({}); /* {} @ {} */\n",
            ret_type, fname, params, func.kind, func.address));
    }
    c.push('\n');
    c
}

pub fn generate_c(output: &JsonOutput, resolved: &ResolvedData, sig_db: &SignatureDatabase) -> String {
    let mut c = generate_c_header(output);
    c.push_str(&generate_c_forward_decls(output, resolved, sig_db));

    // ─── Generate each function (Serial fallback, main handles parallel) ───
    for func in &output.functions {
        generate_function(&mut c, func, resolved, sig_db);
    }

    c
}

pub fn generate_function_string(func: &JsonFunction, resolved: &ResolvedData, sig_db: &SignatureDatabase) -> String {
    let mut c = String::new();
    generate_function(&mut c, func, resolved, sig_db);
    c
}

pub fn generate_function(c: &mut String, func_in: &JsonFunction, resolved: &ResolvedData, sig_db: &SignatureDatabase) {
    let mut func_val = func_in.clone();
    rename_ssa_vars(&mut func_val);
    prepare_calls(&mut func_val, resolved, sig_db);
    apply_expression_folding_c(&mut func_val, resolved);
    let func = &func_val;

    let fname = resolve_func_name(&func.name, &func.address, resolved);
    let (ret_type, params) = if let Some(sig) = sig_db.lookup(&fname) {
        let pstr = if sig.parameters.is_empty() { "void".to_string() }
                  else { sig.parameters.iter().map(|p| format!("{} {}", p.ptype, p.name)).collect::<Vec<_>>().join(", ") };
        (sig.ret_type.clone(), pstr)
    } else {
        (infer_return_type(&func.name, &fname).to_string(), infer_params(func, resolved))
    };

    c.push_str("/* ═══════════════════════════════════════════════════\n");
    c.push_str(&format!(" * {} @ {} ({})\n", fname, func.address, func.kind));
    c.push_str(&format!(" * Blocks: {} | SSA vars: {}\n", func.blocks.len(), func.ssa_vars.len()));
    c.push_str(" * ═══════════════════════════════════════════════════ */\n");
    c.push_str(&format!("{} {}({}) {{\n", ret_type, fname, params));

    // ─── Local variable declarations (deduplicated) ───
    emit_local_vars(c, func);

    if func.blocks.is_empty() {
        if ret_type != "void" {
            c.push_str(&format!("{}return 0;\n", INDENT));
        }
        c.push_str("}\n\n");
        return;
    }

    // ─── Structure the CFG ───
    let structured = structure_function(func);

    // ─── Emit structured C ───
    let mut ctx = EmitCtx {
        resolved: &resolved,
        sig_db,
        indent: 1,
    };
    for node in &structured {
        emit_node(c, node, &mut ctx, func);
    }

    // ─── Ensure there's a return ───
    let needs_return = func.blocks.iter().any(|b|
        b.instructions.iter().any(|i| i.op == "ret")
    );
    if !needs_return {
        if ret_type != "void" {
            c.push_str(&format!("{}return 0;\n", INDENT));
        } else {
            c.push_str(&format!("{}return;\n", INDENT));
        }
    }

    c.push_str("}\n\n");
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Emission Context
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

struct EmitCtx<'a> {
    resolved: &'a ResolvedData,
    sig_db: &'a SignatureDatabase,
    indent: usize,
}

impl<'a> EmitCtx<'a> {
    fn pad(&self) -> String {
        INDENT.repeat(self.indent)
    }
    fn indented(&self) -> EmitCtx<'a> {
        EmitCtx { resolved: self.resolved, sig_db: self.sig_db, indent: self.indent + 1 }
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Recursive CFG node emitter
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn emit_node(c: &mut String, node: &CfgStructure, ctx: &mut EmitCtx, func: &JsonFunction) {
    match node {
        CfgStructure::Block(fb) => {
            emit_flat_block(c, fb, ctx);
        }

        CfgStructure::If { cond, then, else_, .. } => {
            let pad = ctx.pad();
            c.push_str(&format!("{}if ({}) {{\n", pad, cond));
            let mut inner = ctx.indented();
            for n in then { emit_node(c, n, &mut inner, func); }
            if let Some(eb) = else_ {
                c.push_str(&format!("{}}} else {{\n", pad));
                for n in eb { emit_node(c, n, &mut inner, func); }
            }
            c.push_str(&format!("{}}}\n", pad));
        }

        CfgStructure::While { cond, body, .. } => {
            let pad = ctx.pad();
            c.push_str(&format!("{}while ({}) {{\n", pad, cond));
            let mut inner = ctx.indented();
            for n in body { emit_node(c, n, &mut inner, func); }
            c.push_str(&format!("{}}}\n", pad));
        }

        CfgStructure::DoWhile { cond, body } => {
            let pad = ctx.pad();
            c.push_str(&format!("{}do {{\n", pad));
            let mut inner = ctx.indented();
            for n in body { emit_node(c, n, &mut inner, func); }
            c.push_str(&format!("{}}} while ({});\n", pad, cond));
        }

        CfgStructure::InfiniteLoop { body } => {
            let pad = ctx.pad();
            c.push_str(&format!("{}while (1) {{\n", pad));
            let mut inner = ctx.indented();
            for n in body { emit_node(c, n, &mut inner, func); }
            c.push_str(&format!("{}}}\n", pad));
        }

        CfgStructure::Seq(nodes) => {
            for n in nodes { emit_node(c, n, ctx, func); }
        }
    }
}

fn emit_flat_block(c: &mut String, fb: &FlatBlock, ctx: &EmitCtx) {
    let pad = ctx.pad();

    let insns = &fb.instructions;
    let n = insns.len();
    let mut i = 0;

    while i < n {
        let insn = &insns[i];

        // ── Skip prologue/epilogue noise ──
        if is_prologue_epilogue_noise(insn) {
            i += 1;
            continue;
        }

        // ── Skip pure CMP/TEST (already fused into conditions) ──
        if insn.op == "cmp" || insn.op == "test" {
            // Emit as comment only when not followed by cond_jump
            let next_is_branch = insns.get(i + 1)
                .map(|nx| nx.op == "cond_jump")
                .unwrap_or(false);
            if !next_is_branch {
                let lhs = resolve_operand_str(insn.src.get(0).map(|s| s.as_str()).unwrap_or("?"), ctx.resolved);
                let rhs = resolve_operand_str(insn.src.get(1).map(|s| s.as_str()).unwrap_or("?"), ctx.resolved);
                c.push_str(&format!("{}/* compare {} vs {} */\n", pad, lhs, rhs));
            }
            i += 1;
            continue;
        }

        // ── Skip nops ──
        if insn.op == "nop" {
            i += 1;
            continue;
        }

        // ── CALL (prepared) ──
        if insn.op == "call" {
            let call_str = insn.string_ref.as_deref().unwrap_or("call(...)");
            if let Some(dst) = &insn.dst {
                c.push_str(&format!("{}{} = {};\n", pad, prettify_operand(dst), call_str));
            } else {
                c.push_str(&format!("{}{};\n", pad, call_str));
            }
            i += 1;
            continue;
        }

        // ── RETURN ──
        if insn.op == "ret" {
            let ret_val = collect_eax_before(insns, i);
            if let Some(v) = ret_val {
                c.push_str(&format!("{}return {};\n", pad, v));
            } else {
                c.push_str(&format!("{}return;\n", pad));
            }
            i += 1;
            continue;
        }

        // ── Generic instruction emission ──
        let line = instruction_to_c(insn, ctx.resolved);
        if !line.is_empty() {
            c.push_str(&format!("{}{};\n", pad, line));
        }

        i += 1;
    }
}

/// Look backwards from `idx` for the last assign to eax/rax
fn collect_eax_before(insns: &[JsonInstruction], idx: usize) -> Option<String> {
    for insn in insns[..idx].iter().rev() {
        if insn.op == "assign" || insn.op == "movzx" || insn.op == "movsx" || insn.op == "movabs" || insn.op == "load" {
            if let Some(dst) = &insn.dst {
                if dst.contains("eax") || dst.contains("rax") {
                    return insn.src.get(0).cloned();
                }
            }
        }
        break; // only look one step back
    }
    None
}

/// Look backwards for the last assignment to a specific register
fn find_last_reg_assign(insns: &[JsonInstruction], idx: usize, reg_name: &str) -> Option<String> {
    for insn in insns[..idx].iter().rev() {
        if insn.op == "assign" || insn.op == "movzx" || insn.op == "movsx" || insn.op == "lea" || insn.op == "movabs" || insn.op == "load" {
            if let Some(dst) = &insn.dst {
                if dst.contains(reg_name) {
                    return insn.src.get(0).cloned();
                }
            }
        }
        if insn.op == "call" { break; } // Don't look past other calls
    }
    None
}


// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Instruction → C string
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn instruction_to_c(insn: &JsonInstruction, resolved: &ResolvedData) -> String {
    let resolve = |s: &str| resolve_operand_str(s, resolved);

    let dst = insn.dst.as_deref().map(|d| prettify_operand(&resolve(d))).unwrap_or_default();
    let src: Vec<String> = insn.src.iter().map(|s| prettify_operand(&resolve(s))).collect();
    let q = "?".to_string();
    let s0 = src.get(0).cloned().unwrap_or_else(|| q.clone());
    let s1 = src.get(1).cloned().unwrap_or_else(|| q.clone());

    match insn.op.as_str() {
        "assign"  => format!("{} = {}", dst, s0),
        "add"     => format!("{} = {} + {}", dst, s0, s1),
        "sub"     => format!("{} = {} - {}", dst, s0, s1),
        "mul"     => format!("{} = {} * {}", dst, s0, s1),
        "div"     => format!("{} = {} / {}", dst, s0, s1),
        "and"     => format!("{} = {} & {}", dst, s0, s1),
        "or"      => format!("{} = {} | {}", dst, s0, s1),
        "xor"     => format!("{} = {} ^ {}", dst, s0, s1),
        "not"     => format!("{} = ~{}", dst, s0),
        "shl"     => format!("{} = {} << {}", dst, s0, s1),
        "shr"     => format!("{} = (unsigned){} >> {}", dst, s0, s1),
        "sar"     => format!("{} = (signed){} >> {}", dst, s0, s1),
        "load"    => format!("{} = *({})", dst, s0),
        "store"   => format!("*({}){}", s0,
            if dst.is_empty() { String::new() } else { format!(" = {}", dst) }),
        "lea"     => format!("{} = &{}", dst, s0),
        "call"    => {
            let t = resolve_call_target(&s0, resolved);
            format!("{}()", t)
        }
        "jump"    => String::new(), // handled structurally
        "cond_jump" => String::new(), // handled structurally
        "ret"     => String::new(), // handled above
        "pop"     => format!("{} = stack_pop()", dst),
        "movzx"   => format!("{} = (unsigned){}", dst, s0),
        "movsx"   => format!("{} = (signed){}", dst, s0),
        "movabs"  => format!("{} = {}", dst, s0),
        "unknown" => format!("/* asm: {} */", s0),
        "nop"     => String::new(),
        op if op.starts_with("set") => {
            let cond_code = &op[3..].to_uppercase();
            let c_cond = set_cc_to_c(cond_code, &s0);
            format!("{} = {}", dst, c_cond)
        }
        _ => format!("/* {} {} */", insn.op, src.join(", ")),
    }
}

/// SetCC → C boolean expression
fn set_cc_to_c(cond: &str, _operand: &str) -> String {
    match cond {
        "Z" | "E"   => "(flags_ZF != 0)".into(),
        "NZ" | "NE" => "(flags_ZF == 0)".into(),
        "B" | "C"   => "(flags_CF != 0)".into(),
        "NB" | "NC" => "(flags_CF == 0)".into(),
        "BE"        => "(flags_CF != 0 || flags_ZF != 0)".into(),
        "NBE" | "A" => "(flags_CF == 0 && flags_ZF == 0)".into(),
        "L" | "NGE" => "(flags_SF != flags_OF)".into(),
        "NL" | "GE" => "(flags_SF == flags_OF)".into(),
        "LE" | "NG" => "(flags_ZF != 0 || flags_SF != flags_OF)".into(),
        "NLE" | "G" => "(flags_ZF == 0 && flags_SF == flags_OF)".into(),
        "S"         => "(flags_SF != 0)".into(),
        "NS"        => "(flags_SF == 0)".into(),
        "O"         => "(flags_OF != 0)".into(),
        "NO"        => "(flags_OF == 0)".into(),
        "P" | "PE"  => "(flags_PF != 0)".into(),
        "NP" | "PO" => "(flags_PF == 0)".into(),
        _           => format!("(bool_{})", cond.to_lowercase()),
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Local Variable Emission
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn emit_local_vars(c: &mut String, func: &JsonFunction) {
    if func.ssa_vars.is_empty() { return; }

    // Group by canonical register, pick a type guess
    let mut seen: std::collections::BTreeSet<String> = std::collections::BTreeSet::new();
    let mut vars: Vec<(String, String)> = Vec::new(); // (name, type)

    for var in &func.ssa_vars {
        let base = &var.register;
        if seen.insert(base.clone()) {
            let ty = infer_var_type(base);
            let vname = prettify_operand(base);
            vars.push((vname, ty.to_string()));
        }
    }

    if !vars.is_empty() {
        c.push_str(&format!("{}/* local variables */\n", INDENT));
        for (name, ty) in &vars {
            c.push_str(&format!("{}{} {};\n", INDENT, ty, name));
        }
        // Also emit local stack slots
        for insn in func.blocks.iter().flat_map(|b| b.instructions.iter()) {
            for src in &insn.src {
                if let Some(rest) = src.strip_prefix("local_m") {
                    let vname = format!("var_{}", rest);
                    if seen.insert(format!("local_m{}", rest)) {
                        c.push_str(&format!("{}int32_t {};\n", INDENT, vname));
                    }
                }
            }
            if let Some(dst) = &insn.dst {
                if let Some(rest) = dst.strip_prefix("local_m") {
                    let vname = format!("var_{}", rest);
                    if seen.insert(format!("local_m{}", rest)) {
                        c.push_str(&format!("{}int32_t {};\n", INDENT, vname));
                    }
                }
            }
        }
        c.push('\n');
    }
}

fn infer_var_type(reg: &str) -> &'static str {
    if reg.starts_with("xmm") { return "double"; }
    if reg.starts_with("r") && reg.len() == 2 { return "uint64_t"; }
    "int32_t"
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Operand/Name resolution
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn resolve_operand_str(s: &str, resolved: &ResolvedData) -> String {
    // gvar_XXXXXXXX → try import/export/string
    if let Some(hex) = s.strip_prefix("gvar_") {
        if let Ok(addr) = u64::from_str_radix(hex, 16) {
            if let Some(name) = resolved.resolve_addr(addr) {
                return sanitize_c_ident(name);
            }
            if let Some(string) = resolved.resolve_string(addr) {
                return format!("\"{}\"", escape_c_string(&truncate(string, 120)));
            }
        }
        return format!("*(DWORD*)0x{}", hex);
    }

    // 0xXXXXXXXX → resolve
    if let Some(hex) = s.strip_prefix("0x").or_else(|| s.strip_prefix("0X")) {
        if let Ok(addr) = u64::from_str_radix(hex, 16) {
            if let Some(name) = resolved.resolve_addr(addr) {
                return sanitize_c_ident(name);
            }
            if let Some(string) = resolved.resolve_string(addr) {
                return format!("\"{}\"", escape_c_string(&truncate(string, 120)));
            }
        }
    }

    s.to_string()
}

fn resolve_call_target(target: &str, resolved: &ResolvedData) -> String {
    let hex = target.trim_start_matches("0x").trim_start_matches("0X");
    if let Ok(addr) = u64::from_str_radix(hex, 16) {
        if let Some(name) = resolved.resolve_addr(addr) {
            return sanitize_c_ident(name);
        }
        return format!("sub_{:X}", addr);
    }
    if let Some(hex2) = target.strip_prefix("gvar_") {
        if let Ok(addr) = u64::from_str_radix(hex2, 16) {
            if let Some(name) = resolved.resolve_addr(addr) {
                return format!("(&{})", sanitize_c_ident(name));
            }
        }
    }
    // SSA var that is a function pointer
    if target.contains('_') {
        return format!("(*(FARPROC*){})", target);
    }
    target.to_string()
}

fn rename_ssa_vars(func: &mut JsonFunction) {
    let mut mapped_names = std::collections::HashMap::new();
    let mut counter = 1;

    let mut map_name = |s: &mut String| {
        if s.contains('_') 
            && !s.starts_with("arg_") 
            && !s.starts_with("var_") 
            && !s.starts_with("local_") 
            && !s.starts_with("flags")
            && !s.starts_with("gvar_") 
        {
            let new_name = mapped_names.entry(s.clone()).or_insert_with(|| {
                let v = format!("t{}", counter);
                counter += 1;
                v
            });
            *s = new_name.clone();
        }
    };

    for b in &mut func.blocks {
        for i in &mut b.instructions {
            if let Some(d) = &mut i.dst {
                map_name(d);
            }
            for s in &mut i.src {
                map_name(s);
            }
        }
    }
    for v in &mut func.ssa_vars {
        map_name(&mut v.name);
    }
}

fn prepare_calls(func: &mut JsonFunction, resolved: &ResolvedData, sig_db: &SignatureDatabase) {
    for block in &mut func.blocks {
        let insns = std::mem::take(&mut block.instructions);
        let mut pending_args: Vec<String> = Vec::new();
        let mut new_insns: Vec<JsonInstruction> = Vec::with_capacity(insns.len());
        
        let mut i = 0;
        while i < insns.len() {
            let insn = &insns[i];
            
            if is_prologue_epilogue_noise(insn) || insn.op == "nop" {
                i += 1; continue;
            }
            
            if insn.op == "push" {
                let resolved_val = resolve_operand_str(insn.src.get(0).map(|s| s.as_str()).unwrap_or("?"), resolved);
                pending_args.push(prettify_operand(&resolved_val));
                i += 1; continue;
            }
            
            if insn.op == "call" {
                let target_raw = insn.src.get(0).map(|s| s.as_str()).unwrap_or("?");
                let target = resolve_call_target(target_raw, resolved);
                
                let sig = sig_db.lookup(&target);
                let expected_args = sig.map(|s| s.parameters.len()).unwrap_or(0);
                let cc = sig.map(|s| s.calling_convention).unwrap_or(CallingConvention::Unknown);
                
                let mut args: Vec<String> = pending_args.drain(..).rev().collect();
                
                let mut fastcall_args = Vec::new();
                if cc == CallingConvention::Fastcall || cc == CallingConvention::Unknown {
                    let regs64 = ["rcx", "rdx", "r8", "r9"];
                    let regs32 = ["ecx", "edx", "r8d", "r9d"];
                    for idx in 0..4 {
                        if expected_args > 0 && fastcall_args.len() >= expected_args { break; }
                        let mut found = false;
                        for reg in [regs64[idx], regs32[idx]] {
                            if let Some(val) = find_last_reg_assign(&new_insns, new_insns.len(), reg) {
                                let resolved_val = resolve_operand_str(&val, resolved);
                                fastcall_args.push(prettify_operand(&resolved_val));
                                found = true;
                                break;
                            }
                        }
                        if !found {
                            if expected_args > 0 && idx < expected_args {
                                fastcall_args.push(regs64[idx].to_string());
                            } else if cc == CallingConvention::Unknown {
                                break;
                            }
                        }
                    }
                }
                
                let mut final_args = fastcall_args;
                final_args.extend(args);
                
                if expected_args > final_args.len() {
                    for j in final_args.len()..expected_args {
                        final_args.push(format!("/* param_{}? */ 0", j + 1));
                    }
                } else if sig.is_some() && final_args.len() > expected_args {
                    let excess = final_args.len() - expected_args;
                    for _ in 0..excess { final_args.pop(); }
                }
                
                if let Some(s) = sig {
                    for (j, arg) in final_args.iter_mut().enumerate() {
                        if let Some(param) = s.parameters.get(j) {
                            *arg = format!("/* {} */ {}", param.name, arg);
                        }
                    }
                }
                
                let formatted_call = format!("{}({})", sanitize_c_ident(&target), final_args.join(", "));
                
                // Return linkage: Look ahead to see if the next instruction consumes RAX
                let mut call_dst = None;
                if i + 1 < insns.len() {
                    let next = &insns[i + 1];
                    if next.op == "assign" {
                        if let Some(d) = next.dst.as_deref() {
                            let src = next.src.get(0).map(|s| s.as_str()).unwrap_or("");
                            if src.contains("eax") || src.contains("rax") || src.contains("al") {
                                call_dst = Some(d.to_string());
                                i += 1; // skip the assignment, fold it into the call
                            }
                        }
                    }
                }

                let mut new_insn = insn.clone();
                new_insn.dst = call_dst;
                new_insn.string_ref = Some(formatted_call);
                new_insn.src.extend(final_args); // For semantic info
                new_insns.push(new_insn);
                
                i += 1; continue;
            }
            
            // If not push/call, just flush args (or ignore as we optimized them away)
            if !pending_args.is_empty() {
                pending_args.clear();
            }
            
            new_insns.push(insn.clone());
            i += 1;
        }
        
        block.instructions = new_insns;
    }
}

fn resolve_func_name(name: &str, addr_str: &str, resolved: &ResolvedData) -> String {
    let hex = addr_str.trim_start_matches("0x").trim_start_matches("0X");
    if let Ok(addr) = u64::from_str_radix(hex, 16) {
        if let Some(export_name) = resolved.resolve_addr(addr) {
            return sanitize_c_ident(export_name);
        }
    }
    sanitize_c_ident(name)
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Type inference
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn infer_return_type(name: &str, fname: &str) -> &'static str {
    let n = fname.to_lowercase();
    // Heuristics for common Windows API return types
    if n.contains("bool") || n.contains("is_") || n.starts_with("has") { return "BOOL"; }
    if n.starts_with("get") || n.ends_with("count") || n.ends_with("size") { return "int"; }
    if n.contains("handle") || n.ends_with("handle") { return "HANDLE"; }
    if n.contains("str") || n.ends_with("string") || n.ends_with("name") { return "char*"; }
    if name == "MAIN" || fname == "main" { return "int __cdecl"; }
    "void"
}

fn infer_params(func: &JsonFunction, _resolved: &ResolvedData) -> String {
    if func.kind == "MAIN" {
        return "int argc, char** argv, char** envp".to_string();
    }
    // Try to detect parameters by looking at [ebp+N] local_XX accesses (positive offsets)
    let mut param_offsets: std::collections::BTreeSet<i32> = std::collections::BTreeSet::new();
    for block in &func.blocks {
        for insn in &block.instructions {
            for src in &insn.src {
                if let Some(rest) = src.strip_prefix("local_") {
                    if let Ok(off) = i32::from_str_radix(rest, 16) {
                        if off > 0 { param_offsets.insert(off); }
                    }
                }
            }
            if let Some(dst) = &insn.dst {
                if let Some(rest) = dst.strip_prefix("local_") {
                    if let Ok(off) = i32::from_str_radix(rest, 16) {
                        if off > 0 { param_offsets.insert(off); }
                    }
                }
            }
        }
    }

    // Common calling convention for stdcall: params at [ebp+8], [ebp+C], etc.
    let params: Vec<String> = param_offsets.iter()
        .filter(|&&off| off >= 8) // returnaddr=4, saved ebp=8, first param=0xC in some CVs
        .enumerate()
        .map(|(i, _off)| format!("int param_{}", i + 1))
        .collect();

    if params.is_empty() { "void".to_string() } else { params.join(", ") }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Utilities
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn sanitize_c_ident(s: &str) -> String {
    let mut out = String::with_capacity(s.len());
    for (i, c) in s.chars().enumerate() {
        if c.is_alphanumeric() || c == '_' {
            out.push(c);
        } else if i == 0 {
            out.push('_');
        } else {
            out.push('_');
        }
    }
    // Avoid starting with digit
    if out.starts_with(|c: char| c.is_ascii_digit()) {
        out.insert(0, '_');
    }
    if out.is_empty() { out.push_str("unknown"); }
    out
}

fn escape_c_string(s: &str) -> String {
    s.replace('\\', "\\\\")
        .replace('"', "\\\"")
        .replace('\n', "\\n")
        .replace('\r', "\\r")
        .replace('\t', "\\t")
        .replace('\0', "\\0")
}

fn truncate(s: &str, max: usize) -> String {
    if s.len() <= max { s.to_string() }
    else { format!("{}...", &s[..max]) }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Expression Folding pass for C Output
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn apply_expression_folding_c(func: &mut JsonFunction, resolved: &ResolvedData) {
    loop {
        let mut use_count: std::collections::HashMap<String, usize> = std::collections::HashMap::new();
        let mut defs: std::collections::HashMap<String, String> = std::collections::HashMap::new();
        let mut def_idx: std::collections::HashMap<String, (usize, usize)> = std::collections::HashMap::new();

        // Pass 1: count uses & collect foldable definitions
        for (b_idx, block) in func.blocks.iter().enumerate() {
            for (i_idx, insn) in block.instructions.iter().enumerate() {
                for s in &insn.src {
                    *use_count.entry(s.clone()).or_insert(0) += 1;
                }
                if let Some(dst) = &insn.dst {
                    if !dst.is_empty() && dst.contains("_") {
                        let rhs = generate_rhs_c(insn, resolved);
                        if !rhs.is_empty() {
                            defs.insert(dst.clone(), rhs);
                            def_idx.insert(dst.clone(), (b_idx, i_idx));
                        }
                    }
                }
            }
        }

        let mut folded_any = false;
        let mut to_remove: std::collections::HashSet<(usize, usize)> = std::collections::HashSet::new();

        // Pass 2: Substitute single uses
        for (b_idx, block) in func.blocks.iter_mut().enumerate() {
            for (i_idx, insn) in block.instructions.iter_mut().enumerate() {
                for s in &mut insn.src {
                    if use_count.get(s) == Some(&1) {
                        if let Some(rhs) = defs.get(s) {
                            if let Some(&(def_b, def_i)) = def_idx.get(s) {
                                let safe_to_fold = (def_b == b_idx && def_i < i_idx) || (def_b != b_idx);
                                if safe_to_fold {
                                    *s = if rhs.starts_with('(') && rhs.ends_with(')') {
                                        rhs.clone()
                                    } else {
                                        format!("({})", rhs)
                                    };
                                    to_remove.insert((def_b, def_i));
                                    folded_any = true;
                                }
                            }
                        }
                    }
                }
            }
        }

        if !folded_any { break; }

        let mut remove_vec: Vec<_> = to_remove.into_iter().collect();
        remove_vec.sort_by(|a, b| match b.0.cmp(&a.0) {
            std::cmp::Ordering::Equal => b.1.cmp(&a.1),
            other => other,
        });

        for (b, i) in remove_vec {
            if b < func.blocks.len() && i < func.blocks[b].instructions.len() {
                func.blocks[b].instructions.remove(i);
            }
        }
    }
}

fn generate_rhs_c(insn: &JsonInstruction, resolved: &ResolvedData) -> String {
    let resolve = |s: &str| resolve_operand_str(s, resolved);
    let src: Vec<String> = insn.src.iter().map(|s| prettify_operand(&resolve(s))).collect();
    let q = "?".to_string();
    let s0 = src.get(0).cloned().unwrap_or_else(|| q.clone());
    let s1 = src.get(1).cloned().unwrap_or_else(|| q.clone());

    match insn.op.as_str() {
        "assign" | "movzx" | "movsx" => s0,
        "add" => format!("{} + {}", s0, s1),
        "sub" => format!("{} - {}", s0, s1),
        "mul" => format!("{} * {}", s0, s1),
        "div" => format!("{} / {}", s0, s1),
        "and" => format!("{} & {}", s0, s1),
        "or"  => format!("{} | {}", s0, s1),
        "xor" => format!("{} ^ {}", s0, s1),
        "not" => format!("~{}", s0),
        "shl" => format!("{} << {}", s0, s1),
        "shr" => format!("(unsigned){} >> {}", s0, s1),
        "sar" => format!("(signed){} >> {}", s0, s1),
        "lea" => format!("&{}", s0),
        "call" => insn.string_ref.clone().unwrap_or_else(|| "call(...)".to_string()),
        _ => String::new(),
    }
}
