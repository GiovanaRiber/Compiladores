#include <iostream>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <string>
#include <iomanip>

using namespace std;

unordered_map<string, float> tabela_simbolos;

enum tipoToken {Num, Var, Op, Atrib, Fim};

struct Token {
    tipoToken tipo;
    string valor;
};

vector<Token> criarToken(const string& entrada) {

    vector<Token> tokens;
    size_t i = 0;

    while (i < entrada.size()) {

        if (isspace(entrada[i])) { // para pular espaços em branco
            i++;
        }
        else if (isdigit(entrada[i])) { // caso números

            string num;
            while (i < entrada.size() && isdigit(entrada[i]))
                num += entrada[i++];
            tokens.push_back({Num, num});
        }
        else if (isalpha(entrada[i])) { // caso variáveis

            string var;
            while (i < entrada.size() && isalnum(entrada[i]))
                var += entrada[i++];
            tokens.push_back({Var, var}); 
        }
        else if (entrada[i] == '+' || entrada[i] == '-' || 
                 entrada[i] == '/' || entrada[i] == '*') { // caso operadores

            tokens.push_back({Op, string(1, entrada[i++])});  
        }
        else if (entrada[i] == '=') { // caso atribuição

            tokens.push_back({Atrib, "="});
            i++;
        }
        else { 

            cerr << "Caractere invalido: " << entrada[i] << endl;
            exit(1);
        }
    }
    tokens.push_back({Fim, ""}); // adiciona token de fim
    return tokens; 
}

void exibir_tabela() {             // exibe todos os tokens
    cout << "Tabela de simbolos:\n";
    for (auto& par : tabela_simbolos) {
        cout << par.first << " = " << par.second << endl;
    }
}

float calcularExpressao(const vector<Token>& tokens) {

    char op = '+'; // operador inicial
    float resultado = 0; // armazenar o resultado final
    size_t posicao = 0; // posicao na lista de tokens

    while (posicao < tokens.size()) {

        Token t = tokens[posicao++];

        if (t.tipo == Fim) break;

        if (t.tipo == Num || t.tipo == Var) { // caso seja um número ou uma variável
             
            float valor;

            if (t.tipo == Num)
                valor = stoi(t.valor);
            else {

                if (!tabela_simbolos.count(t.valor)) {
                    cerr << "Variavel " << t.valor << " nao definida !" << endl;
                    exit(1);
                }
                valor = tabela_simbolos[t.valor];
            }

            if (op == '/' && valor == 0) { // divisão por zero
                cerr << "Erro: divisao por zero (" << resultado << "/" << t.valor << "=0)" << endl;
                return 0; 
            }

            switch (op) { // dependendo do operador
                case '/': resultado /= valor; break;
                case '*': resultado *= valor; break;
                case '-': resultado -= valor; break;
                case '+': resultado += valor; break;
            }
        }
        else if (t.tipo == Op) { // caso seja um operador, armazena ele
            op = t.valor[0];
        }
    }
    return resultado;
}

void atribuirVariavel(const vector<Token>& tokens) {

    string var = tokens[0].valor;
    vector<Token> expressao(tokens.begin()+2, tokens.end()); // adiciona a espressão depois do =
    float valor = calcularExpressao(expressao);

    tabela_simbolos[var] = valor; // adiciona na tabela

    if (valor == static_cast<int>(valor)) // exibe o resultador dependendo do tipo
        cout << static_cast<int>(valor) << endl;
    else 
        cout << fixed << setprecision(2) << valor << endl;
}

int main() {

    string entrada;

    while (true) {
        cout << ">> ";

        getline(cin, entrada);
        if (entrada == ".") break; // para sair do loop
        if (entrada == "exibir") { // para mostrar a tabela de símbolos
            exibir_tabela();
            continue;
        }
        vector<Token> tokens = criarToken(entrada);

        if (tokens.size() >= 3 && tokens[0].tipo == Var &&
                                  tokens[1].tipo == Atrib && 
                                  tokens[2].tipo != Fim) { // verifica se é uma atribuição  
            
            atribuirVariavel(tokens); 
        
        }
        else if (tokens[0].tipo == Var && tokens[1].tipo == Atrib) { // para atribuições vazias

            cerr << "Erro: atribuicao indefinida !" << endl;
            continue;
        }
        else {                          // caso seja uma expressão normal

            float resultado = calcularExpressao(tokens);

            if (resultado == static_cast<int>(resultado))
                cout << static_cast<int>(resultado) << endl;
            else
                cout << fixed << setprecision(2) << resultado << endl;
        }
    }
    return 0;
}