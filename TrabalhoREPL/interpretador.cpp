#include <iostream>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <string>
#include <iomanip>

using namespace std;
unordered_map<string, float> tabela_simbolos;
enum tipoToken {Num, Var, Op, Atrib, Fim, Div, Mult, Plus, Minus, Abrir, Fechar};

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
        else {
            char c = entrada[i++];

            switch (c) { // reconhece os peradores
                case '+': tokens.push_back({Plus, string(1, c)}); break;
                case '-': tokens.push_back({Minus, string(1, c)}); break;
                case '*': tokens.push_back({Mult, string(1, c)}); break;
                case '/': tokens.push_back({Div, string(1, c)}); break;
                case '=': tokens.push_back({Atrib, "="}); break;
                case '(': tokens.push_back({Abrir, "("}); break;
                case ')': tokens.push_back({Fechar, ")"}); break;
                default:
                    cerr << "Caractere invalido: " << entrada[c] << endl;
                    exit(1);
            }
        }
    }
    tokens.push_back({Fim, ""}); // adiciona token de fim
    return tokens; 
}

void exibir_tabela() {             // exibe todos os tokens

    if (tabela_simbolos.empty()) {
        cout << "A tabela de simbolos esta vazia !" << endl;
        return;
    }
    cout << "Tabela de simbolos:\n";
    for (auto& par : tabela_simbolos) {
        cout << par.first << " = " << par.second << endl;
    }
}

size_t posicao = 0;
vector<Token> tokens;

float expr();  //funçções recursivas
float termo();
float fator();

float expr() {

    float resultado = termo();

    while (tokens[posicao].tipo == Plus || tokens[posicao].tipo == Minus) {

        tipoToken op = tokens[posicao++].tipo;
        float valor = termo();

        if (op == Plus)
            resultado += valor;
        else 
            resultado -= valor;
    }
    return resultado;
}

float termo() {

    float resultado = fator();

    while (tokens[posicao].tipo == Mult || tokens[posicao].tipo == Div) {

        tipoToken op = tokens[posicao++].tipo;
        float valor = fator();

        if (op == Mult)
            resultado *= valor;
        else {
            if (valor == 0) { // divisão por zero
                cerr << "Erro: divisao por zero (" << resultado << "/" << tokens[posicao].valor << "=0)" << endl;
                return 0; 
            }
            resultado /= valor;
        }
    }
    return resultado;
}

float fator() {

    Token t  = tokens[posicao++];

    if (t.tipo == Num) {
        return stoi(t.valor);

    } else if (t.tipo == Var) {

        if (!tabela_simbolos.count(t.valor)) {
            cerr << "Variavel " << t.valor << " nao definida !" << endl;
            exit(1);
        }
        return tabela_simbolos[t.valor];

    } else if (t.tipo == Abrir) {

        float valor = expr();
        if (tokens[posicao].tipo != Fechar) {
            cerr << "Erro: parenteses nao fechados !" << endl;
            exit(1);
        }
        posicao++;
        return valor;

    } else {
        cerr << "Erro: token inesperado !" << endl;
        exit(1);
    }
}

float calcularExpressao(const vector<Token>& tokensEntrada) {
    tokens = tokensEntrada;
    posicao = 0;
    return expr();
}

void atribuirVariavel(const vector<Token>& tokens) {

    string var = tokens[0].valor;
    vector<Token> expressao(tokens.begin()+2, tokens.end()); // adiciona a espressão depois do =
    float valor = calcularExpressao(expressao);
    tabela_simbolos[var] = valor; // adiciona na tabela

    if (valor == static_cast<int>(valor))           // exibe o resultador dependendo do tipo
        cout << static_cast<int>(valor) << endl;    // para inteiro 
    else 
        cout << fixed << setprecision(2) << valor << endl; // para float
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
                cout << static_cast<int>(resultado) << endl;    // para inteiro
            else
                cout << fixed << setprecision(2) << resultado << endl; // para float
        }
    }
    return 0;
}