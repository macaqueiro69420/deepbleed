use std::collections::BTreeMap;
use serde::{Serialize, Deserialize};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED SIGNATURES - Function Prototype Reconstruction
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct FunctionSignature {
    pub name: String,
    pub ret_type: String,
    pub parameters: Vec<ParameterInfo>,
    pub calling_convention: CallingConvention,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ParameterInfo {
    pub name: String,
    pub ptype: String,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Serialize, Deserialize)]
pub enum CallingConvention {
    Stdcall,
    Cdecl,
    Fastcall,
    Unknown,
}

pub struct SignatureDatabase {
    pub sigs: BTreeMap<String, FunctionSignature>,
}

impl SignatureDatabase {
    pub fn new() -> Self {
        let mut sigs = BTreeMap::new();
        
        // Add some common Windows APIs
        add_winapi(&mut sigs, "CryptAcquireContextA", "BOOL", 
            &[("hProv", "HCRYPTPROV*"), ("szContainer", "LPCSTR"), ("szProvider", "LPCSTR"), ("dwProvType", "DWORD"), ("dwFlags", "DWORD")]);
        add_winapi(&mut sigs, "CryptReleaseContext", "BOOL", 
            &[("hProv", "HCRYPTPROV"), ("dwFlags", "DWORD")]);
        add_winapi(&mut sigs, "CryptCreateHash", "BOOL", 
            &[("hProv", "HCRYPTPROV"), ("Algid", "ALG_ID"), ("hKey", "HCRYPTKEY"), ("dwFlags", "DWORD"), ("phHash", "HCRYPTHASH*")]);
        add_winapi(&mut sigs, "CryptHashData", "BOOL", 
            &[("hHash", "HCRYPTHASH"), ("pbData", "BYTE*"), ("dwDataLen", "DWORD"), ("dwFlags", "DWORD")]);
        add_winapi(&mut sigs, "CryptGetHashParam", "BOOL", 
            &[("hHash", "HCRYPTHASH"), ("dwParam", "DWORD"), ("pbData", "BYTE*"), ("pdwDataLen", "DWORD*"), ("dwFlags", "DWORD")]);
        add_winapi(&mut sigs, "CryptDestroyHash", "BOOL", 
            &[("hHash", "HCRYPTHASH")]);
        add_winapi(&mut sigs, "MessageBoxA", "int", 
            &[("hWnd", "HWND"), ("lpText", "LPCSTR"), ("lpCaption", "LPCSTR"), ("uType", "UINT")]);
        add_winapi(&mut sigs, "CreateFileA", "HANDLE", 
            &[("lpFileName", "LPCSTR"), ("dwDesiredAccess", "DWORD"), ("dwShareMode", "DWORD"), ("lpSecurityAttributes", "LPSECURITY_ATTRIBUTES"), ("dwCreationDisposition", "DWORD"), ("dwFlagsAndAttributes", "DWORD"), ("hTemplateFile", "HANDLE")]);
        add_winapi(&mut sigs, "WriteFile", "BOOL", 
            &[("hFile", "HANDLE"), ("lpBuffer", "LPCVOID"), ("nNumberOfBytesToWrite", "DWORD"), ("lpNumberOfBytesWritten", "LPDWORD"), ("lpOverlapped", "LPOVERLAPPED")]);
        add_winapi(&mut sigs, "ReadFile", "BOOL", 
            &[("hFile", "HANDLE"), ("lpBuffer", "LPVOID"), ("nNumberOfBytesToRead", "DWORD"), ("lpNumberOfBytesRead", "LPDWORD"), ("lpOverlapped", "LPOVERLAPPED")]);
        add_winapi(&mut sigs, "CloseHandle", "BOOL", 
            &[("hObject", "HANDLE")]);
        add_winapi(&mut sigs, "GetProcAddress", "FARPROC", 
            &[("hModule", "HMODULE"), ("lpProcName", "LPCSTR")]);
        add_winapi(&mut sigs, "LoadLibraryA", "HMODULE", 
            &[("lpLibFileName", "LPCSTR")]);

        SignatureDatabase { sigs }
    }

    pub fn lookup(&self, name: &str) -> Option<&FunctionSignature> {
        // Try exact match, then try dropping A/W/Ex suffix
        if let Some(sig) = self.sigs.get(name) { return Some(sig); }
        
        let cleaned = name.trim_end_matches('A').trim_end_matches('W').trim_end_matches("Ex");
        if let Some(sig) = self.sigs.get(cleaned) { return Some(sig); }
        
        // Try finding if name contains the key (e.g. ADVAPI32!CryptAcquireContextA)
        for (key, sig) in &self.sigs {
            if name.contains(key) { return Some(sig); }
        }

        None
    }
}

fn add_winapi(map: &mut BTreeMap<String, FunctionSignature>, name: &str, ret: &str, params: &[(&str, &str)]) {
    let parameters = params.iter().map(|(n, t)| ParameterInfo { name: n.to_string(), ptype: t.to_string() }).collect();
    map.insert(name.to_string(), FunctionSignature {
        name: name.to_string(),
        ret_type: ret.to_string(),
        parameters,
        calling_convention: CallingConvention::Stdcall, // WinAPI is stdcall
    });
}
