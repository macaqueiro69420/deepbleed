use crate::types::*;
use zydis::ffi::{DecodedOperand, DecodedOperandKind, MemoryInfo};
use zydis::{Decoder, MachineMode, Mnemonic, StackWidth, VisibleOperands};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED LIFTER ENGINE - Assembly → IR
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

pub struct Lifter {
    pub base_addr: u64,
    pub is_64bit: bool,
}

impl Lifter {
    pub fn new(base_addr: u64, is_64bit: bool) -> Self {
        Lifter { base_addr, is_64bit }
    }

    pub fn get_register(zydis_reg: zydis::Register) -> Register {
        use zydis::Register::*;
        match zydis_reg {
            RAX => Register::RAX, EAX => Register::EAX, AX => Register::AX, AL => Register::AL, AH => Register::AH,
            RBX => Register::RBX, EBX => Register::EBX, BX => Register::BX, BL => Register::BL, BH => Register::BH,
            RCX => Register::RCX, ECX => Register::ECX, CX => Register::CX, CL => Register::CL, CH => Register::CH,
            RDX => Register::RDX, EDX => Register::EDX, DX => Register::DX, DL => Register::DL, DH => Register::DH,
            RSI => Register::RSI, ESI => Register::ESI, SI => Register::SI,
            RDI => Register::RDI, EDI => Register::EDI, DI => Register::DI,
            RBP => Register::RBP, EBP => Register::EBP, BP => Register::BP,
            RSP => Register::RSP, ESP => Register::ESP, SP => Register::SP,
            R8 => Register::R8, R9 => Register::R9, R10 => Register::R10, R11 => Register::R11,
            R12 => Register::R12, R13 => Register::R13, R14 => Register::R14, R15 => Register::R15,
            RIP => Register::RIP, EIP => Register::EIP,
            FLAGS | EFLAGS | RFLAGS => Register::FLAGS,
            XMM0 => Register::XMM0, XMM1 => Register::XMM1, XMM2 => Register::XMM2, XMM3 => Register::XMM3,
            XMM4 => Register::XMM4, XMM5 => Register::XMM5, XMM6 => Register::XMM6, XMM7 => Register::XMM7,
            _ => Register::Invalid,
        }
    }

    pub fn operand_to_ir(&self, op: &DecodedOperand) -> Operand {
        match &op.kind {
            DecodedOperandKind::Unused => Operand::Unknown("unused".into()),
            DecodedOperandKind::Reg(reg) => Operand::Reg(Self::get_register(*reg)),
            DecodedOperandKind::Mem(mem) => self.memory_info_to_ir(mem),
            DecodedOperandKind::Ptr(ptr) => {
                Operand::GlobalVar((ptr.offset as u64) | ((ptr.segment as u64) << 32))
            }
            DecodedOperandKind::Imm(imm) => {
                if imm.is_signed { Operand::Imm(imm.value as i64) }
                else { Operand::UImm(imm.value) }
            }
        }
    }

    fn memory_info_to_ir(&self, mem: &MemoryInfo) -> Operand {
        let base = mem.base;
        let index = mem.index;
        let disp = mem.disp.displacement as i32;

        if base == zydis::Register::RBP || base == zydis::Register::EBP {
            if index == zydis::Register::NONE {
                return Operand::LocalVar(disp);
            }
        }

        if base == zydis::Register::RIP || base == zydis::Register::EIP {
            let abs_addr = (self.base_addr as i64 + disp as i64) as u64;
            return Operand::GlobalVar(abs_addr);
        }

        let base_reg = Self::get_register(base);
        Operand::Deref(Box::new(Operand::Reg(base_reg)), disp)
    }

    pub fn get_jump_target(
        &self,
        insn: &zydis::Instruction<VisibleOperands>,
        addr: u64,
    ) -> Option<u64> {
        let operands = insn.operands();
        if operands.is_empty() { return None; }
        match &operands[0].kind {
            DecodedOperandKind::Imm(imm_info) => {
                let instr_end = addr + insn.length as u64;
                if imm_info.is_relative {
                    if imm_info.is_signed {
                        Some((instr_end as i64 + imm_info.value as i64) as u64)
                    } else {
                        Some(instr_end + imm_info.value)
                    }
                } else {
                    Some(imm_info.value)
                }
            }
            _ => None,
        }
    }

    fn mnemonic_to_condition(mnemonic: Mnemonic) -> Option<String> {
        match mnemonic {
            Mnemonic::JO => Some("O".into()), Mnemonic::JNO => Some("NO".into()),
            Mnemonic::JB => Some("B".into()), Mnemonic::JNB => Some("NB".into()),
            Mnemonic::JZ => Some("Z".into()), Mnemonic::JNZ => Some("NZ".into()),
            Mnemonic::JBE => Some("BE".into()), Mnemonic::JNBE => Some("NBE".into()),
            Mnemonic::JS => Some("S".into()), Mnemonic::JNS => Some("NS".into()),
            Mnemonic::JP => Some("P".into()), Mnemonic::JNP => Some("NP".into()),
            Mnemonic::JL => Some("L".into()), Mnemonic::JNL => Some("NL".into()),
            Mnemonic::JLE => Some("LE".into()), Mnemonic::JNLE => Some("NLE".into()),
            _ => None,
        }
    }

    pub fn lift_instruction(
        &self,
        insn: &zydis::Instruction<VisibleOperands>,
        addr: u64,
    ) -> IRInsn {
        let operands = insn.operands();
        let mn = insn.mnemonic;
        let fmt_mn = |m: Mnemonic| -> String { format!("{:?}", m).to_lowercase() };

        let make_unknown = || {
            let mut asm = fmt_mn(mn);
            for op in operands { asm.push(' '); asm.push_str(&self.operand_to_ir(op).to_string()); }
            IRInsn::Unknown { asm, addr }
        };

        match mn {
            // ── MOV family ──
            Mnemonic::MOV | Mnemonic::MOVAPS | Mnemonic::MOVUPS | Mnemonic::MOVDQA
            | Mnemonic::MOVDQU | Mnemonic::MOVBE | Mnemonic::MOVAPD | Mnemonic::MOVUPD
            | Mnemonic::MOVSD | Mnemonic::MOVSS | Mnemonic::MOVD | Mnemonic::MOVQ
            | Mnemonic::MOVHLPS | Mnemonic::MOVLHPS | Mnemonic::MOVHPD | Mnemonic::MOVLPD
            | Mnemonic::MOVHPS | Mnemonic::MOVLPS | Mnemonic::MOVMSKPD | Mnemonic::MOVMSKPS => {
                if operands.len() >= 2 {
                    return IRInsn::Assign { dst: self.operand_to_ir(&operands[0]), src: self.operand_to_ir(&operands[1]) };
                }
            }
            Mnemonic::MOVZX => {
                if operands.len() >= 2 { return IRInsn::Movzx { dst: self.operand_to_ir(&operands[0]), src: self.operand_to_ir(&operands[1]) }; }
            }
            Mnemonic::MOVSX | Mnemonic::MOVSXD => {
                if operands.len() >= 2 { return IRInsn::Movsx { dst: self.operand_to_ir(&operands[0]), src: self.operand_to_ir(&operands[1]) }; }
            }
            Mnemonic::LEA => {
                if operands.len() >= 2 { return IRInsn::Lea { dst: self.operand_to_ir(&operands[0]), src: self.operand_to_ir(&operands[1]) }; }
            }
            // ── Arithmetic ──
            Mnemonic::ADD => {
                if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]); return IRInsn::Add { dst: d.clone(), lhs: d, rhs: s }; }
            }
            Mnemonic::SUB => {
                if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]); return IRInsn::Sub { dst: d.clone(), lhs: d, rhs: s }; }
            }
            Mnemonic::IMUL => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    if operands.len() == 3 { let s2 = self.operand_to_ir(&operands[2]); return IRInsn::Mul { dst: d.clone(), lhs: d, rhs: s2 }; }
                    return IRInsn::Mul { dst: d.clone(), lhs: d, rhs: s };
                }
            }
            Mnemonic::MUL | Mnemonic::DIV | Mnemonic::IDIV => {
                if !operands.is_empty() {
                    let ax = Operand::Reg(if self.is_64bit { Register::RAX } else { Register::EAX });
                    let s = self.operand_to_ir(&operands[0]);
                    return IRInsn::Div { dst: ax.clone(), lhs: ax, rhs: s };
                }
            }
            // ── Bitwise ──
            Mnemonic::AND => { if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]); return IRInsn::And { dst: d.clone(), lhs: d, rhs: s }; } }
            Mnemonic::OR  => { if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]); return IRInsn::Or  { dst: d.clone(), lhs: d, rhs: s }; } }
            Mnemonic::XOR => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    if d == s { return IRInsn::Assign { dst: d, src: Operand::Imm(0) }; }
                    return IRInsn::Xor { dst: d.clone(), lhs: d, rhs: s };
                }
            }
            Mnemonic::NOT => { if !operands.is_empty() { let d = self.operand_to_ir(&operands[0]); return IRInsn::Not { dst: d.clone(), src: d }; } }
            Mnemonic::NEG => { if !operands.is_empty() { let d = self.operand_to_ir(&operands[0]); return IRInsn::Sub { dst: d.clone(), lhs: Operand::Imm(0), rhs: d }; } }
            // ── Shifts ──
            Mnemonic::SHL | Mnemonic::SHLD => { if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let a = self.operand_to_ir(&operands[1]); return IRInsn::Shl { dst: d.clone(), lhs: d, rhs: a }; } }
            Mnemonic::SHR | Mnemonic::SHRD => { if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let a = self.operand_to_ir(&operands[1]); return IRInsn::Shr { dst: d.clone(), lhs: d, rhs: a }; } }
            Mnemonic::SAR | Mnemonic::SHRX | Mnemonic::SARX => { if operands.len() >= 2 { let d = self.operand_to_ir(&operands[0]); let a = self.operand_to_ir(&operands[1]); return IRInsn::Sar { dst: d.clone(), lhs: d, rhs: a }; } }
            // ── Compare / Test ──
            Mnemonic::CMP  => { if operands.len() >= 2 { return IRInsn::Cmp { lhs: self.operand_to_ir(&operands[0]), rhs: self.operand_to_ir(&operands[1]) }; } }
            Mnemonic::TEST => { if operands.len() >= 2 { return IRInsn::Test { lhs: self.operand_to_ir(&operands[0]), rhs: self.operand_to_ir(&operands[1]) }; } }
            // ── SetCC ──
            Mnemonic::SETB | Mnemonic::SETBE | Mnemonic::SETL | Mnemonic::SETLE
            | Mnemonic::SETNB | Mnemonic::SETNBE | Mnemonic::SETNL | Mnemonic::SETNLE
            | Mnemonic::SETNO | Mnemonic::SETNP | Mnemonic::SETNS | Mnemonic::SETNZ
            | Mnemonic::SETO | Mnemonic::SETP | Mnemonic::SETS | Mnemonic::SETZ => {
                if !operands.is_empty() {
                    let cond = format!("{:?}", mn).trim_start_matches("SET").to_string();
                    return IRInsn::SetCC { dst: self.operand_to_ir(&operands[0]), condition: cond };
                }
            }
            // ── Stack ──
            Mnemonic::PUSH => { if !operands.is_empty() { return IRInsn::Push { src: self.operand_to_ir(&operands[0]) }; } }
            Mnemonic::POP  => { if !operands.is_empty() { return IRInsn::Pop  { dst: self.operand_to_ir(&operands[0]) }; } }
            // ── Control Flow ──
            Mnemonic::CALL => {
                if let Some(target) = self.get_jump_target(insn, addr) { return IRInsn::Call { target: Operand::UImm(target) }; }
                else if !operands.is_empty() { return IRInsn::Call { target: self.operand_to_ir(&operands[0]) }; }
            }
            Mnemonic::JMP => {
                if let Some(target) = self.get_jump_target(insn, addr) { return IRInsn::Jump { target }; }
                else { return IRInsn::Jump { target: 0 }; }
            }
            Mnemonic::RET | Mnemonic::IRET | Mnemonic::IRETD | Mnemonic::IRETQ => { return IRInsn::Return; }
            // ── NOPs ──
            Mnemonic::NOP | Mnemonic::FNOP | Mnemonic::ENDBR32 | Mnemonic::ENDBR64 | Mnemonic::FWAIT => { return IRInsn::Nop; }
            Mnemonic::CMC | Mnemonic::CLC | Mnemonic::STC | Mnemonic::CLI
            | Mnemonic::STI | Mnemonic::CLD | Mnemonic::STD => { return IRInsn::Nop; }
            Mnemonic::PUSHFD | Mnemonic::PUSHF | Mnemonic::POPFD | Mnemonic::POPF
            | Mnemonic::PUSHFQ | Mnemonic::POPFQ => { return IRInsn::Nop; }
            // ── Inc/Dec ──
            Mnemonic::INC => { if !operands.is_empty() { let d = self.operand_to_ir(&operands[0]); return IRInsn::Add { dst: d.clone(), lhs: d, rhs: Operand::Imm(1) }; } }
            Mnemonic::DEC => { if !operands.is_empty() { let d = self.operand_to_ir(&operands[0]); return IRInsn::Sub { dst: d.clone(), lhs: d, rhs: Operand::Imm(1) }; } }
            // ── Leave ──
            Mnemonic::LEAVE => {
                let sp = Operand::Reg(if self.is_64bit { Register::RSP } else { Register::ESP });
                let bp = Operand::Reg(if self.is_64bit { Register::RBP } else { Register::EBP });
                return IRInsn::Assign { dst: sp, src: bp };
            }
            // ── CMOVcc ──
            Mnemonic::CMOVB | Mnemonic::CMOVBE | Mnemonic::CMOVL | Mnemonic::CMOVLE
            | Mnemonic::CMOVNB | Mnemonic::CMOVNBE | Mnemonic::CMOVNL | Mnemonic::CMOVNLE
            | Mnemonic::CMOVNO | Mnemonic::CMOVNP | Mnemonic::CMOVNS | Mnemonic::CMOVNZ
            | Mnemonic::CMOVO | Mnemonic::CMOVP | Mnemonic::CMOVS | Mnemonic::CMOVZ => {
                if operands.len() >= 2 { return IRInsn::Assign { dst: self.operand_to_ir(&operands[0]), src: self.operand_to_ir(&operands[1]) }; }
            }
            // ── Sign extend ──
            Mnemonic::CBW | Mnemonic::CWDE | Mnemonic::CDQE => {
                return IRInsn::Movsx { dst: Operand::Reg(if self.is_64bit { Register::RAX } else { Register::EAX }), src: Operand::Reg(Register::AX) };
            }
            Mnemonic::CWD | Mnemonic::CDQ | Mnemonic::CQO => {
                return IRInsn::Assign { dst: Operand::Reg(if self.is_64bit { Register::RDX } else { Register::EDX }), src: Operand::Reg(if self.is_64bit { Register::RAX } else { Register::EAX }) };
            }
            // ── Misc known ──
            Mnemonic::HLT | Mnemonic::CPUID | Mnemonic::RDTSC | Mnemonic::RDTSCP
            | Mnemonic::PAUSE | Mnemonic::SYSCALL | Mnemonic::SYSENTER | Mnemonic::INT3 => {
                return IRInsn::Unknown { asm: fmt_mn(mn), addr };
            }
            Mnemonic::SYSRET | Mnemonic::SYSEXIT => { return IRInsn::Return; }
            // ── Rotates ──
            Mnemonic::ROL | Mnemonic::ROR | Mnemonic::RCL | Mnemonic::RCR => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let a = self.operand_to_ir(&operands[1]);
                    return IRInsn::Assign { dst: d, src: Operand::Unknown(format!("{:?}(dst, {})", mn, a)) };
                }
            }
            // ── Bit scan/test ──
            Mnemonic::BSF | Mnemonic::BSR | Mnemonic::POPCNT | Mnemonic::LZCNT | Mnemonic::TZCNT => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    return IRInsn::Assign { dst: d, src: Operand::Unknown(format!("{}({})", fmt_mn(mn), s)) };
                }
            }
            Mnemonic::BT | Mnemonic::BTC | Mnemonic::BTR | Mnemonic::BTS => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    return IRInsn::Assign { dst: d.clone(), src: Operand::Unknown(format!("{}({}, {})", fmt_mn(mn), d, s)) };
                }
            }
            // ── ADC/SBB ──
            Mnemonic::ADC | Mnemonic::SBB => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    return IRInsn::Assign { dst: d.clone(), src: Operand::Unknown(format!("{}({}, {})", fmt_mn(mn), d, s)) };
                }
            }
            Mnemonic::XCHG | Mnemonic::XADD | Mnemonic::CMPXCHG | Mnemonic::CMPXCHG8B => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    return IRInsn::Assign { dst: d.clone(), src: Operand::Unknown(format!("{}({}, {})", fmt_mn(mn), d, s)) };
                }
            }
            Mnemonic::BSWAP => {
                if !operands.is_empty() { let d = self.operand_to_ir(&operands[0]); return IRInsn::Assign { dst: d, src: Operand::Unknown("bswap(dst)".into()) }; }
            }
            // ── FP/SSE ops ──
            Mnemonic::ADDSS | Mnemonic::ADDSD | Mnemonic::SUBSD | Mnemonic::SUBSS
            | Mnemonic::MULSS | Mnemonic::MULSD | Mnemonic::DIVSS | Mnemonic::DIVSD
            | Mnemonic::ANDPS | Mnemonic::ANDPD | Mnemonic::ORPS | Mnemonic::ORPD
            | Mnemonic::XORPS | Mnemonic::XORPD | Mnemonic::UCOMISS | Mnemonic::UCOMISD
            | Mnemonic::CVTSI2SS | Mnemonic::CVTSI2SD | Mnemonic::CVTSS2SI | Mnemonic::CVTSD2SI
            | Mnemonic::CVTSS2SD | Mnemonic::CVTSD2SS | Mnemonic::SQRTSS | Mnemonic::SQRTSD => {
                if operands.len() >= 2 {
                    let d = self.operand_to_ir(&operands[0]); let s = self.operand_to_ir(&operands[1]);
                    return IRInsn::Assign { dst: d, src: Operand::Unknown(format!("{}({})", fmt_mn(mn), s)) };
                }
            }
            // ── INT ──
            Mnemonic::INT | Mnemonic::INT1 => {
                if !operands.is_empty() { return IRInsn::Unknown { asm: format!("int {}", self.operand_to_ir(&operands[0])), addr }; }
            }
            Mnemonic::LAHF | Mnemonic::SAHF => {
                return IRInsn::Assign { dst: Operand::Reg(Register::AH), src: Operand::Reg(Register::FLAGS) };
            }
            Mnemonic::XLAT => {
                return IRInsn::Assign { dst: Operand::Reg(Register::AL), src: Operand::Deref(Box::new(Operand::Reg(Register::RBX)), 0) };
            }
            _ => {}
        }

        // conditional jumps
        if let Some(cond) = Self::mnemonic_to_condition(mn) {
            if let Some(tgt) = self.get_jump_target(insn, addr) {
                return IRInsn::CondJump { target: tgt, condition: cond };
            }
        }

        make_unknown()
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  BLOCK LIFTER - Disassemble & lift basic blocks
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

pub struct BlockLifter {
    pub decoder: Decoder,
    pub base_addr: u64,
    pub is_64bit: bool,
}

impl BlockLifter {
    pub fn new(machine_mode: MachineMode, stack_width: StackWidth, base_addr: u64) -> Self {
        let decoder = Decoder::new(machine_mode, stack_width).expect("Failed to init decoder");
        let is_64bit = matches!(machine_mode, MachineMode::LONG_64);
        BlockLifter { decoder, base_addr, is_64bit }
    }

    pub fn lift_basic_block(&self, raw_code: &[u8], start_addr: u64) -> BasicBlock {
        let mut ir_instructions = Vec::new();
        let offset = (start_addr.saturating_sub(self.base_addr)) as usize;
        let mut end_addr = start_addr;
        let mut edges = Vec::new();

        ir_instructions.push(IRInsn::Label { addr: start_addr });

        let mut current_offset = offset;
        while current_offset < raw_code.len() {
            let current_addr = self.base_addr + current_offset as u64;

            match self.decoder.decode_first::<VisibleOperands>(&raw_code[current_offset..]) {
                Ok(Some(insn)) => {
                    let insn_len = insn.length as usize;
                    let lifter = Lifter::new(current_addr, self.is_64bit);
                    let ir = lifter.lift_instruction(&insn, current_addr);

                    match &ir {
                        IRInsn::Jump { target } => {
                            edges.push(*target);
                            ir_instructions.push(ir);
                            end_addr = current_addr + insn_len as u64;
                            break;
                        }
                        IRInsn::CondJump { target, .. } => {
                            edges.push(*target);
                            edges.push(current_addr + insn_len as u64);
                            ir_instructions.push(ir);
                            end_addr = current_addr + insn_len as u64;
                            break;
                        }
                        IRInsn::Return => {
                            ir_instructions.push(ir);
                            end_addr = current_addr + insn_len as u64;
                            break;
                        }
                        IRInsn::Call { target } => {
                            if let Operand::UImm(t) = target { edges.push(*t); }
                            ir_instructions.push(ir);
                        }
                        _ => { ir_instructions.push(ir); }
                    }

                    end_addr = current_addr + insn_len as u64;
                    current_offset += insn_len;
                }
                _ => { current_offset += 1; }
            }
        }

        BasicBlock { start_addr, end_addr, edges, ir_instructions }
    }
}

// ━━━━ Control flow analysis ━━━━

pub fn is_control_instruction(mnemonic: Mnemonic) -> ControlType {
    match mnemonic {
        Mnemonic::RET | Mnemonic::IRET | Mnemonic::IRETD | Mnemonic::IRETQ => ControlType::Return,
        Mnemonic::CALL => ControlType::Call,
        Mnemonic::JMP => ControlType::Jump,
        Mnemonic::JO | Mnemonic::JNO | Mnemonic::JB | Mnemonic::JNB
        | Mnemonic::JZ | Mnemonic::JNZ | Mnemonic::JBE | Mnemonic::JNBE
        | Mnemonic::JS | Mnemonic::JNS | Mnemonic::JP | Mnemonic::JNP
        | Mnemonic::JL | Mnemonic::JNL | Mnemonic::JLE | Mnemonic::JNLE
        | Mnemonic::JCXZ | Mnemonic::JECXZ | Mnemonic::JRCXZ
        | Mnemonic::LOOP | Mnemonic::LOOPE | Mnemonic::LOOPNE => ControlType::ConditionalJump,
        _ => ControlType::Unknown,
    }
}

pub fn extract_jump_target(insn: &zydis::Instruction<VisibleOperands>, addr: u64) -> Option<u64> {
    let operands = insn.operands();
    if operands.is_empty() { return None; }
    match &operands[0].kind {
        DecodedOperandKind::Imm(imm_info) => {
            if imm_info.is_relative {
                let instr_end = addr + insn.length as u64;
                if imm_info.is_signed { Some((instr_end as i64 + imm_info.value as i64) as u64) }
                else { Some(instr_end + imm_info.value) }
            } else {
                Some(imm_info.value)
            }
        }
        _ => None,
    }
}

pub fn analyze_chunk(
    raw_code: &[u8],
    base_addr: u64,
    machine_mode: MachineMode,
    stack_width: StackWidth,
) -> AnalysisResult {
    let decoder = Decoder::new(machine_mode, stack_width).expect("Failed to init decoder");
    let mut instructions = 0;
    let mut control_flow = Vec::new();
    let mut leaders = Vec::new();
    let mut call_targets = Vec::new();

    leaders.push(base_addr);
    let mut offset = 0;

    while offset < raw_code.len() {
        let current_addr = base_addr + offset as u64;
        match decoder.decode_first::<VisibleOperands>(&raw_code[offset..]) {
            Ok(Some(insn)) => {
                instructions += 1;
                let insn_len = insn.length as usize;
                let ctrl_type = is_control_instruction(insn.mnemonic);
                if ctrl_type != ControlType::Unknown {
                    let target = extract_jump_target(&insn, current_addr);
                    control_flow.push(ControlFlowInfo { addr: current_addr, size: insn_len, ctrl_type, target });
                    if let Some(tgt) = target {
                        leaders.push(tgt);
                        if ctrl_type == ControlType::Call { call_targets.push(tgt); }
                    }
                    if ctrl_type == ControlType::Jump || ctrl_type == ControlType::ConditionalJump || ctrl_type == ControlType::Return {
                        leaders.push(current_addr + insn_len as u64);
                    }
                }
                offset += insn_len;
            }
            _ => { offset += 1; }
        }
    }

    AnalysisResult { instructions, control_flow, leaders, call_targets }
}
