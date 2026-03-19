use memmap2::Mmap;
use object::{File, Object, ObjectSection, ObjectSymbol, SectionKind, SymbolKind};
use rayon::prelude::*;
use std::fs::File as StdFile;
use std::sync::atomic::{AtomicUsize, Ordering};
use zydis::{Decoder, MachineMode, StackWidth, NoOperands};

/// Representa uma unidade de código a ser analisada (Função ou Seção).
#[derive(Debug, Clone)]
struct CodeUnit {
    name: String,
    address: u64,
    size: u64,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: deepbleed <path_to_pe_file>");
        std::process::exit(1);
    }

    let path = &args[1];
    println!("[*] DEEP_BLEED Engine v0.1.0 starting...");
    println!("[*] Mapping: {}", path);

    // Mapeamento de memória de alta performance (Zero-copy)
    let file = StdFile::open(path)?;
    let mmap = unsafe { Mmap::map(&file)? };

    // Parsing do binário (PE/ELF/Mach-O suportados pelo crate 'object')
    let obj = File::parse(&*mmap)?;
    
    // Determinação precisa do modo de CPU
    let (machine_mode, stack_width) = match obj.architecture() {
        object::Architecture::X86_64 => (MachineMode::LONG_64, StackWidth::_64),
        object::Architecture::I386 => (MachineMode::LEGACY_32, StackWidth::_32),
        _ => return Err("Unsupported architecture. X86/X64 only.".into()),
    };

    println!("[+] Target Arch: {:?}", obj.architecture());

    // 1. Identificação de "Code Units" (Funções, Exportações e Seções)
    let mut code_units = Vec::new();

    // Extrair funções de símbolos definidos
    for symbol in obj.symbols() {
        if symbol.kind() == SymbolKind::Text && symbol.size() > 0 {
            code_units.push(CodeUnit {
                name: symbol.name().unwrap_or("sym_func").to_string(),
                address: symbol.address(),
                size: symbol.size(),
            });
        }
    }

    // Adicionar Exportações (Crítico para PEs sem símbolos de debug)
    if let Ok(exports) = obj.exports() {
        for export in exports {
            code_units.push(CodeUnit {
                name: format!("export:{}", String::from_utf8_lossy(export.name())),
                address: export.address(),
                size: 0, // Tamanho desconhecido via export table
            });
        }
    }

    // Seções executáveis para varredura completa
    let exec_sections: Vec<_> = obj.sections()
        .filter(|s| s.kind() == SectionKind::Text)
        .collect();

    for sec in &exec_sections {
        code_units.push(CodeUnit {
            name: format!(".section:{}", sec.name().unwrap_or("?")),
            address: sec.address(),
            size: sec.size(),
        });
    }

    println!("[*] Identified {} code units for parallel processing.", code_units.len());

    let total_inst = AtomicUsize::new(0);

    // 2. Disassembling Massivo Paralelo
    code_units.par_iter().for_each(|unit| {
        // Encontrar os dados brutos
        let data = obj.sections()
            .find(|s| unit.address >= s.address() && unit.address < s.address() + s.size())
            .and_then(|s| {
                let offset = (unit.address - s.address()) as usize;
                let section_data = s.data().ok()?;
                let end = if unit.size > 0 {
                    (offset + unit.size as usize).min(section_data.len())
                } else {
                    section_data.len()
                };
                Some(&section_data[offset..end])
            });

        if let Some(raw_code) = data {
            let decoder = Decoder::new(machine_mode, stack_width)
                .expect("Critical: Failed to initialize Zydis decoder");

            let mut local_count = 0;
            
            // Sweep linear
            for item in decoder.decode_all::<NoOperands>(raw_code, unit.address) {
                if item.is_ok() {
                    local_count += 1;
                }
            }

            total_inst.fetch_add(local_count, Ordering::Relaxed);
            
            if local_count > 0 && unit.size > 0 {
                // Notifica o processamento de funções identificadas (evita spam de seções massivas)
                println!(
                    "[+] Worker Thread | Unit: {:<30} | Inst: {:<8} | VA: 0x{:012X}",
                    unit.name, local_count, unit.address
                );
            }
        }
    });

    println!("--------------------------------------------------");
    println!("[!] Paralelismo concluído com sucesso.");
    println!("[!] Instruções Totais Processadas: {}", total_inst.load(Ordering::SeqCst));

    Ok(())
}
