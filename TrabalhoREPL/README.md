# Interpretado de Expressões - Estilo REPL

**Interpretador simples de expressões aritméticas**, implementado em C++, com suporte a variáveis e atribuições. Ele simula um terminal do tipo **REPL** (Read-Eval-Print Loop), onde o usuário pode digitar comandos matemáticos, ver resultados imediatos e armazenar variáveis.

**Trabalho desenvolvido para a disciplina de Compiladores.**
---
## Funcionalidades

- Suporte a operações: `+`, `-`, `*`, `/` 
- Atribuição de valores e variáveis
- Suporte a **parenteses** para controle de precedência
- Exibição da tabela de símbolos com o comando `exibir`
- Detecção de erros:
    - Variáveis não declaradas
    - Divisão por zero
    - Atruições vazias
    - Parênteses não fechadas
    - Tokens inválidos

### Como funciona

- O programa lê comandos do usuário no terminal.
- Cada entrada é tranformada em uma lista de **tokens**.
- Se for uma atribuição, o valor é amazenado.
- Se for expressão, o valor é calculado e exibido.
- Comando `exibir` mostra a tabela de símbolos.
- Caractere `. encerra a execução`.

## Gramática suportada

A linguagem reconhecida pelo interpretadoe segue a seguinte gramática:

```
<expr>     → <termo> { ("+" | "-") <termo> }
<termo>    → <fator> { ("*" | "/") <fator> }
<fator>    → <número> | <variável> | "(" <expr> ")"
```
* Operadore `*` e `/` têm maior precedência que `+` e `-`.
* Parênteses podem ser usados para alterar a ordem de validação.
* Atribuições são tratadas separadamente, no estilo: 

```
<atribuiçção> → <variável> "=" <expr>
```

## Exemplo

```
>> x = 20
20
>> y = x + 2
22
>> (x + y) * 2
84
>> x + y * 2
64
>> exibir
Tabela de simbolos:
x = 20
y = 22
>> .
````