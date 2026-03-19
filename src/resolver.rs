use fnv::FnvHashMap;
use object::{Object, ObjectSection, ObjectSymbol, SectionKind};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED RESOLVER - Strings, Imports, Exports extraction
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[derive(Debug, Default)]
pub struct ResolvedData {
    /// VA → string content (from .rdata, .data sections)
    pub strings: FnvHashMap<u64, String>,
    /// VA → "dll!FunctionName" (from PE import tables)
    pub imports: FnvHashMap<u64, String>,
    /// VA → export name (from PE export table)
    pub exports: FnvHashMap<u64, String>,
    /// Combined: VA → human name (imports + exports + symbols)
    pub names: FnvHashMap<u64, String>,
    /// VA of a pointer -> String it points to (Medium Confidence Injection)
    pub ptr_to_string: FnvHashMap<u64, String>,
}

impl ResolvedData {
    pub fn resolve_addr(&self, addr: u64) -> Option<&str> {
        self.names.get(&addr).map(|s| s.as_str())
    }
    pub fn resolve_string(&self, addr: u64) -> Option<&str> {
        self.strings.get(&addr).map(|s| s.as_str())
    }
}

/// Build all resolved data from the PE binary
pub fn build_resolved_data(mmap: &[u8], obj: &object::File<'_>) -> ResolvedData {
    let mut data = ResolvedData::default();
    let image_base = obj.relative_address_base();
    let is_64bit = matches!(obj.architecture(), object::Architecture::X86_64);

    // 1) Extract exports (DLL exported functions)
    extract_exports(obj, &mut data);

    // 2) Extract imports via PE parsing
    extract_imports_raw(mmap, image_base, is_64bit, &mut data);

    // 3) Extract named symbols
    extract_symbols(obj, &mut data);

    // 4) Extract strings from data sections
    extract_strings(obj, &mut data);

    // 5) Build combined name table
    for (&addr, name) in &data.exports {
        data.names.insert(addr, name.clone());
    }
    for (&addr, name) in &data.imports {
        data.names.insert(addr, name.clone());
    }

    // 6) Precompute Static Pointer-to-String values for Medium Confidence Decompilation
    extract_string_pointers(obj, is_64bit, &mut data);

    println!("[+] Resolved: {} strings, {} static pointers to strings, {} imports, {} exports",
        data.strings.len(), data.ptr_to_string.len(), data.imports.len(), data.exports.len());

    data
}

/// Extract PE exports (for DLLs)
fn extract_exports(obj: &object::File<'_>, data: &mut ResolvedData) {
    if let Ok(exports) = obj.exports() {
        for exp in exports {
            let name = String::from_utf8_lossy(exp.name()).to_string();
            if !name.is_empty() {
                data.exports.insert(exp.address(), name);
            }
        }
    }
}

/// Extract named symbols from the symbol table
fn extract_symbols(obj: &object::File<'_>, data: &mut ResolvedData) {
    for sym in obj.symbols() {
        if let Ok(name) = sym.name() {
            if !name.is_empty() && sym.address() != 0 {
                // Ignore section symbols
                if name.starts_with(".text") || name.starts_with(".data") || name == ".rdata" { continue; }
                data.names.entry(sym.address()).or_insert_with(|| name.to_string());
            }
        }
    }
}

/// Extract imports by parsing the PE import directory from raw bytes
fn extract_imports_raw(mmap: &[u8], image_base: u64, is_64bit: bool, data: &mut ResolvedData) {
    // Find the import directory from PE header
    let pe_offset = if mmap.len() > 0x3C + 4 {
        u32::from_le_bytes([mmap[0x3C], mmap[0x3D], mmap[0x3E], mmap[0x3F]]) as usize
    } else {
        return;
    };

    if pe_offset + 4 > mmap.len() { return; }
    let sig = &mmap[pe_offset..pe_offset + 4];
    if sig != b"PE\x00\x00" { return; }

    let opt_offset = pe_offset + 24;
    let (import_dir_rva, _import_dir_size, ptr_size) = if is_64bit {
        if opt_offset + 120 > mmap.len() { return; }
        let rva = u32::from_le_bytes([
            mmap[opt_offset + 112], mmap[opt_offset + 113],
            mmap[opt_offset + 114], mmap[opt_offset + 115],
        ]);
        let sz = u32::from_le_bytes([
            mmap[opt_offset + 116], mmap[opt_offset + 117],
            mmap[opt_offset + 118], mmap[opt_offset + 119],
        ]);
        (rva, sz, 8usize)
    } else {
        if opt_offset + 104 > mmap.len() { return; }
        let rva = u32::from_le_bytes([
            mmap[opt_offset + 96], mmap[opt_offset + 97],
            mmap[opt_offset + 98], mmap[opt_offset + 99],
        ]);
        let sz = u32::from_le_bytes([
            mmap[opt_offset + 100], mmap[opt_offset + 101],
            mmap[opt_offset + 102], mmap[opt_offset + 103],
        ]);
        (rva, sz, 4usize)
    };

    if import_dir_rva == 0 { return; }

    // We need an RVA-to-file-offset converter using section table
    let sections = parse_section_table(mmap, pe_offset, is_64bit);

    let rva_to_offset = |rva: u32| -> Option<usize> {
        for (sec_rva, sec_vsize, sec_raw, sec_rawsize) in &sections {
            if rva >= *sec_rva && rva < *sec_rva + *sec_vsize {
                let off = (rva - *sec_rva) as usize + *sec_raw as usize;
                if off < *sec_raw as usize + *sec_rawsize as usize && off < mmap.len() {
                    return Some(off);
                }
            }
        }
        None
    };

    // Parse import descriptors
    let Some(import_offset) = rva_to_offset(import_dir_rva) else { return };

    let mut desc_off = import_offset;
    loop {
        if desc_off + 20 > mmap.len() { break; }

        let int_rva = read_u32(mmap, desc_off);       // OriginalFirstThunk
        let name_rva = read_u32(mmap, desc_off + 12);  // DLL name
        let iat_rva = read_u32(mmap, desc_off + 16);   // FirstThunk (IAT)

        // End marker: all zeros
        if int_rva == 0 && name_rva == 0 && iat_rva == 0 { break; }

        // Read DLL name
        let dll_name = if let Some(name_off) = rva_to_offset(name_rva) {
            read_cstring(mmap, name_off)
        } else {
            String::from("?")
        };
        let short_dll = dll_name
            .trim_end_matches(".dll").trim_end_matches(".DLL")
            .trim_end_matches(".Dll")
            .to_string();

        let thunk_rva = if int_rva != 0 { int_rva } else { iat_rva };
        let Some(mut thunk_off) = rva_to_offset(thunk_rva) else {
            desc_off += 20;
            continue;
        };

        let mut iat_slot_rva = iat_rva;

        loop {
            if thunk_off + ptr_size > mmap.len() { break; }

            let thunk_val = if is_64bit {
                read_u64(mmap, thunk_off)
            } else {
                read_u32(mmap, thunk_off) as u64
            };

            if thunk_val == 0 { break; }

            // Check ordinal bit
            let ordinal_flag = if is_64bit { 1u64 << 63 } else { 1u64 << 31 };
            if thunk_val & ordinal_flag != 0 {
                let ordinal = (thunk_val & 0xFFFF) as u16;
                let iat_va = image_base + iat_slot_rva as u64;
                data.imports.insert(iat_va, format!("{}!ord_{}", short_dll, ordinal));
            } else {
                // Hint-Name entry: 2 bytes hint + null-terminated name
                let hint_rva = thunk_val as u32;
                if let Some(hint_off) = rva_to_offset(hint_rva) {
                    if hint_off + 2 < mmap.len() {
                        let func_name = read_cstring(mmap, hint_off + 2);
                        if !func_name.is_empty() {
                            let iat_va = image_base + iat_slot_rva as u64;
                            data.imports.insert(iat_va, format!("{}!{}", short_dll, func_name));
                        }
                    }
                }
            }

            thunk_off += ptr_size;
            iat_slot_rva += ptr_size as u32;
        }

        desc_off += 20;
    }
}

/// Parse the PE section table to enable RVA→file offset conversion
fn parse_section_table(mmap: &[u8], pe_offset: usize, is_64bit: bool) -> Vec<(u32, u32, u32, u32)> {
    let mut sections = Vec::new();

    let coff_offset = pe_offset + 4;
    if coff_offset + 20 > mmap.len() { return sections; }
    let num_sections = u16::from_le_bytes([mmap[coff_offset + 2], mmap[coff_offset + 3]]) as usize;
    let opt_header_size = u16::from_le_bytes([mmap[coff_offset + 16], mmap[coff_offset + 17]]) as usize;

    let section_table_offset = coff_offset + 20 + opt_header_size;

    for i in 0..num_sections {
        let sec_off = section_table_offset + i * 40;
        if sec_off + 40 > mmap.len() { break; }

        let virtual_size = read_u32(mmap, sec_off + 8);
        let virtual_addr = read_u32(mmap, sec_off + 12);
        let raw_size = read_u32(mmap, sec_off + 16);
        let raw_ptr = read_u32(mmap, sec_off + 20);

        sections.push((virtual_addr, virtual_size, raw_ptr, raw_size));
    }

    sections
}

/// Extract strings from .rdata, .data, and other data sections
fn extract_strings(obj: &object::File<'_>, data: &mut ResolvedData) {
    for section in obj.sections() {
        let kind = section.kind();
        if kind == SectionKind::Text { continue; }
        // Only scan data-like sections
        if kind != SectionKind::ReadOnlyData && kind != SectionKind::Data
            && kind != SectionKind::ReadOnlyString && kind != SectionKind::UninitializedData
        {
            continue;
        }

        let Ok(sec_data) = section.data() else { continue };
        if sec_data.is_empty() { continue; }
        let sec_addr = section.address();

        // Scan for ASCII strings
        scan_ascii_strings(sec_data, sec_addr, &mut data.strings);

        // Scan for UTF-16LE strings
        scan_utf16_strings(sec_data, sec_addr, &mut data.strings);
    }
}

/// Scan for null-terminated ASCII strings (min length 4)
fn scan_ascii_strings(data: &[u8], base: u64, out: &mut FnvHashMap<u64, String>) {
    let mut i = 0;
    while i < data.len() {
        let start = i;
        while i < data.len() && is_printable_ascii(data[i]) {
            i += 1;
        }
        let len = i - start;
        if len >= 4 && i < data.len() && data[i] == 0 {
            let s = String::from_utf8_lossy(&data[start..i]).to_string();
            out.insert(base + start as u64, s);
            i += 1;
        } else {
            i = start + 1;
        }
    }
}

/// Scan for null-terminated UTF-16LE strings (min length 4 chars)
fn scan_utf16_strings(data: &[u8], base: u64, out: &mut FnvHashMap<u64, String>) {
    let mut i = 0;
    while i + 3 < data.len() {
        // Check if this looks like start of UTF-16
        if !(is_printable_ascii(data[i]) && data[i + 1] == 0) {
            i += 1;
            continue;
        }

        let start = i;
        let mut chars = Vec::new();

        while i + 1 < data.len() {
            if data[i] == 0 && data[i + 1] == 0 { break; } // Null terminator
            if data[i + 1] != 0 { break; } // Not ASCII in UTF-16
            if !is_printable_ascii(data[i]) && data[i] != 0x0A && data[i] != 0x0D && data[i] != 0x09 {
                break;
            }
            chars.push(data[i] as char);
            i += 2;
        }

        if chars.len() >= 4 && i + 1 < data.len() && data[i] == 0 && data[i + 1] == 0 {
            let s = chars.into_iter().collect::<String>();
            // Don't overwrite existing ASCII string at same addr
            out.entry(base + start as u64).or_insert_with(|| format!("L\"{}\"", s));
            i += 2;
        } else {
            i = start + 1;
        }
    }
}

#[inline]
fn is_printable_ascii(b: u8) -> bool {
    (0x20..=0x7E).contains(&b) || b == 0x09 || b == 0x0A || b == 0x0D
}

fn read_u32(data: &[u8], offset: usize) -> u32 {
    if offset + 4 <= data.len() {
        u32::from_le_bytes([data[offset], data[offset+1], data[offset+2], data[offset+3]])
    } else {
        0
    }
}

fn read_u64(data: &[u8], offset: usize) -> u64 {
    if offset + 8 <= data.len() {
        u64::from_le_bytes([
            data[offset], data[offset+1], data[offset+2], data[offset+3],
            data[offset+4], data[offset+5], data[offset+6], data[offset+7],
        ])
    } else {
        0
    }
}

fn read_cstring(data: &[u8], offset: usize) -> String {
    let mut end = offset;
    while end < data.len() && data[end] != 0 { end += 1; }
    String::from_utf8_lossy(&data[offset..end]).to_string()
}

/// Medium Confidence Pre-computation: Scan memory for pointers to known strings
fn extract_string_pointers(obj: &object::File<'_>, is_64bit: bool, data: &mut ResolvedData) {
    let ptr_size = if is_64bit { 8 } else { 4 };
    
    for section in obj.sections() {
        let kind = section.kind();
        // We scan ReadOnlyData, Data, and Text since jump tables/pointer arrays could be anywhere
        if kind != SectionKind::ReadOnlyData && kind != SectionKind::Data 
            && kind != SectionKind::Text && kind != SectionKind::UninitializedData {
            continue;
        }

        if let Ok(sec_data) = section.data() {
            let sec_addr = section.address();
            let mut i = 0;
            
            while i + ptr_size <= sec_data.len() {
                let ptr_val = if is_64bit {
                    u64::from_le_bytes(sec_data[i..i+8].try_into().unwrap_or([0; 8]))
                } else {
                    u32::from_le_bytes(sec_data[i..i+4].try_into().unwrap_or([0; 4])) as u64
                };
                
                if ptr_val > 0 {
                    if let Some(s) = data.strings.get(&ptr_val) {
                        data.ptr_to_string.insert(sec_addr + i as u64, s.clone());
                    }
                }
                
                i += ptr_size;
            }
        }
    }
}
