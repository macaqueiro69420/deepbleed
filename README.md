# 🩸 DEEP_BLEED: Aggressive Decompilation Engine

**DEEP_BLEED** é um decompiler binário de alto desempenho escrito em Rust, projetado para transformar executáveis PE (Portable Executable) de arquiteturas x86 e x64 em código C legível e estruturado.

O foco do projeto é fornecer uma base sólida para engenharia reversa, utilizando técnicas modernas de análise estática e otimização de representação intermediária (IR).

---

## 🚀 Funcionalidades Principais

-   **Lifting de IR & SSA:** Tradução direta de opcodes x86/x64 para uma Representação Intermediária (IR) baseada em Single Static Assignment (SSA).
-   **Análise de Fluxo de Controle (CFG):** Reconstrução paralela de grafos de fluxo de controle por chunks de memória.
-   **Signature Database:** Identificação automatizada de APIs comuns do Windows e convenções de chamada (`stdcall`, `fastcall`).
-   **Otimizações Agresivas:**
    -   *Dead Code Elimination* (DCE).
    -   *Constant Propagation*.
    -   *Expression Folding / Inlining*.
-   **Geração de Pseudocódigo C:** Output focado em legibilidade para humanos e consumo por LLMs.
-   **Output Duplo:** Gera um arquivo `.ir.json` (para ferramentas) e `.decompiled.c` (para análise humana).

---

## 📊 Status do Projeto

Atualmente, o decompiler está em fase de **Desenvolvimento**.

### Roadmap & Melhorias
-   ✅ SSA Variable Inlining (Done)
-   ✅ Identificação de Funções de Runtime (CRT) (Done)
-   ✅ Recuperação de Assinaturas de Call (Done)
-   🟡 Struct & Type Recovery (Em andamento)
-   🟡 Loop Structuring Improvements (Em andamento)

---

## 🛠️ Como Usar

### Pré-requisitos
-   [Rust](https://www.rust-lang.org/) (Edition 2024)

### Instalação
```bash
git clone https://github.com/macaqueiro69420/deepbleed
cd deepbleed
cargo build --release
```

### Execução
Para analisar um executável:
```bash
./target/release/deepbleed <caminho_para_o_binario.exe> --output <nome_base>
```

**Argumentos:**
-   `--output <name>`: Define o prefixo dos arquivos de saída.
-   `--no-json`: Pula a geração do arquivo JSON de IR.

---

## 🏗️ Tech Stack

-   **Linguagem:** Rust 🦀
-   **Disassembler:** [Zydis](https://zydis.rs/) (Decodificação completa de instruções).
-   **Binários:** [object-rs](https://github.com/gimli-rs/object) (Parsing de PE/read).
-   **Paralelismo:** [Rayon](https://github.com/rayon-rs/rayon) (Análise de CFG ultra-rápida).
-   **Data Structures:** DashMap (Thread-safe hash maps).

---
> *Desenvolvido para transformar binários complexos em código compreensível.*
