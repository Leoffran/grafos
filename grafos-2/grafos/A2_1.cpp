#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

// Pra rodar:
// g++ A2_1.cpp -o 1
// .\1.exe teste.txt

// executa uma dfs (busca em profundidade) para definir a ordem que os vértices serão visitados
void dfsOrdem(int v, const vector<vector<int>>& adj, vector<bool>& visitado, stack<int>& ordem) {

    // marca o vértice atual como visitado
    visitado[v] = true;

    // para cada vértice adjacente a v:
    for (int u : adj[v]) {

        // se ele não foi visitado, executa a dfs a partir dele
        if (!visitado[u]) dfsOrdem(u, adj, visitado, ordem);
    }

    // depois de processar os vizinhos, adiciona v a ordem (ou seja: pós-ordem)
    ordem.push(v);
}

// executa uma dfs (busca em profundidade) para pegar uma componente fortemente conexa
void dfsComponente(int v, const vector<vector<int>>& adjT, vector<bool>& visitado, vector<int>& componente) {

    // marca o vértice atual como visitado
    visitado[v] = true;

    // adiciona o vértice ao componente
    componente.push_back(v);

    // pra cada vértice adjacente a v:
    for (int u : adjT[v]) {

        // se não foi visitado, realiza a dfs a partir dele
        if (!visitado[u]) dfsComponente(u, adjT, visitado, componente);
    }
}

int main(int argc, char* argv[]) {

    // Verifica se o arquivo foi passado como argumento
    if (argc < 2) {
        cerr << "Uso: ./programa <arquivo_do_grafo>" << endl;
        return 1;
    }

    // cria o grafo com a biblioteca
    Grafo g(argv[1]);

    // obtém o número de vértices
    int n = g.qtdVertices();

    //// monta a lista de adjacência
    vector<vector<int>> adj(n + 1);
    
    // para cada vértice
    for (int i = 1; i <= n; i++) {

        // se houver uma aresta entre ele e outro vértice
        for (int j = 1; j <= n; j++) {
            if (g.haAresta(i, j) && i != j) {

                // adiciona a direção i -> j
                adj[i].push_back(j);
            }
        }
    }
    
///// PRIMEIRA DFS (CALCULAR A ORDEM) /////////////////////////////////////

    // vector pra marcar se o vértice foi visitado
    vector<bool> visitado(n + 1, false);

    // stack pra mostrar a ordem dos vértices a serem visitados
    stack<int> ordem;

    // para cada vértice do grafo
    for (int i = 1; i <= n; i++) {

        // se o vértice ainda não foi visitado
        if (!visitado[i]) {

            // chama a dfs recursiva que percorre todos os vértices alcançáveis a partir de i
            // e empilha a ordem (pós-ordem)
            dfsOrdem(i, adj, visitado, ordem);
        }
    }

///// CRIA O GRAFO TRANSPOSTO /////////////////////////////////////////////

    // matriz do grafo transposto
    vector<vector<int>> adjT(n + 1);

    // para cada vértice v
    for (int v = 1; v <= n; v++) {

        // para cada u adjacente
        for (int u : adj[v]) {

            // adiciona a aresta invertida
            adjT[u].push_back(v);
        }
    }

///// SEGUNDA DFS (COMPONENTES CONEXOS) ///////////////////////////////////

    // marca os vértices como não visitados para o grafo transposto
    fill(visitado.begin(), visitado.end(), false);

    // enquanto houverem vértices a serem visitados
    while (!ordem.empty()) {

        // pega o vértice do topo da pilha
        int v = ordem.top();
        ordem.pop();

        // se o vértice ainda não foi visitado
        if (!visitado[v]) {

            // vetor pra armazenar todos os vértices da componente atual
            vector<int> componente;

            // executa a DFS no grafo transposto a partir de v
            // todos os vértices alcançáveis formam uma componente
            dfsComponente(v, adjT, visitado, componente);

            // ordena pra que a saída seja consistente
            sort(componente.begin(), componente.end());

            // para cada vértice no componente
            for (size_t k = 0; k < componente.size(); k++) {

                // imprime seu rótulo
                cout << g.rotulo(componente[k]);

                // vírgula entre vértices
                if (k < componente.size() - 1) cout << ",";
            }
            // pula a linha após cada componente
            cout << "\n";
        }

    }

    // animação para estudos: https://www.youtube.com/watch?v=wCFA5CQMVGA
    return 0;
}