use crate::resolver::ResolvedData;
use crate::types::*;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED CODEGEN - IR → C Pseudocode
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

pub fn generate_c(output: &JsonOutput, resolved: &ResolvedData) -> String {
    let mut c = String::with_capacity(1024 * 1024);

    // File header
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
        output.stats.total_functions, output.stats.user_functions, output.stats.external_functions));
    c.push_str(" * ═══════════════════════════════════════════════════\n");
    c.push_str(" */\n\n");
    c.push_str("#include <windows.h>\n#include <stdio.h>\n#include <stdlib.h>\n#include <string.h>\n\n");

    // Forward declarations
    c.push_str("/* ═══ Forward Declarations ═══ */\n");
    for func in &output.functions {
        let fname = resolve_func_name(&func.name, &func.address, resolved);
        c.push_str(&format!("void {}(); /* {} @ {} */\n", fname, func.kind, func.address));
    }
    c.push_str("\n");

    // Generate each function
    for func in &output.functions {
        generate_function(&mut c, func, resolved);
    }

    c
}

fn generate_function(c: &mut String, func: &JsonFunction, resolved: &ResolvedData) {
    let fname = resolve_func_name(&func.name, &func.address, resolved);

    c.push_str("/* ═══════════════════════════════════════════════════\n");
    c.push_str(&format!(" * {} @ {} ({})\n", fname, func.address, func.kind));
    c.push_str(&format!(" * Blocks: {} | SSA vars: {}\n", func.blocks.len(), func.ssa_vars.len()));
    c.push_str(" * ═══════════════════════════════════════════════════ */\n");

    // Guess calling convention
    let cc = if func.kind == "MAIN" { "int __cdecl" } else { "void __stdcall" };
    let params = if func.kind == "MAIN" {
        "(int argc, char** argv, char** envp)"
    } else {
        "()"
    };

    c.push_str(&format!("{} {}{}  {{\n", cc, fname, params));

    // Collect local variables from SSA vars
    if !func.ssa_vars.is_empty() {
        c.push_str("    /* Local variables */\n");
        let mut declared = std::collections::HashSet::new();
        for var in &func.ssa_vars {
            let base = &var.register;
            if !declared.contains(base) {
                c.push_str(&format!("    int {};  /* {} versions */\n", base, 
                    func.ssa_vars.iter().filter(|v| v.register == *base).count()));
                declared.insert(base.clone());
            }
        }
        c.push_str("\n");
    }

    // Generate each block
    for block in &func.blocks {
        generate_block(c, block, resolved);
    }

    c.push_str("}\n\n");
}

fn generate_block(c: &mut String, block: &JsonBlock, resolved: &ResolvedData) {
    c.push_str(&format!("{}:  /* {} */\n", block.id, block.address));

    for insn in &block.instructions {
        let line = instruction_to_c(insn, resolved);
        c.push_str(&format!("    {};\n", line));
    }
    c.push('\n');
}

fn instruction_to_c(insn: &JsonInstruction, resolved: &ResolvedData) -> String {
    let resolve_operand = |s: &str| -> String {
        if let Some(addr_str) = s.strip_prefix("gvar_") {
            if let Ok(addr) = u64::from_str_radix(addr_str, 16) {
                if let Some(name) = resolved.resolve_addr(addr) {
                    return format!("/* {} */ {}", s, name);
                }
                if let Some(string) = resolved.resolve_string(addr) {
                    return format!("\"{}\"", escape_c_string(string));
                }
            }
        }
        if let Some(hex_str) = s.strip_prefix("0x") {
            if let Ok(addr) = u64::from_str_radix(hex_str, 16) {
                if let Some(string) = resolved.resolve_string(addr) {
                    return format!("\"{}\"", escape_c_string(string));
                }
                if let Some(name) = resolved.resolve_addr(addr) {
                    return name.to_string();
                }
            }
        }
        s.to_string()
    };

    let dst = insn.dst.as_deref().map(|d| resolve_operand(d)).unwrap_or_default();
    let src: Vec<String> = insn.src.iter().map(|s| resolve_operand(s)).collect();
    let q = "?".to_string();
    let s0 = src.get(0).unwrap_or(&q);
    let s1 = src.get(1).unwrap_or(&q);

    match insn.op.as_str() {
        "assign" => format!("{} = {}", dst, s0),
        "add" => format!("{} = {} + {}", dst, s0, s1),
        "sub" => format!("{} = {} - {}", dst, s0, s1),
        "mul" => format!("{} = {} * {}", dst, s0, s1),
        "div" => format!("{} = {} / {}", dst, s0, s1),
        "and" => format!("{} = {} & {}", dst, s0, s1),
        "or"  => format!("{} = {} | {}", dst, s0, s1),
        "xor" => format!("{} = {} ^ {}", dst, s0, s1),
        "not" => format!("{} = ~{}", dst, s0),
        "shl" => format!("{} = {} << {}", dst, s0, s1),
        "shr" => format!("{} = {} >> {}", dst, s0, s1),
        "sar" => format!("{} = (signed){} >> {}", dst, s0, s1),
        "load" => format!("{} = *{}", dst, s0),
        "store" => format!("*{} = {}", dst, s0),
        "lea" => format!("{} = &{}", dst, s0),
        "call" => {
            let resolved_target = resolve_call_target(s0, resolved);
            format!("{}()", resolved_target)
        }
        "jump" => format!("goto bb_{}", s0.trim_start_matches("0x")),
        "cond_jump" => {
            let c_cond = condition_to_c(s1);
            format!("if ({}) goto bb_{}", c_cond, s0.trim_start_matches("0x"))
        }
        "ret" => "return".to_string(),
        "push" => format!("PUSH({})", s0),
        "pop" => format!("{} = POP()", dst),
        "cmp" => {
            let meta = if let Some(ref m) = insn.metadata {
                m.ascii.as_ref().map(|a| format!("  /* '{}' */", a)).unwrap_or_default()
            } else { String::new() };
            format!("CMP({}, {}){}", s0, s1, meta)
        }
        "test" => format!("TEST({}, {})", s0, s1),
        "movzx" => format!("{} = (unsigned){}", dst, s0),
        "movsx" => format!("{} = (signed){}", dst, s0),
        "movabs" => format!("{} = {}", dst, s0),
        "unknown" => format!("__asm {{ {} }}", s0),
        op if op.starts_with("set") => {
            let cond = op.trim_start_matches("set");
            format!("{} = (flags & {})", dst, cond.to_uppercase())
        }
        _ => format!("/* {} */ {}", insn.op, src.join(", ")),
    }
}

/// Resolve a call target address to a human-readable name
fn resolve_call_target(target: &str, resolved: &ResolvedData) -> String {
    // Try to parse as hex address
    let addr_str = target.trim_start_matches("0x").trim_start_matches("0X");
    if let Ok(addr) = u64::from_str_radix(addr_str, 16) {
        // Check imports (IAT indirect calls)
        if let Some(name) = resolved.resolve_addr(addr) {
            return name.to_string();
        }
        // Check strings (unlikely but possible)
        if let Some(string) = resolved.resolve_string(addr) {
            return format!("/* str: \"{}\" */", escape_c_string(string));
        }
        return format!("sub_{:X}", addr);
    }

    // Already a resolved name or gvar
    if target.starts_with("gvar_") {
        if let Some(hex) = target.strip_prefix("gvar_") {
            if let Ok(addr) = u64::from_str_radix(hex, 16) {
                if let Some(name) = resolved.resolve_addr(addr) {
                    return format!("[{}]", name);
                }
            }
        }
    }

    target.to_string()
}

/// Resolve function name using exports
fn resolve_func_name(name: &str, addr_str: &str, resolved: &ResolvedData) -> String {
    // Try to resolve via exports
    let hex = addr_str.trim_start_matches("0x").trim_start_matches("0X");
    if let Ok(addr) = u64::from_str_radix(hex, 16) {
        if let Some(export_name) = resolved.resolve_addr(addr) {
            // Clean up export name for C identifier
            return sanitize_c_ident(export_name);
        }
    }
    sanitize_c_ident(name)
}

fn sanitize_c_ident(s: &str) -> String {
    s.chars()
        .map(|c| if c.is_alphanumeric() || c == '_' { c } else { '_' })
        .collect()
}

fn escape_c_string(s: &str) -> String {
    s.replace('\\', "\\\\")
        .replace('"', "\\\"")
        .replace('\n', "\\n")
        .replace('\r', "\\r")
        .replace('\t', "\\t")
}

fn condition_to_c(cond: &str) -> &str {
    match cond {
        "Z"   => "ZF /* == */",
        "NZ"  => "!ZF /* != */",
        "B"   => "CF /* < unsigned */",
        "NB"  => "!CF /* >= unsigned */",
        "BE"  => "CF||ZF /* <= unsigned */",
        "NBE" => "!CF&&!ZF /* > unsigned */",
        "L"   => "SF!=OF /* < signed */",
        "NL"  => "SF==OF /* >= signed */",
        "LE"  => "ZF||SF!=OF /* <= signed */",
        "NLE" => "!ZF&&SF==OF /* > signed */",
        "S"   => "SF /* negative */",
        "NS"  => "!SF /* positive */",
        "O"   => "OF /* overflow */",
        "NO"  => "!OF /* no overflow */",
        "P"   => "PF /* parity */",
        "NP"  => "!PF /* no parity */",
        _     => cond,
    }
}
