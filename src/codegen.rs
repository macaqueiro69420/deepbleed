use crate::resolver::ResolvedData;
use crate::structurer::*;
use crate::types::*;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED CODEGEN v2 — Structured C Pseudocode Generator
//  Aggressive: if/else/while/do-while, no goto, no CMP/TEST exposed,
//  prologue/epilogue suppressed, call args inferred, types guessed.
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

const INDENT: &str = "    ";

pub fn generate_c(output: &JsonOutput, resolved: &ResolvedData) -> String {
    let mut c = String::with_capacity(4 * 1024 * 1024);

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
    c.push_str("#include <windows.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n");

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
            let hex = addr.trim_start_matches("0x");
            c.push_str(&format!("/* {} = \"{}\" */\n", addr, escape_c_string(&truncate(s, 80))));
            let _ = hex;
        }
        c.push('\n');
    }

    // ─── Forward declarations ───
    c.push_str("/* ═══ Forward Declarations ═══ */\n");
    for func in &output.functions {
        let fname = resolve_func_name(&func.name, &func.address, resolved);
        let ret_type = infer_return_type(&func.name, &fname);
        let params = infer_params(func, resolved);
        c.push_str(&format!("{} {}({}); /* {} @ {} */\n",
            ret_type, fname, params, func.kind, func.address));
    }
    c.push('\n');

    // ─── Generate each function ───
    for func in &output.functions {
        generate_function(&mut c, func, resolved);
    }

    c
}

fn generate_function(c: &mut String, func: &JsonFunction, resolved: &ResolvedData) {
    let fname = resolve_func_name(&func.name, &func.address, resolved);
    let ret_type = infer_return_type(&func.name, &fname);
    let params = infer_params(func, resolved);

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
    indent: usize,
}

impl<'a> EmitCtx<'a> {
    fn pad(&self) -> String {
        INDENT.repeat(self.indent)
    }
    fn indented(&self) -> EmitCtx<'a> {
        EmitCtx { resolved: self.resolved, indent: self.indent + 1 }
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
    let mut pending_call_args: Vec<String> = Vec::new();

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
                // standalone CMP/TEST — show as comparison comment
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

        // ── PUSH before call → collect as arg ──
        if insn.op == "push" {
            let arg = resolve_operand_str(insn.src.get(0).map(|s| s.as_str()).unwrap_or("?"), ctx.resolved);
            pending_call_args.push(arg);
            i += 1;
            continue;
        }

        // ── CALL — emit with accumulated args ──
        if insn.op == "call" {
            let target_raw = insn.src.get(0).map(|s| s.as_str()).unwrap_or("?");
            let target = resolve_call_target(target_raw, ctx.resolved);

            // args come in reverse (stack = LIFO)
            let args: Vec<String> = pending_call_args.drain(..).rev().collect();

            // Check if there's a following assign eax, eax that uses return value
            let ret_used = insns.get(i + 1)
                .map(|nx| nx.op == "assign" && nx.dst.as_deref().map(|d| d.contains("eax") || d.contains("rax")).unwrap_or(false))
                .unwrap_or(false);

            if ret_used {
                // Let the next assign consume the call's result
                c.push_str(&format!("{}{}_retval = {}({});\n",
                    pad,
                    sanitize_c_ident(&target),
                    target,
                    args.join(", ")));
            } else {
                c.push_str(&format!("{}{}({});\n", pad, target, args.join(", ")));
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

        // ── Flush pending push args if we reach a non-call non-push ──
        if !pending_call_args.is_empty() {
            for arg in pending_call_args.drain(..) {
                c.push_str(&format!("{}/* unused arg: {} */\n", pad, arg));
            }
        }

        // ── Generic instruction emission ──
        let line = instruction_to_c(insn, ctx.resolved);
        if !line.is_empty() {
            c.push_str(&format!("{}{};\n", pad, line));
        }

        i += 1;
    }

    // Flush remaining push args
    for arg in pending_call_args.drain(..) {
        c.push_str(&format!("{}/* unused arg: {} */\n", pad, arg));
    }
}

/// Look backwards from `idx` for the last assign to eax/rax
fn collect_eax_before(insns: &[JsonInstruction], idx: usize) -> Option<String> {
    for insn in insns[..idx].iter().rev() {
        if insn.op == "assign" || insn.op == "movzx" || insn.op == "movsx" {
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
                return format!("[{}]", sanitize_c_ident(name));
            }
        }
    }
    // SSA var that is a function pointer
    if target.contains('_') {
        return format!("(*(FARPROC*){})", target);
    }
    target.to_string()
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
