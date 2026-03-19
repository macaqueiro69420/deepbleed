use memmap2::Mmap;
use object::{File, Object, ObjectSection, SectionKind};
use rayon::prelude::*;
use std::fs::File as StdFile;
use std::sync::atomic::{AtomicUsize, Ordering};
use zydis::{Decoder, MachineMode, StackWidth, NoOperands};

/// Constante de granularidade para o paralelismo massivo.
/// Chunks de 16KB permitem que seções grandes sejam divididas entre todos os núcleos da CPU.
const CHUNK_SIZE: usize = 16 * 1024;

/// Representa uma fatia de código (Chunk) para processamento paralelo.
#[derive(Debug, Clone)]
struct CodeChunk {
    name: String,
    address: u64,
    offset: usize,
    size: usize,
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let args: Vec<String> = std::env::args().collect();
    if args.len() < 2 {
        eprintln!("Usage: deepbleed <path_to_pe_file>");
        std::process::exit(1);
    }

    let path = &args[1];
    println!("[*] DEEP_BLEED Engine v0.1.0 starting...");
    println!("[*] Hyper-Parallel Mode: ENABLED");

    // Mapeamento de memória de alta performance (Zero-copy)
    let file = StdFile::open(path)?;
    let mmap = unsafe { Mmap::map(&file)? };

    // Parsing do binário
    let obj = File::parse(&*mmap)?;
    
    // Determinação precisa do modo de CPU
    let (machine_mode, stack_width) = match obj.architecture() {
        object::Architecture::X86_64 => (MachineMode::LONG_64, StackWidth::_64),
        object::Architecture::I386 => (MachineMode::LEGACY_32, StackWidth::_32),
        _ => return Err("Unsupported architecture. X86/X64 only.".into()),
    };

    println!("[+] Target Arch: {:?}", obj.architecture());

    // 1. Fragmentação Massiva (Chunking)
    // Para garantir hiper-paralelismo, não processamos por seção, mas por pedaços fixos.
    let mut code_chunks = Vec::new();

    // Seções executáveis
    let exec_sections: Vec<_> = obj.sections()
        .filter(|s| s.kind() == SectionKind::Text)
        .collect();

    for sec in &exec_sections {
        let sec_data = sec.data()?;
        let sec_addr = sec.address();
        let sec_name = sec.name().unwrap_or("?");
        
        let mut current_pos = 0;
        while current_pos < sec_data.len() {
            let chunk_len = (sec_data.len() - current_pos).min(CHUNK_SIZE);
            code_chunks.push(CodeChunk {
                name: format!("{}:chunk_{:0X}", sec_name, current_pos),
                address: sec_addr + current_pos as u64,
                offset: sec.file_range().unwrap_or((0,0)).0 as usize + current_pos, // Usamos offset do arquivo
                size: chunk_len,
            });
            current_pos += chunk_len;
        }
    }

    println!("[*] Generated {} chunks for parallel execution across all CPU cores.", code_chunks.len());

    let total_inst = AtomicUsize::new(0);

    // 2. Disassembling Massivo Paralelo (Rayon)
    // Agora o Rayon terá centenas de pequenos jobs para distribuir entre todas as CPUs.
    code_chunks.par_iter().for_each(|chunk| {
        // Obter os bytes brutos do chunk diretamente do Mmap (Thread-safe)
        let end = chunk.offset + chunk.size;
        if let Some(raw_code) = mmap.get(chunk.offset..end) {
            
            // Cada Worker Thread reinicializa o Zydis (lock-free)
            let decoder = Decoder::new(machine_mode, stack_width)
                .expect("Critical: Failed to initialize Zydis decoder");

            let mut local_count = 0;
            
            // Sweep linear sincronizado por chunk
            // Nota técnica: x86 sincroniza sua instrução em poucos bytes mesmo se começarmos no meio.
            for item in decoder.decode_all::<NoOperands>(raw_code, chunk.address) {
                if item.is_ok() {
                    local_count += 1;
                }
            }

            total_inst.fetch_add(local_count, Ordering::Relaxed);
            
            // Feedback de progresso (opcional, pode ser barulhento em bins gigantes)
            // println!("[+] Worker [{:?}] | Processed {} instructions at 0x{:012X}", std::thread::current().id(), local_count, chunk.address);
        }
    });

    println!("--------------------------------------------------");
    println!("[!] Paralelismo Massivo concluído.");
    println!("[!] Instruções Totais Processadas: {}", total_inst.load(Ordering::SeqCst));

    Ok(())
}
