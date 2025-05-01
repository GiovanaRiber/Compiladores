#include <iostream>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <string>

using namespace std;

unordered_map<string, int> tabela_simbolos;

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
        else if (entrada[i] == '+' || 
                 entrada[i] == '-' || 
                 entrada[i] == '/' || 
                 entrada[i] == '*') { // caso operadores

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

int calcularExpressao(const vector<Token>& tokens) {

    char op = '+'; // operador inicial
    int resultado = 0; // armazenar o resultado final
    size_t posicao = 0; // posicao na lista de tokens

    while (posicao < tokens.size()) {

        Token t = tokens[posicao++];

        if (t.tipo == Num) { // caso seja um número
            
            int valor = stoi(t.valor);
            switch (op) {
                case '/': resultado /= valor; break;
                case '*': resultado *= valor; break;
                case '-': resultado -= valor; break;
                case '+': resultado += valor; break;
            }
        }
        else if (t.tipo == Var) { // caso seja uma variável
            
            if (!tabela_simbolos.count(t.valor)) {
                cerr << "Variavel indefinida " << t.valor << endl;
                exit(1);
            }

            int valor = tabela_simbolos[t.valor];
            switch (op) {
                case '/': resultado /= valor; break;
                case '*': resultado *= valor; break;
                case '-': resultado -= valor; break;
                case '+': resultado += valor; break;
            }
        }
        else if (t.tipo == Op) { // caso seja um operador, armazena ele
            op = t.valor[0];
        }
        else if (t.tipo == Fim) { // fim :) 
            break;
        }
    }

    return resultado;
}

int main() {

    string entrada;

    while (true) {
        cout << "> ";

        if (!getline(cin, entrada)) break;
        if (entrada == ".") break; // para sair do loop
        if (entrada == "exibir") { // para mostrar a tabela de símbolos
            exibir_tabela();
            continue;
        }
        vector<Token> tokens = criarToken(entrada);

        if (tokens.size() > 2 && tokens[0].tipo == Var && tokens[1].tipo == Atrib) { // verifica se é uma atribuição  
        
            string var = tokens[0].valor;
            vector<Token> expresao(tokens.begin()+2, tokens.end()); // adiciona a espressão depois do =
            int valor = calcularExpressao(expresao);
            tabela_simbolos[var] = valor; // adiciona na tabela
            cout << valor << endl;        // exibe o resultador
        } else {                          // caso seja uma expressão normal
            cout << "" << calcularExpressao(tokens) << endl;
        }
    }
    return 0;
}