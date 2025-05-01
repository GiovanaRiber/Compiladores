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

        if (isspace(entrada[i])) {
            i++;
        }
        else if (isdigit(entrada[i])) {

            string num;
            while (i < entrada.size() && isdigit(entrada[i]))
                num += entrada[i++];
            
        }
        else if (isalpha(entrada[i])) {

            string var;
            while (i < entrada.size() && isalnum(entrada[i]))
                var += entrada[i++];
            tokens.push_back({Var, var}); 
        }
        else if (entrada[i] == '+' || 
                 entrada[i] == '-' || 
                 entrada[i] == '/' || 
                 entrada[i] == '*') {

            tokens.push_back({Op, string(1, entrada[i++])});  
        }
        else if (entrada[i] == '=') {

            tokens.push_back({Atrib, "="});
            i++;
        }
        else {

            cerr << "Caractere invalido: " << entrada[i] << endl;
            exit(1);
        }
    }
    tokens.push_back({Fim, ""});
    return tokens; 
}

void mostrar_tabela() {
    cout << "Tabela de simbolos:\n";
    for (auto& par : tabela_simbolos) {
        cout << par.first << " = " << par.second << endl;
    }
}

int main() {

    string entrada;

    while (true) {
        cout << "> ";

        if (!getline(cin, entrada)) break;
        if (entrada == ".") break;
        if (entrada == "exibir") {
            mostrar_tabela();
            continue;
        }
        vector<Token> tokens = criarToken(entrada);
    }
    return 0;
}