use crate::lifter::*;
use crate::types::*;
use fnv::{FnvHashMap, FnvHashSet};
use object::Object;
use zydis::{Decoder, MachineMode, Mnemonic, StackWidth, VisibleOperands};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED ENTRY POINT HUNTER - Surgical main() localization
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Known CRT / external library function name patterns
const EXTERNAL_PATTERNS: &[&str] = &[
    "__security_init_cookie", "__security_check_cookie",
    "__scrt_common", "__scrt_exe", "__scrt_initialize",
    "_CRT_INIT", "_initterm", "_initterm_e",
    "__acrt_", "_cexit", "_exit", "_c_exit",
    "__stdio_common", "__std_type_info",
    "_seh_filter", "__C_specific_handler",
    "__report_rangecheckfailure",
    "_guard_dispatch_icall", "_guard_check_icall",
    "__GSHandlerCheck",
    "memset", "memcpy", "memmove", "memcmp",
    "strlen", "strcmp", "strcpy", "strcat", "strncpy", "strncmp",
    "wcslen", "wcscpy", "wcsncpy",
    "malloc", "free", "calloc", "realloc",
    "printf", "fprintf", "sprintf", "snprintf",
    "scanf", "fscanf", "sscanf",
    "fopen", "fclose", "fread", "fwrite", "fseek", "ftell",
    "exit", "abort", "atexit",
    "GetLastError", "SetLastError",
    "GetProcAddress", "LoadLibrary", "GetModuleHandle",
    "HeapAlloc", "HeapFree", "HeapCreate",
    "VirtualAlloc", "VirtualFree", "VirtualProtect",
    "CreateFile", "CloseHandle", "ReadFile", "WriteFile",
    "ExitProcess", "TerminateProcess",
    "IsDebuggerPresent", "OutputDebugString",
    // --- MinGW & GCC specific ---
    "___chkstk", "_pei386", "_matherr", "__main", "__tls",
    "__tmainCRTStartup", "_mainCRTStartup", "WinMainCRTStartup",
    "__dyn_tls", "__mingw", "__cpu_features",
];

/// Known external DLL patterns
const EXTERNAL_DLLS: &[&str] = &[
    "msvcrt", "ucrtbase", "vcruntime", "api-ms-win",
    "kernel32", "ntdll", "user32", "advapi32", "ws2_32",
    "shell32", "ole32", "oleaut32", "gdi32", "comctl32",
    "msvcp", "concrt", "ucrtbased", "vcruntime",
];

/// Build set of known external/import addresses from PE import table
pub fn build_external_set(obj: &object::File<'_>) -> FnvHashSet<String> {
    let mut externals = FnvHashSet::default();

    if let Ok(imports) = obj.imports() {
        for import in imports {
            let lib_name = std::str::from_utf8(import.library()).unwrap_or("");
            let func_name = std::str::from_utf8(import.name()).unwrap_or("");

            let is_external = EXTERNAL_DLLS.iter().any(|dll| {
                lib_name.to_lowercase().contains(dll)
            }) || EXTERNAL_PATTERNS.iter().any(|pat| {
                func_name.contains(pat)
            });

            if is_external {
                externals.insert(func_name.to_string());
            }
        }
    }

    externals
}

pub fn is_likely_external(
    func_name: &str,
    _func_addr: u64,
    external_names: &FnvHashSet<String>,
) -> bool {
    if external_names.contains(func_name) {
        return true;
    }
    // Check prefix patterns
    for pat in EXTERNAL_PATTERNS {
        if func_name.contains(pat) {
            return true;
        }
    }
    // High confidence heuristics
    if func_name.starts_with("__") && func_name != "__main" { return true; }
    if func_name.starts_with("_") && (func_name.contains("CRT") || func_name.contains("pei386") || func_name.contains("chkstk")) { return true; }
    false
}

/// Entry point info extracted from PE header
pub struct EntryPointInfo {
    pub entry_rva: u64,
    pub entry_va: u64,
    pub image_base: u64,
    pub main_candidate: Option<u64>,
}

/// Find the AddressOfEntryPoint and attempt to locate main()
pub fn find_entry_and_main(
    obj: &object::File<'_>,
    mmap: &[u8],
    machine_mode: MachineMode,
    stack_width: StackWidth,
    text_base: u64,
    text_offset: usize,
    text_size: usize,
) -> EntryPointInfo {
    let entry_va = obj.entry();
    let image_base = obj.relative_address_base();
    let entry_rva = entry_va.saturating_sub(image_base);

    println!("[+] AddressOfEntryPoint (RVA): 0x{:X}", entry_rva);
    println!("[+] Entry VA: 0x{:X}", entry_va);
    println!("[+] Image Base: 0x{:X}", image_base);

    let main_candidate = tail_follow_to_main(
        mmap, entry_va, text_base, text_offset, text_size,
        machine_mode, stack_width,
    );

    if let Some(main_addr) = main_candidate {
        println!("[!] main() candidate found at: 0x{:X}", main_addr);
    } else {
        println!("[!] main() not identified, analyzing from entry point");
    }

    EntryPointInfo { entry_rva, entry_va, image_base, main_candidate }
}

/// Tail-Follow algorithm: follows CALL chain from entry point to find main()
///
/// Strategy:
/// - Disassemble from entry point
/// - Follow CALL targets linearly
/// - Look for the pattern: 3 argument setup (RCX/RDX/R8 or push x3) → CALL → ExitProcess
/// - The CALL target just before ExitProcess with 3-arg setup is main()
fn tail_follow_to_main(
    mmap: &[u8],
    entry_va: u64,
    text_base: u64,
    text_offset: usize,
    text_size: usize,
    machine_mode: MachineMode,
    stack_width: StackWidth,
) -> Option<u64> {
    let decoder = Decoder::new(machine_mode, stack_width).ok()?;
    let is_64bit = matches!(machine_mode, MachineMode::LONG_64);

    // Follow calls from entry point, up to 10 levels deep
    let mut addr_to_scan = entry_va;
    let mut visited: FnvHashSet<u64> = FnvHashSet::default();
    let mut best_main_candidate: Option<u64> = None;

    for _depth in 0..10 {
        if visited.contains(&addr_to_scan) { break; }
        visited.insert(addr_to_scan);

        if let Some(candidate) = scan_for_main_pattern(
            mmap, addr_to_scan, text_base, text_offset, text_size,
            &decoder, is_64bit,
        ) {
            best_main_candidate = Some(candidate);
            break;
        }

        // Follow the first CALL we find
        if let Some(first_call) = find_first_call(
            mmap, addr_to_scan, text_base, text_offset, text_size, &decoder,
        ) {
            addr_to_scan = first_call;
        } else {
            break;
        }
    }

    best_main_candidate
}

/// Scan a function for the argc/argv/envp → CALL main pattern
fn scan_for_main_pattern(
    mmap: &[u8],
    func_addr: u64,
    text_base: u64,
    text_offset: usize,
    text_size: usize,
    decoder: &Decoder,
    is_64bit: bool,
) -> Option<u64> {
    let func_file_offset = addr_to_file_offset(func_addr, text_base, text_offset)?;
    if func_file_offset >= mmap.len() { return None; }

    let max_scan = (text_size).min(mmap.len() - func_file_offset).min(2048);
    let code = &mmap[func_file_offset..func_file_offset + max_scan];

    let mut offset = 0;
    let mut arg_regs_set: FnvHashSet<Register> = FnvHashSet::default();
    let mut last_calls: Vec<(u64, u64)> = Vec::new(); // (call_addr, target)
    let mut push_count = 0u32;

    while offset < code.len() {
        let current_addr = func_addr + offset as u64;
        match decoder.decode_first::<VisibleOperands>(&code[offset..]) {
            Ok(Some(insn)) => {
                let insn_len = insn.length as usize;
                let mn = insn.mnemonic;
                let ops = insn.operands();

                if is_64bit {
                    // x64: look for moves into RCX, RDX, R8 (argc, argv, envp)
                    if (mn == Mnemonic::MOV || mn == Mnemonic::LEA) && ops.len() >= 2 {
                        if let zydis::ffi::DecodedOperandKind::Reg(reg) = &ops[0].kind {
                            let r = Lifter::get_register(*reg);
                            match r {
                                Register::RCX | Register::ECX => { arg_regs_set.insert(Register::RCX); }
                                Register::RDX | Register::EDX => { arg_regs_set.insert(Register::RDX); }
                                Register::R8 => { arg_regs_set.insert(Register::R8); }
                                _ => {}
                            }
                        }
                    }
                } else {
                    // x86: look for PUSH patterns (3 pushes before CALL)
                    if mn == Mnemonic::PUSH {
                        push_count += 1;
                    } else if mn != Mnemonic::CALL {
                        push_count = 0;
                    }
                }

                if mn == Mnemonic::CALL {
                    if let Some(target) = extract_call_target(&insn, current_addr) {
                        let has_3_args = if is_64bit {
                            arg_regs_set.len() >= 2 // RCX+RDX is enough, R8 is optional
                        } else {
                            push_count >= 3
                        };
                        last_calls.push((current_addr, target));
                        if has_3_args {
                            return Some(target);
                        }
                    }
                    arg_regs_set.clear();
                    push_count = 0;
                }

                if mn == Mnemonic::RET || mn == Mnemonic::JMP {
                    // If we haven't found the 3-arg pattern but found calls,
                    // return the last call as best guess
                    if let Some((_addr, target)) = last_calls.last() {
                        return Some(*target);
                    }
                    break;
                }

                offset += insn_len;
            }
            _ => { offset += 1; }
        }
    }

    None
}

/// Find the first CALL target from a function
fn find_first_call(
    mmap: &[u8],
    func_addr: u64,
    text_base: u64,
    text_offset: usize,
    text_size: usize,
    decoder: &Decoder,
) -> Option<u64> {
    let func_file_offset = addr_to_file_offset(func_addr, text_base, text_offset)?;
    if func_file_offset >= mmap.len() { return None; }

    let max_scan = (text_size).min(mmap.len() - func_file_offset).min(512);
    let code = &mmap[func_file_offset..func_file_offset + max_scan];

    let mut offset = 0;
    while offset < code.len() {
        let current_addr = func_addr + offset as u64;
        match decoder.decode_first::<VisibleOperands>(&code[offset..]) {
            Ok(Some(insn)) => {
                if insn.mnemonic == Mnemonic::CALL {
                    return extract_call_target(&insn, current_addr);
                }
                if insn.mnemonic == Mnemonic::JMP {
                    // tail-call: follow the JMP
                    return extract_call_target(&insn, current_addr);
                }
                offset += insn.length as usize;
            }
            _ => { offset += 1; }
        }
    }
    None
}

fn extract_call_target(insn: &zydis::Instruction<VisibleOperands>, addr: u64) -> Option<u64> {
    let ops = insn.operands();
    if ops.is_empty() { return None; }
    match &ops[0].kind {
        zydis::ffi::DecodedOperandKind::Imm(imm) => {
            let end = addr + insn.length as u64;
            if imm.is_relative {
                if imm.is_signed { Some((end as i64 + imm.value as i64) as u64) }
                else { Some(end + imm.value) }
            } else {
                Some(imm.value)
            }
        }
        _ => None,
    }
}

fn addr_to_file_offset(addr: u64, text_base: u64, text_offset: usize) -> Option<usize> {
    if addr >= text_base {
        Some(text_offset + (addr - text_base) as usize)
    } else {
        None
    }
}

/// Discover functions by analyzing call targets and building the call tree
pub fn discover_functions(
    call_targets: &FnvHashMap<u64, u32>,
    entry_info: &EntryPointInfo,
    external_names: &FnvHashSet<String>,
    leaders: &FnvHashSet<u64>,
) -> Vec<FunctionInfo> {
    let mut functions = Vec::new();

    // Entry point is always a function
    functions.push(FunctionInfo {
        address: entry_info.entry_va,
        name: "_start".to_string(),
        kind: FunctionKind::EntryPoint,
        block_addrs: Vec::new(),
    });

    // Main, if found
    if let Some(main_addr) = entry_info.main_candidate {
        functions.push(FunctionInfo {
            address: main_addr,
            name: "main".to_string(),
            kind: FunctionKind::Main,
            block_addrs: Vec::new(),
        });
    }

    // All call targets are potential functions
    for (&addr, &_count) in call_targets {
        if addr == entry_info.entry_va { continue; }
        if entry_info.main_candidate == Some(addr) { continue; }

        let name = format!("sub_{:X}", addr);
        let kind = if is_likely_external(&name, addr, external_names) {
            FunctionKind::ExternalLib
        } else {
            FunctionKind::User
        };

        functions.push(FunctionInfo {
            address: addr,
            name,
            kind,
            block_addrs: Vec::new(),
        });
    }

    // Assign leaders (basic block starts) to functions
    let mut sorted_func_addrs: Vec<u64> = functions.iter().map(|f| f.address).collect();
    sorted_func_addrs.sort();

    let mut sorted_leaders: Vec<u64> = leaders.iter().copied().collect();
    sorted_leaders.sort();

    for func in &mut functions {
        let func_start = func.address;
        // Find the next function start
        let next_func = sorted_func_addrs.iter()
            .find(|&&a| a > func_start)
            .copied()
            .unwrap_or(u64::MAX);

        // Collect leaders that belong to this function
        func.block_addrs = sorted_leaders.iter()
            .filter(|&&l| l >= func_start && l < next_func)
            .copied()
            .collect();
    }

    functions.sort_by_key(|f| f.address);
    functions
}
