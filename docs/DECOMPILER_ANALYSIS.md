# DEEP_BLEED Decompiler - Análise de Melhorias

Este documento detalha as razões para a avaliação atual do decompiler (**35/100**) e mapeia os desafios críticos para elevar a qualidade do output para um nível de legibilidade de engenharia reversa profissional.

## Por que a nota é 35/100?

Embora o decompiler consiga emitir código C válido sintaticamente, ele falha em ser um "decompiler" no sentido semântico. Ele está mais para um *Lifter* com fluxo de controle básico do que um decompiler completo.

### 1. Poluição de SSA (Single Static Assignment) (DONE)
O output está repleto de variáveis temporárias desnecessárias (`rax_0`, `rax_1`, `rax_2`). 
- **Problema:** Um decompiler maduro deve colapsar operações simples. 
- **Exemplo Atual:** 
  ```c
  rax_1 = rax_1 ^ rsp;
  [esp+0x10] = rax_2;
  ```
- **O que deveria ser:** 
  ```c
  var_10 = rax ^ (stack_pointer);
  ```

### 2. Calling Convention & Signatures (DONE)
Implementamos uma `SignatureDatabase` e suporte a `stdcall`/`fastcall`. O decompiler agora identifica corretamente argumentos de APIs comuns do Windows e recupera parâmetros baseados em registradores (RCX, RDX, R8, R9) e pilha.
- **Antes:** `CryptAcquireContext` aparecia com 1 argumento.
- **Agora:** Aparece com os 5 argumentos corretos e nomes de parâmetros reais.

### 3. Falha no Structurer (Duplicação de Código)
Observamos casos onde o algoritmo de estruturação entra em loops de repetição de código idêntico dentro de blocos `do-while`.
- **Causa:** Má resolução de grafos de fluxo de controle (CFG) complexos ou recursivos.
- **Resultado:** O output de uma única função pode crescer exponencialmente com código redundante.

### 4. Ausência de Type Recovery e Struct Mapping
O código ainda opera sobre " offsets de memória raw" (`[ebx+0x10]`).
- **O ideal:** O decompiler deveria inferir que `ebx` é um ponteiro para uma struct e mostrar algo como `session->secret_key`.

---

## Próximo Passo: Ajuste Escolhido

**Ajuste:** Implementação de um **Expression Folder / Inlining Básico**. (DONE)

**Por que:** Esta é uma mudança simples que gera o maior impacto visual imediato. Ao invés de ver 5 linhas para fazer uma operação aritmética com variáveis temporárias, veremos uma única linha de código C limpa. Isso remove 60% da poluição visual e torna o código "leível" instantaneamente.

---
> [!NOTE]
> Este log serve como guia para as próximas iterações do motor de decompilação DEEP_BLEED.

## Comparativo Real: `test1.c` vs `test1.exe.decompiled.c`

Ao comparar o código original (`test1.c`) com o output do Decompiler, identificamos falhas catastróficas que explicam a nota baixa (**2/100** na avaliação de usuário).

### 1. Desaparecimento de Operações Aritméticas (DONE)
- **Original:** `return a + b;`
- **Decompiled:** `rdx_0 = arg_10; rax_0 = arg_18;` (O operador `+` sumiu).
- **Sugestão:** O motor de análise de IR (Intermediate Representation) está colapsando/ignorando instruções de ALU (Arithmetic Logic Unit). Verifique se o `lifter` está processando corretamente o opcode `ADD`.

### 2. Propagation & Inlining de Argumentos (DONE)
- **Original:** `add(10, 20)`
- **Decompiled:** `add();` (Sem argumentos visíveis no call-site).
- **Sugestão:** Implementar **Inter-procedural Dataflow Analysis**. O decompiler não está rastreando que os valores colocados em `RCX` e `RDX` antes do `CALL` são, na verdade, os argumentos da função.

### 3. Falta de Identificação de Biblioteca (Library Identification) (DONE)
- **Problema:** O decompiler despejou ~3000 linhas de código de runtime do MinGW (CRT Startup, Relocator, etc) e chamou tudo de "USER functions".
- **Sugestão:** Implementar **FLIRT (Fast Library Identification and Recognition Technology)** ou similar. Funções como `___chkstk_ms` e `_pei386_runtime_relocator` devem ser identificadas e ocultadas por padrão.

### 4. Nomeação Genérica (`_text`) (DONE)
- **Problema:** O decompiler falhou em nomear funções importantes como o wrapper do `printf`, chamando-as de `_text_XXXX`.
- **Sugestão:** Quando um símbolo não estiver presente, use a heurística de "chamadas de descendência". Se uma função `F` chama apenas `vfprintf`, nomeie `F` como `sub_printf_wrapper`.

### 5. Linkage de Retorno (DONE)
- **Problema:** `main` chama `add()` e depois `printf()`, mas o código decompilado não mostra que o `RAX` de um vai para o `RDX` do outro.
- **Sugestão:** Melhorar o **Expression Folder**. O resultado de uma função (`RAX`) deve ser injetado como argumento da próxima se o fluxo de dados permitir.

---

## Caixa de Sugestões de "Sobrevivência" (Roadmap 2026)

1.  **(DONE)** **Limpeza de CRT:** Crie um filtro de endereços. Tudo que estiver fora da lógica de entrada (`main`) e for padrão de compilador deve ser marcado como `LIBRARY`.
2.  **(DONE)** **Operação Matemática:** Corrija o `structurer.rs` ou o `optimizer.rs` para não ignorar o `+`, `-`, `*`, `/`. É inaceitável um decompiler não ver uma soma.
3.  **Variáveis SSA:** Implemente um passe de otimização que remova `rax_0`, `rax_1` e transforme em `var_X = a + b`.
4.  **Recuperação de Constantes:** O `10` e `20` do source original sumiram. Eles provavelmente estão sendo carregados via `MOV` e o decompiler os ignorou no output C.
