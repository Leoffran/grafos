#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

// Pra rodar:
// g++ A2_3.cpp -o 3
// ./3.exe grafo.txt A F

// BFS usado pelo Edmonds-Karp. Preenche 'pai' e retorna o fluxo encontrado.
double bfs(int s, int t, vector<vector<double>> &cap, vector<int> &pai) {
    int n = cap.size();
    fill(pai.begin(), pai.end(), -1);
    pai[s] = -2; // para indicar início

    queue<pair<int, double>> q;
    q.push({s, INF});

    while (!q.empty()) {
        auto [u, fluxo] = q.front();
        q.pop();

        for (int v = 1; v < n; v++) {
            // se há capacidade residual
            if (pai[v] == -1 && cap[u][v] > 0) {
                pai[v] = u;
                double novo_fluxo = min(fluxo, cap[u][v]);
                if (v == t) return novo_fluxo;
                q.push({v, novo_fluxo});
            }
        }
    }
    return 0.0;
}

// Edmonds-Karp: fluxo máximo s -> t
double edmondsKarp(int s, int t, vector<vector<double>> cap) {
    int n = cap.size();
    vector<int> pai(n);
    double fluxo_max = 0;

    while (true) {
        double fluxo = bfs(s, t, cap, pai);
        if (fluxo == 0) break; // não há mais caminhos aumentantes
        fluxo_max += fluxo;

        // atualiza as capacidades residuais
        int v = t;
        while (v != s) {
            int u = pai[v];
            cap[u][v] -= fluxo;
            cap[v][u] += fluxo;
            v = u;
        }       
    }
    return fluxo_max;
}

int main(int argc, char* argv[]) {

    if (argc < 4) {
        cerr << "Uso: ./programa <arquivo_do_grafo> <origem> <destino>\n";
        return 1;
    }

    // cria o grafo
    Grafo g(argv[1]);
    int n = g.qtdVertices();

    // converte rótulos para índices
    string rotS = argv[2];
    string rotT = argv[3];

    int s = g.rotuloParaIndice[rotS];
    int t = g.rotuloParaIndice[rotT];

    vector<vector<double>> cap(n+1, vector<double>(n+1, 0));

    for (int u = 1; u <= n; u++) {
        for (auto [v, w] : g.adjacentes[u]) {
            cap[u][v] = w; // peso é a capacidade
        }
    }

    double fluxo_max = edmondsKarp(s, t, cap);

    cout << fluxo_max << endl;

    return 0;
}