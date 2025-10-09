#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

    // executa o algoritmo de floyd-warshall e retorna para cada vértice,
    // as distâncias entre ele e os outros vértices
    // em ordem crescente de índices
    // Pra rodar:
    // g++ floyd.cpp -o floyd
    // floyd.exe teste.txt

    // levanta erro caso não sejam passados os argumentos corretos
    if (argc < 2) {
        cerr << "Uso: " << argv[0] << " <arquivo_grafo>" << endl;
        return 1;
    }

///// LER O ARQUIVO E CRIAR O GRAFO ///////////////////////////////////////

    // cria o grafo a partir do arquivo passado
    Grafo g(argv[1]);

    // pega a quantidade de vértices
    int n = g.qtdVertices();

///// MATRIZ DE DISTÂNCIAS ////////////////////////////////////////////////

    // inicializa a matriz com infinito
    vector<vector<double>> dist(n+1, vector<double>(n+1, INF));

    // pra cada par de vértices
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {

            // copia o peso entre eles pra matriz
            dist[i][j] = g.peso(i, j);
        }
    }

///// ALGORITMO DE FLOYD-WARSHALL /////////////////////////////////////////

    // testa todos os vértices k como intermediários
    for (int k = 1; k <= n; k++) {
        
        // percorre todos os pares (passando por k) (i -> k -> j)
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {

                // se passar por k reduz a distância, atualiza
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

///// IMPRESSÃO DA SAÍDA /////////////////////////////////////////////////

    // para cada vértice de origem
    for (int i = 1; i <= n; i++) {

        // imprime o vértice:
        cout << i << ":";

        for (int j = 1; j <= n; j++) {

            // imprime a distância de i até j
            cout << dist[i][j];

            // se não for o último da linha, adiciona uma vírgula
            if (j != n) cout << ",";
        }

        cout << endl;
    }

    return 0;
}