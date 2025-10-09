#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

    // roda o algoritmo de dijkstra e pra cada vértice encontrado
    // a partir da origem, imprime (destino, caminho, distância)
    // Pra rodar:
    // g++ dijkstra.cpp -o dijkstra
    // dijkstra.exe teste.txt <ÍNDICE DO VÉRTICE>


    // levanta erro caso não sejam passados os argumentos corretos
    if (argc < 3) {
        cerr << "Uso: " << argv[0] << " <arquivo_grafo> <vertice_origem>" << endl;
        return 1;
    } 

///// LER O ARQUIVO E CRIAR O GRAFO ///////////////////////////////////////

    // pega o arquivo do grafo e o vértice de origem
    string arquivo = argv[1];
    int origem = stoi(argv[2]);

    // cria o grafo a partir do arquivo e pega o número de vértices
    Grafo g(arquivo);
    int n = g.qtdVertices();

///// PREPARAÇÃO PARA DIJKSTRA ////////////////////////////////////////////
    
    // valor infinito pro algoritmo
    const double INF = std::numeric_limits<double>::infinity();

    // vetor de distâncias mínimas da origem pra cada vértice
    // inicializa todos com distância infinita
    vector<double> dist(n+1, INF);

    // vetor pra reconstruir o caminho de cada vértice até a origem
    vector<int> pai(n+1, -1);

    // distância da origem pra ele mesmo é zero
    dist[origem] = 0;

    // priority queue que armazena (distancia, índice do vértice)
    priority_queue<pair<double,int>, vector<pair<double,int>>, greater<>> pq;
    
    // distância da origem pra ele mesmo é zero
    pq.push({0, origem});

///// DIJKSTRA ////////////////////////////////////////////////////////////
    
    // enquanto a fila não estiver vazia
    while (!pq.empty()) {
        
        // retira da fila o vértice com menor distância conhecida
        auto [d, u] = pq.top();
        pq.pop();

        // se a distância retirada da fila for maior do que a já registrada, ignora
        // isso pode acontecer por entradas antigas na fila
        if (d > dist[u]) continue;

        // percorre todos os vizinhos de u
        for (auto [v, peso] : g.adjacentes[u]) {

            // se a distância atual for maior que a distância testada
            if (dist[v] > dist[u] + peso) {

                // atualiza a menor distância
                dist[v] = dist[u] + peso;

                // atualiza o predecessor
                pai[v] = u;

                // insere v na fila de prioridade
                pq.push({dist[v], v});
            }
        }
    }

///// IMPRESSÃO ///////////////////////////////////////////////////////////

    // pra cada vértice
    for (int v = 1; v <= n; v++) {

        // se a distância até um vértice for infinita, é inatingível
        if (dist[v] == INF) {
            cout << v << ": inatingível" << endl;
        }

        // reconstrução do caminho de origem até v
        vector<int> caminho;

        // varre do final até a origem pelos pais,
        // o pai da origem é -1
        for (int x = v; x != -1; x = pai[x]) {

            // adiciona o vértice ao caminho
            caminho.push_back(x);
        }

        // coloca na ordem correta
        reverse(caminho.begin(), caminho.end());

        // imprime o caminho no formato: destino: caminho; d=distância
        cout << v << ": ";
        for (size_t i = 0; i < caminho.size(); i++) {
            cout << caminho[i];

            // imprime a vírgula se não for o último vértice
            if (i < caminho.size() - 1) cout << ",";
        }
        cout << "; d=" << dist[v] << endl;
    }
    
    return 0;
}