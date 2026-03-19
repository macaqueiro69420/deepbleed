use serde::{Serialize, Deserialize};
use std::collections::BTreeMap;
use std::fmt;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED CORE TYPES - IR Intermediate Representation
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub enum ControlType {
    Jump,
    ConditionalJump,
    Call,
    Return,
    Unknown,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct ControlFlowInfo {
    pub addr: u64,
    pub size: usize,
    pub ctrl_type: ControlType,
    pub target: Option<u64>,
}

#[derive(Debug, Clone)]
pub struct CodeChunk {
    pub name: String,
    pub address: u64,
    pub offset: usize,
    pub size: usize,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct BasicBlock {
    pub start_addr: u64,
    pub end_addr: u64,
    pub edges: Vec<u64>,
    pub ir_instructions: Vec<IRInsn>,
}

#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
pub enum Operand {
    Reg(Register),
    Imm(i64),
    UImm(u64),
    LocalVar(i32),
    GlobalVar(u64),
    Deref(Box<Operand>, i32),
    SSAVar(String),
    Unknown(String),
}

#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash, Serialize, Deserialize)]
pub enum Register {
    RAX, RBX, RCX, RDX, RSI, RDI, RBP, RSP,
    R8, R9, R10, R11, R12, R13, R14, R15,
    EAX, EBX, ECX, EDX, ESI, EDI, EBP, ESP,
    AX, BX, CX, DX, SI, DI, BP, SP,
    AL, BL, CL, DL, AH, BH, CH, DH,
    XMM0, XMM1, XMM2, XMM3, XMM4, XMM5, XMM6, XMM7,
    RIP, EIP, FLAGS, Invalid,
}

impl Register {
    pub fn canonical(&self) -> Register {
        match self {
            Register::EAX | Register::AX | Register::AL | Register::AH => Register::RAX,
            Register::EBX | Register::BX | Register::BL | Register::BH => Register::RBX,
            Register::ECX | Register::CX | Register::CL | Register::CH => Register::RCX,
            Register::EDX | Register::DX | Register::DL | Register::DH => Register::RDX,
            Register::ESI | Register::SI => Register::RSI,
            Register::EDI | Register::DI => Register::RDI,
            Register::EBP | Register::BP => Register::RBP,
            Register::ESP | Register::SP => Register::RSP,
            Register::EIP => Register::RIP,
            other => *other,
        }
    }
}

impl fmt::Display for Register {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let s = format!("{:?}", self).to_lowercase();
        write!(f, "{}", s)
    }
}

impl fmt::Display for Operand {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            Operand::Reg(r) => write!(f, "{}", r),
            Operand::Imm(i) => write!(f, "{}", i),
            Operand::UImm(u) => write!(f, "0x{:X}", u),
            Operand::LocalVar(off) => {
                if *off >= 0 { write!(f, "local_{:X}", *off as u32) }
                else { write!(f, "local_m{:X}", (*off).unsigned_abs()) }
            }
            Operand::GlobalVar(addr) => write!(f, "gvar_{:X}", addr),
            Operand::Deref(base, off) => {
                if *off >= 0 { write!(f, "[{}+0x{:X}]", base, *off as u32) }
                else { write!(f, "[{}-0x{:X}]", base, (*off).unsigned_abs()) }
            }
            Operand::SSAVar(name) => write!(f, "{}", name),
            Operand::Unknown(s) => write!(f, "{}", s),
        }
    }
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub enum IRInsn {
    Assign { dst: Operand, src: Operand },
    Add { dst: Operand, lhs: Operand, rhs: Operand },
    Sub { dst: Operand, lhs: Operand, rhs: Operand },
    Mul { dst: Operand, lhs: Operand, rhs: Operand },
    Div { dst: Operand, lhs: Operand, rhs: Operand },
    And { dst: Operand, lhs: Operand, rhs: Operand },
    Or  { dst: Operand, lhs: Operand, rhs: Operand },
    Xor { dst: Operand, lhs: Operand, rhs: Operand },
    Not { dst: Operand, src: Operand },
    Shl { dst: Operand, lhs: Operand, rhs: Operand },
    Shr { dst: Operand, lhs: Operand, rhs: Operand },
    Sar { dst: Operand, lhs: Operand, rhs: Operand },
    Load  { dst: Operand, src: Operand },
    Store { dst: Operand, src: Operand },
    Lea   { dst: Operand, src: Operand },
    Call  { target: Operand },
    Jump  { target: u64 },
    CondJump { target: u64, condition: String },
    Return,
    Push { src: Operand },
    Pop  { dst: Operand },
    Cmp  { lhs: Operand, rhs: Operand },
    Test { lhs: Operand, rhs: Operand },
    SetCC { dst: Operand, condition: String },
    Movzx { dst: Operand, src: Operand },
    Movsx { dst: Operand, src: Operand },
    Movabs { dst: Operand, src: u64 },
    Nop,
    Unknown { asm: String, addr: u64 },
    Label { addr: u64 },
}

impl fmt::Display for IRInsn {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            IRInsn::Assign { dst, src } => write!(f, "{} = {}", dst, src),
            IRInsn::Add { dst, lhs, rhs } => write!(f, "{} = {} + {}", dst, lhs, rhs),
            IRInsn::Sub { dst, lhs, rhs } => write!(f, "{} = {} - {}", dst, lhs, rhs),
            IRInsn::Mul { dst, lhs, rhs } => write!(f, "{} = {} * {}", dst, lhs, rhs),
            IRInsn::Div { dst, lhs, rhs } => write!(f, "{} = {} / {}", dst, lhs, rhs),
            IRInsn::And { dst, lhs, rhs } => write!(f, "{} = {} & {}", dst, lhs, rhs),
            IRInsn::Or  { dst, lhs, rhs } => write!(f, "{} = {} | {}", dst, lhs, rhs),
            IRInsn::Xor { dst, lhs, rhs } => write!(f, "{} = {} ^ {}", dst, lhs, rhs),
            IRInsn::Not { dst, src } => write!(f, "{} = ~{}", dst, src),
            IRInsn::Shl { dst, lhs, rhs } => write!(f, "{} = {} << {}", dst, lhs, rhs),
            IRInsn::Shr { dst, lhs, rhs } => write!(f, "{} = {} >> {}", dst, lhs, rhs),
            IRInsn::Sar { dst, lhs, rhs } => write!(f, "{} = {} >>> {}", dst, lhs, rhs),
            IRInsn::Load { dst, src } => write!(f, "{} = LOAD({})", dst, src),
            IRInsn::Store { dst, src } => write!(f, "STORE({}, {})", dst, src),
            IRInsn::Lea { dst, src } => write!(f, "{} = LEA({})", dst, src),
            IRInsn::Call { target } => write!(f, "CALL({})", target),
            IRInsn::Jump { target } => write!(f, "JMP 0x{:X}", target),
            IRInsn::CondJump { target, condition } => write!(f, "JMP 0x{:X} IF {}", target, condition),
            IRInsn::Return => write!(f, "RET"),
            IRInsn::Push { src } => write!(f, "PUSH({})", src),
            IRInsn::Pop { dst } => write!(f, "POP({})", dst),
            IRInsn::Cmp { lhs, rhs } => write!(f, "CMP({}, {})", lhs, rhs),
            IRInsn::Test { lhs, rhs } => write!(f, "TEST({}, {})", lhs, rhs),
            IRInsn::SetCC { dst, condition } => write!(f, "{} = SET{}", dst, condition),
            IRInsn::Movzx { dst, src } => write!(f, "{} = MOVZX({})", dst, src),
            IRInsn::Movsx { dst, src } => write!(f, "{} = MOVSX({})", dst, src),
            IRInsn::Movabs { dst, src } => write!(f, "{} = 0x{:X}", dst, src),
            IRInsn::Nop => write!(f, "NOP"),
            IRInsn::Unknown { asm, addr } => write!(f, "UNKNOWN @ 0x{:X}: {}", addr, asm),
            IRInsn::Label { addr } => write!(f, "LABEL_0x{:X}:", addr),
        }
    }
}

// ━━━━ JSON Output Structures ━━━━

#[derive(Debug, Serialize, Deserialize)]
pub struct JsonOutput {
    pub binary_info: BinaryInfo,
    pub functions: Vec<JsonFunction>,
    pub stats: AnalysisStats,
    #[serde(skip_serializing_if = "BTreeMap::is_empty")]
    pub imports: BTreeMap<String, String>,
    #[serde(skip_serializing_if = "BTreeMap::is_empty")]
    pub exports: BTreeMap<String, String>,
    #[serde(skip_serializing_if = "BTreeMap::is_empty")]
    pub strings: BTreeMap<String, String>,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct BinaryInfo {
    pub file: String,
    pub arch: String,
    pub image_base: String,
    pub entry_point: String,
    pub main_address: Option<String>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct JsonFunction {
    pub address: String,
    pub name: String,
    pub kind: String,
    pub blocks: Vec<JsonBlock>,
    pub cfg_links: Vec<CfgEdge>,
    pub ssa_vars: Vec<SsaVarInfo>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct JsonBlock {
    pub id: String,
    pub address: String,
    pub instructions: Vec<JsonInstruction>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct JsonInstruction {
    pub addr: String,
    pub op: String,
    pub dst: Option<String>,
    pub src: Vec<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub resolved_name: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub string_ref: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub metadata: Option<InsnMetadata>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct InsnMetadata {
    #[serde(skip_serializing_if = "Option::is_none")]
    pub ascii: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub constant_value: Option<String>,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct CfgEdge {
    pub from: String,
    pub to: String,
    #[serde(rename = "type")]
    pub edge_type: String,
}

#[derive(Debug, Clone, Serialize, Deserialize)]
pub struct SsaVarInfo {
    pub name: String,
    pub register: String,
    pub version: u32,
}

#[derive(Debug, Serialize, Deserialize)]
pub struct AnalysisStats {
    pub total_functions: usize,
    pub user_functions: usize,
    pub external_functions: usize,
    pub total_blocks: usize,
    pub total_ir_instructions: usize,
    pub dce_eliminated: usize,
    pub constants_propagated: usize,
    pub nops_removed: usize,
}

#[derive(Debug, Clone)]
pub struct AnalysisResult {
    pub instructions: usize,
    pub control_flow: Vec<ControlFlowInfo>,
    pub leaders: Vec<u64>,
    pub call_targets: Vec<u64>,
}

#[derive(Debug, Clone)]
pub struct FunctionInfo {
    pub address: u64,
    pub name: String,
    pub kind: FunctionKind,
    pub block_addrs: Vec<u64>,
}

#[derive(Debug, Clone, PartialEq, Serialize, Deserialize)]
pub enum FunctionKind {
    User,
    EntryPoint,
    Main,
    ExternalLib,
}

impl fmt::Display for FunctionKind {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            FunctionKind::User => write!(f, "USER"),
            FunctionKind::EntryPoint => write!(f, "ENTRY_POINT"),
            FunctionKind::Main => write!(f, "MAIN"),
            FunctionKind::ExternalLib => write!(f, "EXTERNAL_LIB"),
        }
    }
}
