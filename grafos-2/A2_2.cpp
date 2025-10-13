#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

// Pra rodar:
// g++ A2_2.cpp -o 2
// .\2.exe teste.txt

void dfsTopologica(int v, const vector<vector<int>>& adj, vector<bool>& visitado, stack<int>& ordem) {

    // marca o vértice atual como visitado
    visitado[v] = true;

    // visita todos os vizinhos do vértice v
    for (int u : adj[v]) {
        if (!visitado[u]) dfsTopologica(u, adj, visitado, ordem);
    }

    // após todos os descendentes, empilha o vértice
    ordem.push(v);
}

int main(int argc, char* argv[]) {

    // Verifica se o arquivo foi passado como argumento
    if (argc < 2) {
        cerr << "Uso: ./programa <arquivo_do_grafo>" << endl;
        return 1;
    }

    // cria o grafo
    Grafo g(argv[1]);
    int n = g.qtdVertices();

///// MONTA A LISTA DE ADJACÊNCIA /////////////////////////////////////////

    // lista de adjacência
    vector<vector<int>> adj(n+1);

    // para cada vértice i:
    for (int i = 1; i <= n; i++) {

        // para cada vértice adjacente (ignorando o peso)
        for (auto [j, peso] : g.adjacentes[i]) {

            // adiciona o vértice j à lista de adjacência de i
            // (i -> j)
            adj[i].push_back(j); 
        }
    }

///// DFS (ORDENAÇÃO TOPOLÓGICA) //////////////////////////////////////////

    // vetor pra marcar quais vértices já foram visitados
    vector<bool> visitado(n + 1, false);

    // pilha pra armazenar a orde de término (pós ordem) da DFS
    stack<int> ordem;

    // para cada vértice i do grafo
    for (int i = 1; i <= n; i++) {

        // se i ainda não foi visitado, executa a dfs a partir dele
        if (!visitado[i]) dfsTopologica(i, adj, visitado, ordem);
    }

///// PREPARA OS RÓTULOS PRA IMPRESSÃO ////////////////////////////////////

    // vetor pra armazenar os rótulos na ordem topológica final
    vector<string> rotulos;

    // retira os vértices da pilha e armazena seus rótulos
    while(!ordem.empty()) {

        // obtém o rótulo do vértice
        rotulos.push_back(g.rotulo(ordem.top()));

        // remove o vértice da pilha
        ordem.pop();
    }

///// IMPRIME A ORDEM TOPOLÓGICA //////////////////////////////////////////

    // percorre os rótulos e imprime separados por vírgula e espaço
    for (size_t i = 0; i < rotulos.size(); i++) {

        // imprime o rótulo
        cout << rotulos[i];

        // vírgula entre rótulos
        if (i < rotulos.size() - 1) cout << " , ";
    }
    cout << endl;

    return 0;
}