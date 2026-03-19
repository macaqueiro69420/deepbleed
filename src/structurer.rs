use crate::types::*;
use fnv::{FnvHashMap, FnvHashSet};

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  DEEP_BLEED STRUCTURER — CFG → Structured Control Flow Recovery
//  Aggressive pattern matching: if/else/while/do-while/switch/for
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// A full C-level condition expression derived from CMP/TEST + CondJump
#[derive(Debug, Clone)]
pub struct CCondition {
    pub lhs: String,
    pub op: CondOp,
    pub rhs: String,
}

#[derive(Debug, Clone, PartialEq)]
pub enum CondOp {
    Eq,    // ==
    Ne,    // !=
    Lt,    // <  signed
    Le,    // <= signed
    Gt,    // >  signed
    Ge,    // >= signed
    Ult,   // <  unsigned
    Ule,   // <= unsigned
    Ugt,   // >  unsigned
    Uge,   // >= unsigned
    IsZero,    // == 0  (from TEST x,x / JZ)
    IsNonZero, // != 0  (from TEST x,x / JNZ)
    IsNeg,     // < 0   (SF set)
    IsPos,     // >= 0  (SF clear)
    Overflow,
    NoOverflow,
    Parity,
    NoParity,
}

impl std::fmt::Display for CCondition {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self.op {
            CondOp::IsZero    => write!(f, "{} == 0", self.lhs),
            CondOp::IsNonZero => write!(f, "{} != 0", self.lhs),
            CondOp::IsNeg     => write!(f, "{} < 0", self.lhs),
            CondOp::IsPos     => write!(f, "{} >= 0", self.lhs),
            CondOp::Overflow  => write!(f, "overflow()"),
            CondOp::NoOverflow => write!(f, "!overflow()"),
            CondOp::Parity    => write!(f, "parity({}) != 0", self.lhs),
            CondOp::NoParity  => write!(f, "parity({}) == 0", self.lhs),
            CondOp::Eq  => write!(f, "{} == {}", self.lhs, self.rhs),
            CondOp::Ne  => write!(f, "{} != {}", self.lhs, self.rhs),
            CondOp::Lt  => write!(f, "{} < {}", self.lhs, self.rhs),
            CondOp::Le  => write!(f, "{} <= {}", self.lhs, self.rhs),
            CondOp::Gt  => write!(f, "{} > {}", self.lhs, self.rhs),
            CondOp::Ge  => write!(f, "{} >= {}", self.lhs, self.rhs),
            CondOp::Ult => write!(f, "(unsigned){} < (unsigned){}", self.lhs, self.rhs),
            CondOp::Ule => write!(f, "(unsigned){} <= (unsigned){}", self.lhs, self.rhs),
            CondOp::Ugt => write!(f, "(unsigned){} > (unsigned){}", self.lhs, self.rhs),
            CondOp::Uge => write!(f, "(unsigned){} >= (unsigned){}", self.lhs, self.rhs),
        }
    }
}

/// Negate a condition (for the else branch)
pub fn negate_cond(cond: &CCondition) -> CCondition {
    let op = match cond.op {
        CondOp::Eq  => CondOp::Ne,  CondOp::Ne  => CondOp::Eq,
        CondOp::Lt  => CondOp::Ge,  CondOp::Ge  => CondOp::Lt,
        CondOp::Le  => CondOp::Gt,  CondOp::Gt  => CondOp::Le,
        CondOp::Ult => CondOp::Uge, CondOp::Uge => CondOp::Ult,
        CondOp::Ule => CondOp::Ugt, CondOp::Ugt => CondOp::Ule,
        CondOp::IsZero    => CondOp::IsNonZero,
        CondOp::IsNonZero => CondOp::IsZero,
        CondOp::IsNeg     => CondOp::IsPos,
        CondOp::IsPos     => CondOp::IsNeg,
        CondOp::Overflow  => CondOp::NoOverflow,
        CondOp::NoOverflow => CondOp::Overflow,
        CondOp::Parity    => CondOp::NoParity,
        CondOp::NoParity  => CondOp::Parity,
    };
    CCondition { lhs: cond.lhs.clone(), op, rhs: cond.rhs.clone() }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Structured CFG Nodes — the output tree
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

#[derive(Debug, Clone)]
pub struct FlatBlock {
    pub id: String,
    pub address: String,
    pub instructions: Vec<JsonInstruction>,
    /// If this block ends with CMP/TEST before condjump, the resolved condition
    pub cond: Option<CCondition>,
    /// Raw condjump targets: (true_target, false_target)
    pub branch_targets: Option<(String, String)>,
}

#[derive(Debug, Clone)]
pub enum CfgStructure {
    /// Plain sequence of instructions
    Block(FlatBlock),
    /// if (cond) { then } [ else { else_ } ]
    If {
        cond: CCondition,
        then: Vec<CfgStructure>,
        else_: Option<Vec<CfgStructure>>,
        merge_block: Option<String>,
    },
    /// while (cond) { body }
    While {
        cond: CCondition,
        header_id: String,
        body: Vec<CfgStructure>,
    },
    /// do { body } while (cond)
    DoWhile {
        cond: CCondition,
        body: Vec<CfgStructure>,
    },
    /// Loop with break (while(1) + break pattern)
    InfiniteLoop {
        body: Vec<CfgStructure>,
    },
    /// Sequence
    Seq(Vec<CfgStructure>),
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Condition Fusion: CMP/TEST + CondJump → CCondition
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Given a block's instructions, find the last CMP or TEST before the jump,
/// and fuse it with the given condition code to produce a C condition.
pub fn fuse_condition(insns: &[JsonInstruction], condition_code: &str) -> CCondition {
    // Walk backwards to find last cmp or test
    let mut cmp_lhs = String::new();
    let mut cmp_rhs = String::new();
    let mut is_test = false;

    for insn in insns.iter().rev() {
        if insn.op == "cmp" || insn.op == "test" {
            is_test = insn.op == "test";
            cmp_lhs = insn.src.get(0).cloned().unwrap_or_default();
            cmp_rhs = insn.src.get(1).cloned().unwrap_or_default();
            break;
        }
    }

    // TEST x, x  ==>  condition on x itself
    let lhs_eq_rhs = !cmp_lhs.is_empty() && cmp_lhs == cmp_rhs;

    let op = if is_test && lhs_eq_rhs {
        match condition_code {
            "Z"   => CondOp::IsZero,
            "NZ"  => CondOp::IsNonZero,
            "S"   => CondOp::IsNeg,
            "NS"  => CondOp::IsPos,
            "B"   => CondOp::IsZero,   // CF set after test = always 0 result, unusual
            _     => CondOp::IsNonZero,
        }
    } else if is_test {
        // TEST a, b — a & b == 0?
        match condition_code {
            "Z"  => CondOp::IsZero,
            "NZ" => CondOp::IsNonZero,
            "S"  => CondOp::IsNeg,
            "NS" => CondOp::IsPos,
            _    => CondOp::IsNonZero,
        }
    } else {
        // CMP a, b
        match condition_code {
            "Z"   => CondOp::Eq,
            "NZ"  => CondOp::Ne,
            "B"   => CondOp::Ult,
            "NB"  => CondOp::Uge,
            "BE"  => CondOp::Ule,
            "NBE" => CondOp::Ugt,
            "L"   => CondOp::Lt,
            "NL"  => CondOp::Ge,
            "LE"  => CondOp::Le,
            "NLE" => CondOp::Gt,
            "S"   => CondOp::IsNeg,
            "NS"  => CondOp::IsPos,
            "O"   => CondOp::Overflow,
            "NO"  => CondOp::NoOverflow,
            "P"   => CondOp::Parity,
            "NP"  => CondOp::NoParity,
            _     => CondOp::IsNonZero,
        }
    };

    // For test a,a patterns we only need lhs
    let effective_rhs = if is_test && lhs_eq_rhs { String::new() }
                        else if is_test { cmp_rhs.clone() }
                        else { cmp_rhs.clone() };

    CCondition { lhs: cmp_lhs, op, rhs: effective_rhs }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  CFG Graph (working over JsonFunction's blocks and cfg_links)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

pub struct CfgGraph<'a> {
    /// block_id → JsonBlock reference
    pub blocks: FnvHashMap<&'a str, &'a JsonBlock>,
    /// block_id → successor ids
    pub succs: FnvHashMap<&'a str, Vec<&'a str>>,
    /// block_id → predecessor ids
    pub preds: FnvHashMap<&'a str, Vec<&'a str>>,
    /// Block ordering (RPO)
    pub order: Vec<&'a str>,
    /// Immediate dominators
    pub idom: FnvHashMap<&'a str, &'a str>,
    /// Dominator tree children
    pub dom_children: FnvHashMap<&'a str, Vec<&'a str>>,
    /// Back edges (for loop detection)
    pub back_edges: FnvHashSet<(&'a str, &'a str)>,
    /// Pre-calculated RPO indices for O(1) lookup
    pub rpo_indices: FnvHashMap<&'a str, usize>,
}

impl<'a> CfgGraph<'a> {
    pub fn build(func: &'a JsonFunction) -> Self {
        let mut blocks = FnvHashMap::default();
        let mut succs: FnvHashMap<&str, Vec<&str>> = FnvHashMap::default();
        let mut preds: FnvHashMap<&str, Vec<&str>> = FnvHashMap::default();

        for b in &func.blocks {
            blocks.insert(b.id.as_str(), b);
            succs.entry(b.id.as_str()).or_default();
            preds.entry(b.id.as_str()).or_default();
        }

        for link in &func.cfg_links {
            let from = link.from.as_str();
            let to   = link.to.as_str();
            succs.entry(from).or_default().push(to);
            preds.entry(to).or_default().push(from);
        }

        // Compute RPO using DFS from entry (first block)
        let entry = func.blocks.first().map(|b| b.id.as_str()).unwrap_or("");
        let order = compute_rpo(entry, &succs, &blocks);

        // Compute dominators (simple Cooper et al. algorithm)
        let idom = compute_dominators(entry, &order, &preds);

        // Build dom-tree children
        let mut dom_children: FnvHashMap<&str, Vec<&str>> = FnvHashMap::default();
        for (node, &dom) in &idom {
            if *node != dom {
                dom_children.entry(dom).or_default().push(node);
            }
        }

        // Detect back edges (target dominates source)
        let mut back_edges = FnvHashSet::default();
        for (from, succ_list) in &succs {
            for &to in succ_list {
                if dominates(&idom, to, from) && from != &to {
                    back_edges.insert((*from, to));
                }
            }
        }

        let rpo_indices = order.iter().enumerate().map(|(i, &s)| (s, i)).collect();

        CfgGraph { blocks, succs, preds, order, idom, dom_children, back_edges, rpo_indices }
    }

    /// Does `a` dominate `b`?
    pub fn dominates(&self, a: &str, b: &str) -> bool {
        dominates(&self.idom, a, b)
    }

    /// Get immediate post-dominator (convergence point) of two successors
    /// This is the immediate dominator of the join node.
    pub fn find_merge(&self, a: &'a str, b: &'a str) -> Option<&'a str> {
        // Optimization: Use dominator hierarchy if available, but a join node 
        // in a non-structured CFG is harder. BFS from both is the fallback.
        // For structured C, we want the "lowest common reachable node" in RPO.
        
        let a_reach = self.reachable_limited(a);
        let b_reach = self.reachable_limited(b);

        let mut common: Vec<&str> = a_reach.intersection(&b_reach)
            .copied()
            .collect();

        // Sort by RPO index — first one is the merge point
        common.sort_by_key(|s| self.rpo_indices.get(*s).copied().unwrap_or(usize::MAX));
        common.into_iter().next()
    }

    /// All blocks reachable from `start` (not crossing back edges, limited search)
    pub fn reachable_limited(&self, start: &'a str) -> FnvHashSet<&'a str> {
        let mut visited = FnvHashSet::default();
        let mut stack = vec![start];
        // Limit search to 512 nodes per path to avoid O(N^2) blowup on extreme cases
        // while still finding merges for most real code.
        let mut count = 0;
        while let Some(node) = stack.pop() {
            if count > 512 { break; }
            if visited.insert(node) {
                count += 1;
                if let Some(succs) = self.succs.get(node) {
                    for &s in succs {
                        if !self.back_edges.contains(&(node, s)) {
                            stack.push(s);
                        }
                    }
                }
            }
        }
        visited
    }

    /// Blocks between `start` (exclusive) and `end` (exclusive), dominated by `start`
    pub fn collect_region(&self, start: &'a str, end: Option<&'a str>) -> Vec<&'a str> {
        let start_idx = *self.rpo_indices.get(start).unwrap_or(&0);
        let end_idx = end.and_then(|e| self.rpo_indices.get(e)).copied().unwrap_or(usize::MAX);

        let mut region: Vec<&str> = self.order.iter()
            .enumerate()
            .filter(|(idx, n)| {
                *idx > start_idx && *idx < end_idx && self.dominates(start, n) && n != &&start
            })
            .map(|(_, n)| *n)
            .collect();

        region
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Dominator computation (Cooper et al. simple iterative)
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

fn compute_rpo<'a>(
    entry: &'a str,
    succs: &FnvHashMap<&'a str, Vec<&'a str>>,
    blocks: &FnvHashMap<&'a str, &'a JsonBlock>,
) -> Vec<&'a str> {
    let mut visited = FnvHashSet::default();
    let mut post = Vec::new();
    dfs_post(entry, succs, blocks, &mut visited, &mut post);
    post.reverse();
    post
}

fn dfs_post<'a>(
    node: &'a str,
    succs: &FnvHashMap<&'a str, Vec<&'a str>>,
    blocks: &FnvHashMap<&'a str, &'a JsonBlock>,
    visited: &mut FnvHashSet<&'a str>,
    post: &mut Vec<&'a str>,
) {
    if !visited.insert(node) { return; }
    if !blocks.contains_key(node) { return; }
    if let Some(s) = succs.get(node) {
        for &succ in s { dfs_post(succ, succs, blocks, visited, post); }
    }
    post.push(node);
}

fn compute_dominators<'a>(
    entry: &'a str,
    order: &[&'a str],
    preds: &FnvHashMap<&'a str, Vec<&'a str>>,
) -> FnvHashMap<&'a str, &'a str> {
    let rpo_idx: FnvHashMap<&str, usize> = order.iter()
        .enumerate().map(|(i, &s)| (s, i)).collect();

    let mut idom: FnvHashMap<&str, &str> = FnvHashMap::default();
    idom.insert(entry, entry);

    let mut changed = true;
    while changed {
        changed = false;
        for &b in order {
            if b == entry { continue; }
            let preds_b: Vec<&str> = preds.get(b).cloned().unwrap_or_default()
                .into_iter()
                .filter(|p| idom.contains_key(*p))
                .collect();

            if preds_b.is_empty() { continue; }

            // new_idom = first processed predecessor
            let mut new_idom = preds_b[0];
            for &p in &preds_b[1..] {
                new_idom = intersect(new_idom, p, &idom, &rpo_idx);
            }

            if idom.get(b) != Some(&new_idom) {
                idom.insert(b, new_idom);
                changed = true;
            }
        }
    }
    idom
}

fn intersect<'a>(
    mut b1: &'a str,
    mut b2: &'a str,
    idom: &FnvHashMap<&'a str, &'a str>,
    rpo_idx: &FnvHashMap<&str, usize>,
) -> &'a str {
    while b1 != b2 {
        let i1 = *rpo_idx.get(b1).unwrap_or(&usize::MAX);
        let i2 = *rpo_idx.get(b2).unwrap_or(&usize::MAX);
        while rpo_idx.get(b1).unwrap_or(&usize::MAX) > rpo_idx.get(b2).unwrap_or(&usize::MAX) {
            b1 = idom.get(b1).copied().unwrap_or(b1);
        }
        while rpo_idx.get(b2).unwrap_or(&usize::MAX) > rpo_idx.get(b1).unwrap_or(&usize::MAX) {
            b2 = idom.get(b2).copied().unwrap_or(b2);
        }
        // Safety: avoid infinite loop if idom not converging
        let ni1 = *rpo_idx.get(b1).unwrap_or(&usize::MAX);
        let ni2 = *rpo_idx.get(b2).unwrap_or(&usize::MAX);
        if i1 == ni1 && i2 == ni2 { break; }
    }
    b1
}

fn dominates<'a>(idom: &FnvHashMap<&'a str, &'a str>, a: &'a str, b: &'a str) -> bool {
    let mut cur = b;
    let mut prev = "";
    loop {
        if cur == a { return true; }
        let next = idom.get(cur).copied().unwrap_or(cur);
        if next == cur || next == prev { return false; }
        prev = cur;
        cur = next;
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Main Structuring Entry Point
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Structure a function's CFG into nested C-like control flow nodes.
pub fn structure_function(func: &JsonFunction) -> Vec<CfgStructure> {
    if func.blocks.is_empty() { return vec![]; }

    let graph = CfgGraph::build(func);
    let entry = func.blocks.first().unwrap().id.as_str();

    let mut visited = FnvHashSet::default();
    structure_region(&graph, entry, None, &mut visited, func, 0)
}

fn structure_region<'a>(
    graph: &CfgGraph<'a>,
    start: &'a str,
    merge: Option<&'a str>,
    visited: &mut FnvHashSet<&'a str>,
    func: &'a JsonFunction,
    depth: usize,
) -> Vec<CfgStructure> {
    // Depth limit: prevent stack overflow on large/complex CFGs
    // Fall back to flat block emission beyond this depth
    const MAX_DEPTH: usize = 48;

    let mut result = Vec::new();
    let mut cur = start;

    loop {
        // Stop at merge point or already-visited
        if Some(cur) == merge { break; }
        if !visited.insert(cur) { break; }

        let block = match graph.blocks.get(cur) {
            Some(b) => *b,
            None => break,
        };

        let succs = graph.succs.get(cur).cloned().unwrap_or_default();

        // ── Check for back edge (loop header) ──
        let back_succs: Vec<&str> = succs.iter()
            .filter(|&&s| graph.back_edges.contains(&(cur, s)))
            .copied()
            .collect();

        let fwd_succs: Vec<&str> = succs.iter()
            .filter(|&&s| !graph.back_edges.contains(&(cur, s)))
            .copied()
            .collect();

        // ── LOOP DETECTION ──
        if !back_succs.is_empty() && depth < MAX_DEPTH {
            let loop_header = back_succs[0];

            if fwd_succs.is_empty() {
                let body_nodes = graph.collect_region(loop_header, None);
                let mut body_visited = visited.clone();
                let body = structure_region_list(graph, &body_nodes, &mut body_visited, func, depth + 1);
                result.push(CfgStructure::InfiniteLoop { body });
                break;
            } else {
                let exit = fwd_succs[0];

                if cur == loop_header {
                    let cond = extract_block_condition(block);
                    let body_nodes = graph.collect_region(cur, Some(exit));
                    let mut body_visited = FnvHashSet::default();
                    body_visited.insert(cur);
                    let body = structure_region_list(graph, &body_nodes, &mut body_visited, func, depth + 1);
                    result.push(CfgStructure::While {
                        cond: cond.unwrap_or_else(|| CCondition {
                            lhs: "1".into(), op: CondOp::IsNonZero, rhs: String::new()
                        }),
                        header_id: cur.to_string(),
                        body,
                    });
                    cur = exit;
                    continue;
                } else {
                    let cond = extract_block_condition(block);
                    let body_nodes = graph.collect_region(loop_header, Some(cur));
                    let mut body_visited = FnvHashSet::default();
                    let mut body = structure_region_list(graph, &body_nodes, &mut body_visited, func, depth + 1);
                    body.push(CfgStructure::Block(make_flat_block(block, None)));
                    result.push(CfgStructure::DoWhile {
                        cond: cond.unwrap_or_else(|| CCondition {
                            lhs: "1".into(), op: CondOp::IsNonZero, rhs: String::new()
                        }),
                        body,
                    });
                    cur = exit;
                    continue;
                }
            }
        }

        // ── IF / IF-ELSE DETECTION ──
        if fwd_succs.len() == 2 && depth < MAX_DEPTH {
            let true_succ  = fwd_succs[0];
            let false_succ = fwd_succs[1];

            let merge_pt = graph.find_merge(true_succ, false_succ);

            let cond = extract_block_condition(block);
            let cond = cond.unwrap_or_else(|| CCondition {
                lhs: "?".into(), op: CondOp::IsNonZero, rhs: String::new()
            });

            let flat = make_flat_block_strip_cmp_jump(block);
            if !flat.instructions.is_empty() {
                result.push(CfgStructure::Block(flat));
            }

            let (then_nodes, else_nodes) = (
                collect_arm(graph, true_succ, merge_pt),
                collect_arm(graph, false_succ, merge_pt),
            );

            let mut then_visited = FnvHashSet::default();
            for &n in &then_nodes { then_visited.insert(n); }
            let then_body = structure_region_list(graph, &then_nodes, &mut then_visited, func, depth + 1);

            let else_body = if !else_nodes.is_empty() {
                let mut else_visited = FnvHashSet::default();
                for &n in &else_nodes { else_visited.insert(n); }
                let eb = structure_region_list(graph, &else_nodes, &mut else_visited, func, depth + 1);
                if eb.is_empty() { None } else { Some(eb) }
            } else {
                None
            };

            for &n in &then_nodes { visited.insert(n); }
            if else_body.is_some() {
                for n in collect_arm(graph, false_succ, merge_pt) { visited.insert(n); }
            }

            result.push(CfgStructure::If {
                cond,
                then: then_body,
                else_: else_body,
                merge_block: merge_pt.map(|s| s.to_string()),
            });

            if let Some(mp) = merge_pt {
                cur = mp;
                continue;
            } else {
                break;
            }
        }

        // ── PLAIN BLOCK (also fallback when depth >= MAX_DEPTH) ──
        let flat = make_flat_block(block, None);
        result.push(CfgStructure::Block(flat));

        match fwd_succs.as_slice() {
            [] => break,
            [next] => {
                cur = *next;
            }
            _ => {
                for &s in &fwd_succs {
                    if Some(s) != merge && depth < MAX_DEPTH {
                        // Reuse visited set where possible by passing it rather than cloning (Delta approach)
                        let sub = structure_region(graph, s, merge, visited, func, depth + 1);
                        result.extend(sub);
                    } else if Some(s) != merge {
                        if let Some(blk) = graph.blocks.get(s) {
                            result.push(CfgStructure::Block(make_flat_block(blk, None)));
                        }
                    }
                }
                break;
            }
        }
    }

    result
}

fn structure_region_list<'a>(
    graph: &CfgGraph<'a>,
    nodes: &[&'a str],
    visited: &mut FnvHashSet<&'a str>,
    func: &'a JsonFunction,
    depth: usize,
) -> Vec<CfgStructure> {
    let mut result = Vec::new();
    for &n in nodes {
        let sub = structure_region(graph, n, None, visited, func, depth);
        result.extend(sub);
    }
    result
}


/// Collect nodes belonging to a conditional arm (between start and merge)
fn collect_arm<'a>(graph: &CfgGraph<'a>, start: &'a str, merge: Option<&'a str>) -> Vec<&'a str> {
    if Some(start) == merge { return vec![]; }
    let start_idx = *graph.rpo_indices.get(start).unwrap_or(&0);
    let end_idx = merge.and_then(|e| graph.rpo_indices.get(e)).copied().unwrap_or(usize::MAX);

    let arm: Vec<&str> = graph.order.iter()
        .copied()
        .enumerate()
        .filter(|(idx, _n)| {
            *idx >= start_idx && *idx < end_idx
        })
        .map(|(_, n)| n)
        .collect();
    arm
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Block Helpers
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Extract the C condition from the last CMP/TEST + cond_jump in a block
pub fn extract_block_condition(block: &JsonBlock) -> Option<CCondition> {
    // Find the cond_jump instruction
    let cj = block.instructions.iter().rev().find(|i| i.op == "cond_jump")?;
    let condition_code = cj.src.get(1)?;

    // The instructions before the jump are what we fuse with
    let before_jump: Vec<&JsonInstruction> = block.instructions.iter()
        .take_while(|i| i.op != "cond_jump")
        .collect();

    // Build a slice to pass to fuse_condition
    let insns_slice: Vec<JsonInstruction> = before_jump.iter().map(|i| (*i).clone()).collect();
    Some(fuse_condition(&insns_slice, condition_code))
}

/// Create a FlatBlock from a JsonBlock, optionally with a condition
fn make_flat_block(block: &JsonBlock, cond: Option<CCondition>) -> FlatBlock {
    // Filter out jump/cond_jump/nop from instructions (they become control flow)
    let insns: Vec<JsonInstruction> = block.instructions.iter()
        .filter(|i| !matches!(i.op.as_str(), "jump" | "cond_jump" | "nop" | "ret"))
        .cloned()
        .collect();

    let branch_targets = block.instructions.iter()
        .find(|i| i.op == "cond_jump")
        .and_then(|i| {
            let t = i.src.get(0)?.clone();
            Some((t.clone(), t)) // placeholder; real targets come from CFG links
        });

    FlatBlock {
        id: block.id.clone(),
        address: block.address.clone(),
        instructions: insns,
        cond,
        branch_targets,
    }
}

/// Create a FlatBlock but strip the CMP/TEST that is fused into an if condition
fn make_flat_block_strip_cmp_jump(block: &JsonBlock) -> FlatBlock {
    // Find last cmp/test index
    let last_cmp_idx = block.instructions.iter().rposition(|i| i.op == "cmp" || i.op == "test");

    let insns: Vec<JsonInstruction> = block.instructions.iter()
        .enumerate()
        .filter(|(idx, i)| {
            // skip the cmp/test that was fused
            if let Some(ci) = last_cmp_idx {
                if *idx == ci { return false; }
            }
            !matches!(i.op.as_str(), "jump" | "cond_jump" | "nop")
        })
        .map(|(_, i)| i.clone())
        .collect();

    FlatBlock {
        id: block.id.clone(),
        address: block.address.clone(),
        instructions: insns,
        cond: None,
        branch_targets: None,
    }
}

// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  Prologue/Epilogue Detection
// ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

/// Returns true if the instruction is prologue/epilogue noise
pub fn is_prologue_epilogue_noise(insn: &JsonInstruction) -> bool {
    match insn.op.as_str() {
        "push" => {
            // push ebp / push rbp / push esi / push edi / push ebx — callee-saved = noise
            let r = insn.src.get(0).map(|s| s.as_str()).unwrap_or("");
            matches!(r, "ebp" | "rbp" | "esi" | "edi" | "ebx" | "rsi" | "rdi" | "rbx"
                     | "esp_0" | "ebp_0" | "rbp_0")
        }
        "pop" => {
            let r = insn.dst.as_deref().unwrap_or("");
            matches!(r, "ebp" | "rbp" | "esi" | "edi" | "ebx" | "rsi" | "rdi" | "rbx"
                     | "esp_0" | "ebp_0" | "rbp_0")
        }
        "assign" => {
            // mov ebp, esp / mov rbp, rsp  — frame setup
            let dst = insn.dst.as_deref().unwrap_or("");
            let src = insn.src.get(0).map(|s| s.as_str()).unwrap_or("");
            (dst.contains("ebp") && src.contains("esp"))
            || (dst.contains("rbp") && src.contains("rsp"))
            // sub esp, N — stack alloc, keep
        }
        _ => false,
    }
}

/// Clean up an instruction's display for C output
pub fn prettify_operand(s: &str) -> String {
    // Replace SSA-style rax_0 with just var_rax or keep as-is
    // If it's a local_mXX (negative offset), show as var_N
    if let Some(rest) = s.strip_prefix("local_m") {
        return format!("var_{}", rest);
    }
    if let Some(rest) = s.strip_prefix("local_") {
        return format!("arg_{}", rest);
    }
    // SSA var rax_0 → keep as is (it's already pretty)
    s.to_string()
}
