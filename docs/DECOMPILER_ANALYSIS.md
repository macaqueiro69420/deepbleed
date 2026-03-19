# DEEP_BLEED Decompiler - Análise de Melhorias

Este documento detalha as razões para a avaliação atual do decompiler (**35/100**) e mapeia os desafios críticos para elevar a qualidade do output para um nível de legibilidade de engenharia reversa profissional.

## Por que a nota é 35/100?

Embora o decompiler consiga emitir código C válido sintaticamente, ele falha em ser um "decompiler" no sentido semântico. Ele está mais para um *Lifter* com fluxo de controle básico do que um decompiler completo.

### 1. Poluição de SSA (Single Static Assignment)
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

### 2. Calling Convention Inexistente
Não há reconstrução de argumentos. O decompiler vê uma chamada de função e tenta adivinhar alguns registros, mas ignora a assinatura real da função (especialmente em APIs do Windows que usam `stdcall`).
- **Impacto:** Funções como `CryptAcquireContext` aparecem com apenas 1 argumento, quando na verdade possuem 5. Isso torna a análise de código impossível sem consultar a documentação da API em paralelo.

### 3. Falha no Structurer (Duplicação de Código)
Observamos casos onde o algoritmo de estruturação entra em loops de repetição de código idêntico dentro de blocos `do-while`.
- **Causa:** Má resolução de grafos de fluxo de controle (CFG) complexos ou recursivos.
- **Resultado:** O output de uma única função pode crescer exponencialmente com código redundante.

### 4. Ausência de Type Recovery e Struct Mapping
O código ainda opera sobre " offsets de memória raw" (`[ebx+0x10]`).
- **O ideal:** O decompiler deveria inferir que `ebx` é um ponteiro para uma struct e mostrar algo como `session->secret_key`.

---

## Próximo Passo: Ajuste Escolhido

**Ajuste:** Implementação de um **Expression Folder / Inlining Básico**.

**Por que:** Esta é uma mudança simples que gera o maior impacto visual imediato. Ao invés de ver 5 linhas para fazer uma operação aritmética com variáveis temporárias, veremos uma única linha de código C limpa. Isso remove 60% da poluição visual e torna o código "leível" instantaneamente.

---
> [!NOTE]
> Este log serve como guia para as próximas iterações do motor de decompilação DEEP_BLEED.
