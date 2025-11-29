#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

// Vetor de distâncias usado no BFS do Hopcroft–Karp
vector<int> dist;

// matchL[u] = vértice da direita emparelhado com u (ou 0 se livre)
// matchR[v] = vértice da esquerda emparelhado com v (ou 0 se livre)
vector<int> matchL, matchR;

// Lista de adjacência apenas da parte L → R
vector<vector<int>> adjLR;

// Constante representando "infinito" para distâncias
const int INF_INT = 1e9;

// BFS de hopcraft-karp -> encontra todos os níveis das camadas de busca
bool bfsHK(int nL) {
    queue<int> q;

    // inicializa as distâncias
    // todos os vértices livres da parte L entra na fila com dist = 0
    for (int u = 1; u <= nL; u++) {
        if (matchL[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF_INT;
        }
    }

    int distInf = INF_INT;

    // BFS tradicional por camadas
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // somente continua se não chegamos ao nível final
        if (dist[u] < distInf) {
            for (int v : adjLR[u]) {
                int mu = matchR[v]; // vértice da esquerda pareado com v
                if (mu == 0) {
                    // vértice livre na direita -> fim do nível
                    distInf = dist[u] + 1;
                }
                else if (dist[mu] == INF_INT) {
                    // avançamos para o próximo nível
                    dist[mu] = dist[u] + 1;
                    q.push(mu);
                }
            }
        }
    }
    // se distInf ainda for infinito, nenhum caminho aumentante existe
    return distInf != INF_INT;
}

// DFS do hopcroft-karp
bool dfsHK(int u) {
    for (int v : adjLR[u]) {
        int mu = matchR[v]; // quem está pareado com v
        // caso 1: v está livre → podemos emparelhar u-v
        // caso 2: mu está no nível correto para continuar o caminho
        if (mu == 0 || (dist[mu] == dist[u] + 1 && dfsHK(mu))) {
            matchL[u] = v;
            matchR[v] = u;
            return true;
        }
    }
    // se não conseguimos avançar, descartamos este vértice
    dist[u] = INF_INT;
    return false;
}

int hopcroftKarp(int nL, int nR) {
    int matching = 0;
    // enquanto existirem caminhos aumentantes
    while (bfsHK(nL)) {
        // para cada vértice livre na parte L tenta buscar um caminho
        for (int u = 1; u <= nL; u++) {
            if (matchL[u] == 0 && dfsHK(u)) {
                matching++;
            }
        }
    }

    return matching;
}

int main(int argc, char* argv[]) {

    // Verificação de uso
    if (argc < 2) {
        cerr << "Uso: ./hk <arquivo_do_grafo>\n";
        return 1;
    }

    // Lê o grafo usando sua grafo.h
    Grafo g(argv[1]);
    int n = g.qtdVertices();

    // Define a bipartição conforme especificado:
    int nL = n / 2;          // Parte esquerda
    int nR = n - nL;         // Parte direita

    // Inicializa estruturas
    adjLR.assign(nL + 1, {});
    matchL.assign(nL + 1, 0);
    matchR.assign(nR + 1, 0);
    dist.assign(nL + 1, INF_INT);

    for (int u = 1; u <= nL; u++) {
        for (auto [v, w] : g.adjacentes[u]) {

            // Só consideramos arestas que levam até a parte R
            if (v >= nL + 1 && v <= n) {
                int vR = v - nL; // converte índice real para índice em R
                adjLR[u].push_back(vR);
            }
        }
    }

    // Calcula emparelhamento máximo
    int maxMatching = hopcroftKarp(nL, nR);

    cout << maxMatching << "\n";

    bool first = true;

    // matchL[u] guarda qual vR está pareado com u
    for (int u = 1; u <= nL; u++) {
        if (matchL[u] != 0) {
            int v = matchL[u] + nL; // converte vR para índice original

            if (!first) cout << ", ";
            cout << u << "-" << v;

            first = false;
        }
    }

    cout << "\n";
    return 0;
}