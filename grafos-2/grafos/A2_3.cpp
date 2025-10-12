#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Pra rodar:
    // g++ A2_3.cpp -o 3
    // .\3.exe teste.txt

    // Verifica se o arquivo foi passado como argumento
    if (argc < 2) {
        cerr << "Uso: ./programa <arquivo_do_grafo>" << endl;
        return 1;
    }

    // cria o grafo
    Grafo g(argv[1]);
    int n = g.qtdVertices();

///// LISTA DE TODAS AS ARESTAS ///////////////////////////////////////////
    
    // vetor que armazenará as arestas do grafo no formato {peso, u, v}
    vector<vector<double>> arestas;

    // percorre todos os vértices do grafo
    for (int u = 1; u <= n; u++) {

        // para cada adjacente:
        // (v = vértice de destino)
        // (w = peso da aresta u-v)
        for (auto [v, w] : g.adjacentes[u]) {

            // como o grafo e não dirigido, cada aresta aparece duas vezes (u->v e v->u)
            // para evitar duplicação, só adiciona se u < v
            if (u < v) {

                // converte tudo pra double e insere no vetor
                arestas.push_back({w, (double)u, (double)v});
            }
        }
    }

    // ordena pelo peso
    sort(arestas.begin(), arestas.end());

///// INICIALIZA OS CONJUNTOS PARA KRUSKAL ////////////////////////////////

    // cada vértice começa no seu próprio conjunto
    vector<int> conjunto(n + 1);
    for (int i = 1; i <= n; i++) conjunto[i] = i;

///// EXECUTA KRUSKAL /////////////////////////////////////////////////////

    // soma do peso total da mst (Minimum Spanning Tree) (Árvore Geradora Mínima)
    double pesoTotal = 0;

    // armazena as arestas da MST
    vector<pair<int,int>> mst;

    // para cada aresta
    for (auto &a : arestas) {

        // pega o vértice u
        int u = (int)a[1];

        // pega o vértice v
        int v = (int)a[2];

        // pega o peso w
        double w = a[0];

        // inicializa o representante de u com u
        int cu = u;

        // enquanto cu não for o representante do conjunto
        // seguimos o ponteiro para o representante
        while (conjunto[cu] != cu) cu = conjunto[cu];

        // inicializa o representante de v com v
        int cv = v;

        // enquanto cu não for o representante do conjunto
        // seguimos o ponteiro para o representante
        while (conjunto[cv] != cv) cv = conjunto[cv];

        // se u e v pertencem a conjuntos diferentes
        if (cu != cv) {

            // adiciona na árvore
            mst.push_back({u, v});

            // acumula peso
            pesoTotal += w;

            // une os conjuntos
            for (int i = 1; i <= n; i++) {
                if (conjunto[i] == cv) conjunto[i] = cu;
            }
        }
    }

///// IMPRIME O RESULTADO /////////////////////////////////////////////////

    // imprime o peso
    cout << pesoTotal << endl;

    // para cada aresta
    for (size_t i = 0; i < mst.size(); i++) {

        // imprime seus u-v
        cout << mst[i].first << "-" << mst[i].second;

        // imprime uma vírgula entre elas
        if (i < mst.size() - 1) cout << ", ";
    }
    cout << endl;

    return 0;
}