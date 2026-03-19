use crate::types::*;
use fnv::FnvHashMap;

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED OPTIMIZER - SSA + DCE + Constant Propagation
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[derive(Debug, Default)]
pub struct OptStats {
    pub dce_eliminated: usize,
    pub constants_propagated: usize,
    pub nops_removed: usize,
}

/// SSA renamer: gives each register write a unique version
pub struct SSARenamer {
    counters: FnvHashMap<Register, u32>,
    current_version: FnvHashMap<Register, u32>,
    pub var_info: Vec<SsaVarInfo>,
}

impl SSARenamer {
    pub fn new() -> Self {
        SSARenamer {
            counters: FnvHashMap::default(),
            current_version: FnvHashMap::default(),
            var_info: Vec::new(),
        }
    }

    fn next_version(&mut self, reg: Register) -> String {
        let canon = reg.canonical();
        let ver = self.counters.entry(canon).or_insert(0);
        let name = format!("{}_{}", format!("{}", canon), ver);
        self.current_version.insert(canon, *ver);
        self.var_info.push(SsaVarInfo {
            name: name.clone(),
            register: format!("{}", canon),
            version: *ver,
        });
        *ver += 1;
        name
    }

    fn current_name(&self, reg: Register) -> String {
        let canon = reg.canonical();
        if let Some(ver) = self.current_version.get(&canon) {
            format!("{}_{}", format!("{}", canon), ver)
        } else {
            format!("{}", canon)
        }
    }

    fn rename_src(&self, op: &Operand) -> Operand {
        match op {
            Operand::Reg(r) => Operand::SSAVar(self.current_name(*r)),
            other => other.clone(),
        }
    }

    fn rename_dst(&mut self, op: &Operand) -> Operand {
        match op {
            Operand::Reg(r) => Operand::SSAVar(self.next_version(*r)),
            other => other.clone(),
        }
    }

    pub fn rename_instruction(&mut self, insn: &IRInsn) -> IRInsn {
        match insn {
            IRInsn::Assign { dst, src } => {
                let new_src = self.rename_src(src);
                let new_dst = self.rename_dst(dst);
                IRInsn::Assign { dst: new_dst, src: new_src }
            }
            IRInsn::Add { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Add { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Sub { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Sub { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Mul { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Mul { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Div { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Div { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::And { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::And { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Or { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Or { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Xor { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Xor { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Not { dst, src } => {
                let ns = self.rename_src(src); let nd = self.rename_dst(dst);
                IRInsn::Not { dst: nd, src: ns }
            }
            IRInsn::Shl { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Shl { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Shr { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Shr { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Sar { dst, lhs, rhs } => {
                let nl = self.rename_src(lhs); let nr = self.rename_src(rhs);
                let nd = self.rename_dst(dst);
                IRInsn::Sar { dst: nd, lhs: nl, rhs: nr }
            }
            IRInsn::Load { dst, src } => {
                let ns = self.rename_src(src); let nd = self.rename_dst(dst);
                IRInsn::Load { dst: nd, src: ns }
            }
            IRInsn::Store { dst, src } => {
                let ns = self.rename_src(src); let nd = self.rename_src(dst);
                IRInsn::Store { dst: nd, src: ns }
            }
            IRInsn::Lea { dst, src } => {
                let ns = self.rename_src(src); let nd = self.rename_dst(dst);
                IRInsn::Lea { dst: nd, src: ns }
            }
            IRInsn::Movzx { dst, src } => {
                let ns = self.rename_src(src); let nd = self.rename_dst(dst);
                IRInsn::Movzx { dst: nd, src: ns }
            }
            IRInsn::Movsx { dst, src } => {
                let ns = self.rename_src(src); let nd = self.rename_dst(dst);
                IRInsn::Movsx { dst: nd, src: ns }
            }
            IRInsn::Push { src } => IRInsn::Push { src: self.rename_src(src) },
            IRInsn::Pop { dst } => IRInsn::Pop { dst: self.rename_dst(dst) },
            IRInsn::Call { target } => IRInsn::Call { target: self.rename_src(target) },
            IRInsn::Cmp { lhs, rhs } => IRInsn::Cmp { lhs: self.rename_src(lhs), rhs: self.rename_src(rhs) },
            IRInsn::Test { lhs, rhs } => IRInsn::Test { lhs: self.rename_src(lhs), rhs: self.rename_src(rhs) },
            IRInsn::SetCC { dst, condition } => {
                let nd = self.rename_dst(dst);
                IRInsn::SetCC { dst: nd, condition: condition.clone() }
            }
            other => other.clone(),
        }
    }
}

/// Apply SSA renaming to a basic block
pub fn apply_ssa(block: &mut BasicBlock) -> Vec<SsaVarInfo> {
    let mut renamer = SSARenamer::new();
    let new_insns: Vec<IRInsn> = block.ir_instructions.iter()
        .map(|insn| renamer.rename_instruction(insn))
        .collect();
    block.ir_instructions = new_insns;
    renamer.var_info
}

/// Dead Code Elimination: remove NOPs, self-moves, unused computations
pub fn apply_dce(block: &mut BasicBlock) -> usize {
    let original_len = block.ir_instructions.len();

    // Collect all SSA variable names used as sources
    let mut used_vars: std::collections::HashSet<String> = std::collections::HashSet::new();

    // First pass: collect all used source variables
    for insn in &block.ir_instructions {
        collect_src_vars(insn, &mut used_vars);
    }

    // Remove dead instructions
    block.ir_instructions.retain(|insn| {
        match insn {
            IRInsn::Nop => false,
            // Self-assignment is dead (mov rax, rax)
            IRInsn::Assign { dst, src } if dst == src => false,
            // SSA var that is never read downstream (only safely delete pure Assigns for now)
            IRInsn::Assign { dst: Operand::SSAVar(name), .. } => {
                // Keep if it's FLAGS (side effects matter for CMP chains)
                if name.starts_with("flags") { return true; }
                // Keep if it could be a function argument register
                let n = name.to_lowercase();
                if n.starts_with("rcx") || n.starts_with("rdx") || n.starts_with("r8") || n.starts_with("r9") ||
                   n.starts_with("rdi") || n.starts_with("rsi") || n.starts_with("rax") || n.starts_with("xmm") {
                    return true;
                }
                used_vars.contains(name)
            }
            _ => true,
        }
    });

    original_len - block.ir_instructions.len()
}

fn collect_src_vars(insn: &IRInsn, used: &mut std::collections::HashSet<String>) {
    let collect_op = |op: &Operand, used: &mut std::collections::HashSet<String>| {
        if let Operand::SSAVar(name) = op { used.insert(name.clone()); }
    };
    match insn {
        IRInsn::Assign { src, .. } => { collect_op(src, used); }
        IRInsn::Add { lhs, rhs, .. } | IRInsn::Sub { lhs, rhs, .. }
        | IRInsn::Mul { lhs, rhs, .. } | IRInsn::Div { lhs, rhs, .. }
        | IRInsn::And { lhs, rhs, .. } | IRInsn::Or { lhs, rhs, .. }
        | IRInsn::Xor { lhs, rhs, .. } | IRInsn::Shl { lhs, rhs, .. }
        | IRInsn::Shr { lhs, rhs, .. } | IRInsn::Sar { lhs, rhs, .. } => {
            collect_op(lhs, used); collect_op(rhs, used);
        }
        IRInsn::Not { src, .. } | IRInsn::Load { src, .. } | IRInsn::Movzx { src, .. }
        | IRInsn::Movsx { src, .. } | IRInsn::Lea { src, .. } => { collect_op(src, used); }
        IRInsn::Store { dst, src } => { collect_op(dst, used); collect_op(src, used); }
        IRInsn::Push { src } | IRInsn::Call { target: src } => { collect_op(src, used); }
        IRInsn::Pop { dst } => { collect_op(dst, used); }
        IRInsn::Cmp { lhs, rhs } | IRInsn::Test { lhs, rhs } => {
            collect_op(lhs, used); collect_op(rhs, used);
        }
        _ => {}
    }
}

/// Constant Propagation within a basic block
pub fn apply_constant_propagation(block: &mut BasicBlock) -> usize {
    let mut constants: FnvHashMap<String, i64> = FnvHashMap::default();
    let mut propagated = 0;

    // First pass: find constants
    for insn in &block.ir_instructions {
        if let IRInsn::Assign { dst: Operand::SSAVar(name), src: Operand::Imm(val) } = insn {
            constants.insert(name.clone(), *val);
        }
        if let IRInsn::Assign { dst: Operand::SSAVar(name), src: Operand::UImm(val) } = insn {
            constants.insert(name.clone(), *val as i64);
        }
    }

    // Second pass: propagate into CMP/TEST and other uses
    for insn in &mut block.ir_instructions {
        match insn {
            IRInsn::Cmp { lhs, rhs } | IRInsn::Test { lhs, rhs } => {
                if let Operand::SSAVar(name) = lhs {
                    if let Some(val) = constants.get(name) {
                        *lhs = Operand::Imm(*val);
                        propagated += 1;
                    }
                }
                if let Operand::SSAVar(name) = rhs {
                    if let Some(val) = constants.get(name) {
                        *rhs = Operand::Imm(*val);
                        propagated += 1;
                    }
                }
            }
            IRInsn::Add { rhs, .. } | IRInsn::Sub { rhs, .. }
            | IRInsn::And { rhs, .. } | IRInsn::Or { rhs, .. }
            | IRInsn::Xor { rhs, .. } => {
                if let Operand::SSAVar(name) = rhs {
                    if let Some(val) = constants.get(name) {
                        *rhs = Operand::Imm(*val);
                        propagated += 1;
                    }
                }
            }
            _ => {}
        }
    }

    propagated
}

/// Expression Folding: Inline variables that are assigned once and used once
pub fn apply_expression_folding(block: &mut BasicBlock) -> usize {
    let mut defs: FnvHashMap<String, Operand> = FnvHashMap::default();
    let mut use_count: FnvHashMap<String, usize> = FnvHashMap::default();
    let mut folded = 0;

    // Count uses and find definitions
    for insn in &block.ir_instructions {
        match insn {
            IRInsn::Assign { dst: Operand::SSAVar(name), src } => {
                // Only fold simple operands or registers for now to avoid side-effect issues
                if matches!(src, Operand::Imm(_) | Operand::UImm(_) | Operand::SSAVar(_) | Operand::Reg(_)) {
                    defs.insert(name.clone(), src.clone());
                }
            }
            _ => {}
        }
        
        let mut local_uses: std::collections::HashSet<String> = std::collections::HashSet::new();
        collect_src_vars(insn, &mut local_uses);
        for name in local_uses {
            *use_count.entry(name).or_insert(0) += 1;
        }
    }

    // Replace uses if use_count == 1
    for insn in &mut block.ir_instructions {
        match insn {
            IRInsn::Assign { dst, src } => {
                if let Operand::SSAVar(name) = src {
                    if use_count.get(name) == Some(&1) {
                        if let Some(new_src) = defs.get(name) {
                            *src = new_src.clone();
                            folded += 1;
                        }
                    }
                }
            }
            IRInsn::Add { lhs, rhs, .. } | IRInsn::Sub { lhs, rhs, .. }
            | IRInsn::Mul { lhs, rhs, .. } | IRInsn::Div { lhs, rhs, .. }
            | IRInsn::And { lhs, rhs, .. } | IRInsn::Or { lhs, rhs, .. }
            | IRInsn::Xor { lhs, rhs, .. } | IRInsn::Shl { lhs, rhs, .. }
            | IRInsn::Shr { lhs, rhs, .. } | IRInsn::Sar { lhs, rhs, .. } => {
                if let Operand::SSAVar(name) = lhs {
                    if use_count.get(name) == Some(&1) {
                        if let Some(new_src) = defs.get(name) {
                            *lhs = new_src.clone();
                            folded += 1;
                        }
                    }
                }
                if let Operand::SSAVar(name) = rhs {
                    if use_count.get(name) == Some(&1) {
                        if let Some(new_src) = defs.get(name) {
                            *rhs = new_src.clone();
                            folded += 1;
                        }
                    }
                }
            }
            IRInsn::Push { src } | IRInsn::Call { target: src } | IRInsn::Load { src, .. } 
            | IRInsn::Movzx { src, .. } | IRInsn::Movsx { src, .. } | IRInsn::Lea { src, .. } => {
                if let Operand::SSAVar(name) = src {
                    if use_count.get(name) == Some(&1) {
                        if let Some(new_src) = defs.get(name) {
                            *src = new_src.clone();
                            folded += 1;
                        }
                    }
                }
            }
            _ => {}
        }
    }

    folded
}

/// Full optimization pipeline for a block
pub fn optimize_block(block: &mut BasicBlock) -> (Vec<SsaVarInfo>, OptStats) {
    let mut stats = OptStats::default();

    // Count and remove NOPs first
    let pre_nop = block.ir_instructions.len();
    block.ir_instructions.retain(|i| !matches!(i, IRInsn::Nop));
    stats.nops_removed = pre_nop - block.ir_instructions.len();

    // SSA rename
    let ssa_vars = apply_ssa(block);

    // Constant propagation
    stats.constants_propagated = apply_constant_propagation(block);

    // Expression folding (Inline single-use vars)
    apply_expression_folding(block);

    // DCE (Eliminate instructions whose results were inlined or are unused)
    stats.dce_eliminated = apply_dce(block);

    (ssa_vars, stats)
}
