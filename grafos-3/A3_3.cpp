#include <bits/stdc++.h>
#include "grafo.h"
using namespace std;

// verifica se conjunto S (bitmask) é estável (conjunto independente)
bool ehEstavel(int S, const vector<vector<int>> &adj, int n) {
    for (int i = 0; i < n; i++) {
        if (S & (1 << i)) {
            for (int j : adj[i]) {
                if (S & (1 << j)) return false;
            }
        }
    }
    return true;
}

// gera todos subconjuntos de S
vector<int> subConjuntos(int S) {
    vector<int> subs;
    int T = S;
    while (T) {
        subs.push_back(T);
        T = (T - 1) & S;
    }
    // Inclui o conjunto vazio se necessário
    // subs.push_back(0);
    return subs;
}

// Lawler DP com reconstrução da coloração
pair<int, vector<int>> lawlerColoring(int n, const vector<vector<int>> &adj) {
    int N = 1 << n;
    vector<int> dp(N, INT_MAX);
    vector<int> estavel(N, 0);
    vector<int> escolha(N, 0);

    // Pré-computa quais conjuntos são estáveis
    for (int S = 0; S < N; S++) {
        estavel[S] = ehEstavel(S, adj, n);
    }

    dp[0] = 0;

    for (int S = 1; S < N; S++) {
        // Gera todos os subconjuntos de S
        vector<int> subs = subConjuntos(S);
        for (int T : subs) {
            if (!estavel[T]) continue;
            int resto = S ^ T;
            if (dp[resto] != INT_MAX && 1 + dp[resto] < dp[S]) {
                dp[S] = 1 + dp[resto];
                escolha[S] = T;
            }
        }
    }

    // reconstruir coloração
    vector<int> cores(n, 0);
    int S = N - 1;
    int cor = 1;
    while (S) {
        int T = escolha[S];
        for (int i = 0; i < n; i++) {
            if (T & (1 << i)) cores[i] = cor;
        }
        S ^= T;
        cor++;
    }

    return {dp[N-1], cores};
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "Uso: ./lawler <arquivo_do_grafo>\n";
        return 1;
    }

    Grafo g(argv[1]);
    
    // Verifica se o grafo é não-dirigido
    if (g.ehDirecionado()) {
        cerr << "Erro: O grafo deve ser não-dirigido!" << endl;
        return 1;
    }
    
    int n = g.qtdVertices();
    
    // Construir lista de adjacência (índices 0-based)
    vector<vector<int>> adj(n);
    for (int u = 1; u <= n; u++) {
        for (auto [v, w] : g.adjacentes[u]) {
            // Garantir que não há duplicatas
            if (find(adj[u-1].begin(), adj[u-1].end(), v-1) == adj[u-1].end()) {
                adj[u-1].push_back(v-1);
            }
        }
    }

    auto [chrom, cores] = lawlerColoring(n, adj);

    // Imprime o número cromático
    cout << chrom << endl;
    
    // Imprime as cores de cada vértice
    for (int i = 0; i < n; i++) {
        cout << cores[i];
        if (i != n-1) cout << ", ";
    }
    cout << endl;

    return 0;
}