# Interpretado de Expressões - Estilo REPL

**Interpretador simples de expressões aritméticas**, implementado em C++, com suporte a variáveis e atribuições. Ele simula um terminal do tipo **REPL** (Read-Eval-Print Loop), onde o usuário pode digitar comandos matemáticos, ver resultados imediatos e armazenar variáveis.

**Trabalho desenvolvido para a disciplina de Compiladores.**

---
## Funcionalidades

- Suporte a operações: `+`, `-`, `*`, `/` 
- Atribuição de valores e variáveis
- Exibição da tabela de símbolos
- Detecção de erros:
    - Variáveis não declaradas
    - Divisão por zero
    - Atruições vazias

### Como funciona

- O programa lê comandos do usuário no terminal.
- Cada entrada é tranformada em uma lista de **tokens**.
- Se for uma atribuição, o valor é amazenado.
- Se for expressão, o valor é calculado e exibido.
- Comando `exibir` mostra a tabela de símbolos.
- Caractere `. encerra a execução`.

## Exemplo

```
>> x = 20
20
>> y = x + 2
22
>> x * 2
40
>> exibir
Tabela de simbolos:
x = 20
y =  22
>>.
````
### Observações

As expressões são avaliadas da **esquerda para a direita**, ou seja, não consideram a precedência matemática tradicional.
```
>> 2 + 3 * 5
>> 25
```
O resultado será 25 (`(2 + 3) * 5`), e não 17 (`2 + (3 * 5)`), que seria o correto na matemática formal.