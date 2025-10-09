/*
#include <iostream>
#include <string>
#include <vector>
*/
#include "grafo.h"

using namespace std;

int main() {

    // feito por IA, só pra testar se compila

    // para compilar e rodar (no terminal):
    //   g++ -std=c++17 main.cpp -o main.exe
    //   .\main.exe

    // nome do arquivo de grafo
    string arquivo = "teste.txt";

    // cria o grafo a partir do arquivo
    Grafo g(arquivo);

    // imprime informações básicas
    cout << "Quantidade de vertices: " << g.qtdVertices() << endl;
    cout << "Quantidade de arestas: " << g.qtdArestas() << endl;

    // imprime rótulos e vizinhos de cada vértice
    for (int v = 1; v <= g.qtdVertices(); v++) {
        cout << "Vertice " << v << " (rotulo: " << g.rotulo(v) << "): ";
        vector<int> viz = g.vizinhos(v);
        cout << "Vizinhos -> ";
        for (int u : viz) {
            cout << u << "(peso=" << g.peso(v, u) << ") ";
        }
        cout << endl;
    }

    // exemplo de verificação de aresta
    int u = 1, w = 2;
    if (g.haAresta(u, w)) {
        cout << "Existe aresta entre " << u << " e " << w
             << " com peso " << g.peso(u, w) << endl;
    } else {
        cout << "Nao existe aresta entre " << u << " e " << w << endl;
    }

    return 0;
}
