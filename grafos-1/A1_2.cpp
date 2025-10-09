#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

// Executa a busca em largura a partir de um vértice (s)
// Pra rodar:
// g++ buscas.cpp -o buscas
// .\buscas.exe teste.txt <INDICE DO VERTICE INICIAL>

    // levanta erro caso não sejam passados os argumentos corretos
    if (argc < 3) {
        cerr << "Uso " << argv[0] << " <arquivo_grafo> <vertice_inicial>" << endl;
    }

///// LER O ARQUIVO E CRIAR O GRAFO ///////////////////////////////////////

    string arquivo = argv[1];
    int s = stoi(argv[2]);

    // Carrega o grafo
    Grafo g(arquivo);
    int n = g.qtdVertices();

///// INICIALIZAR AS ESTRUTURAS DE DADOS AUXILIARES ///////////////////////

    // vetor que marca true se um vertice já foi visitado
    vector<bool> visitado(n+1, false);

    // guarda o nível de cada vértice (inicia todos com -1)
    vector<int> nivel(n+1, -1);

    // dicionário que mostra quais vértices estão em cada nível
    // (nível, (vector de vértices))
    map<int, vector<int>> niveis;

    // fila que mostra o próximo vértice a ser explorado
    queue<int> fila;

///// INICIALIZAR O ALGORITMO /////////////////////////////////////////////

    // marca o vértice inicial (s) como visitado
    visitado[s] = true;

    // marca o nível de s como zero
    nivel[s] = 0;

    // adiciona s na fila pra ser explorado
    fila.push(s);

    // adiciona (s) ao nível zero no dicionário
    niveis[0].push_back(s);

///// LAÇO PRINCIPAL DA BUSCA EM LARGURA //////////////////////////////////

    // enquanto ainda houver vértices a serem explorados
    while(!fila.empty()) {

        // pega o vértice da fila
        int u = fila.front();
        fila.pop();

        // pra cada vértice vizinho
        for (int v : g.vizinhos(u)) {

            // se o vizinho ainda não foi visitado
            if (!visitado[v]) {

                // passa a ser visitado
                visitado[v] = true;
                    
                // guarda seu nível
                nivel[v] = nivel[u] + 1;

                // adiciona na fila pra ser explorado
                fila.push(v);

                // adiciona no dicionário de níveis
                niveis[nivel[v]].push_back(v);

            }
        }
    }

///// IMPRESSÃO DO RESULTADO///////////////////////////////////////////////

    // para cada nível no dicionário
    for (auto& [nivelAtual, vertices] : niveis) {

        // imprime o nível
        cout << nivelAtual << ": ";

        // pra cada vértice nesse nível
        for (size_t i = 0; i < vertices.size(); i++) {

            // imprime o vértice
            cout << vertices[i];

            // imprime a vírgula se não for o último vértice
            if (i < vertices.size() - 1) cout << ",";

        }

        // imprime a quebra de linha entre os níveis
        cout << endl;

    }

    return 0;
}