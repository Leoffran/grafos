#include <bits/stdc++.h>
#include "grafo.h"

using namespace std;

int main(int argc, char* argv[]) {

    // Se houver ciclo euleriano imprime 1 e os vértices que o compõem, 
    // caso contrário imprime zero
    // Pra rodar:
    // g++ euleriano.cpp -o euleriano
    // euleriano.exe teste2.txt

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

    // vetor que marca true se um vertice já foi visitado
    vector<bool> visitado(n+1, false);
    
    // variável pra armazenar vertice de partida da BFS
    int start = -1;

    // encontra o primeiro vértice com grau > 0 para iniciar a BFS
    for (int i = 1; i <= n; i++) {
        if (g.grau(i) > 0) { 
            start = i; 
            break; 
        }
    }

    // se não houver nenhum vértice com arestas, grafo não tem ciclo Euleriano
    if (start == -1) { 
        cout << "0" << endl;
        return 0;
    }

///// INICIALIZAR O ALGORITMO DA BUSCA EM LARGURA /////////////////////////

    // fila pra guardar os vertices a serem explorados
    queue<int> fila;

    // marca o vértice inicial (s) como visitado
    visitado[start] = true;

    // adiciona s na fila pra ser explorado
    fila.push(start);


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

                // adiciona na fila pra ser explorado
                fila.push(v);

            }
        }
    }

///// VERIFICAÇÕES NECESSÁRIAS PRA CICLO EULERIANO ////////////////////////

    // verifica se todos os vertices com grau > foram visitados
    bool conexo = true;
    for (int i = 1; i <= n; i++) {
        if (g.grau(i) > 0 && !visitado[i]) {
            conexo = false;
            break;
        }
    }

    // se o grafo não for conexo, não existe ciclo euleriano
    if (!conexo) {
        cout << "0" << endl;
        return 0;
    }

    // verifica se todos os vértices têm grau par
    // o ciclo euleriano só existe se todos os graus forem pares
    bool graus_pares = true;
    for (int i = 1; i <=n; i++) {
        if (g.grau(i) % 2 != 0) {
            graus_pares = false;
            break;
        }
    }

    // se houver grau ímpar, não existe ciclo euleriano
    if (!graus_pares) {
        cout << "0" << endl;
        return 0;
    }

    // copia da lista de adjacência dos vértices
    // multiset pra permitir arestas repetidas (multigrafo)
    vector<multiset<int>> adj(n+1);
    for (int u = 0; u <= n; u++) {
        for (int v : g.vizinhos(u)) {
            adj[u].insert(v);
        }
    }

///// ESTRUTURAS AUXILIARES //////////////////////////////////////////////

    // pilha pra explorar os vértices
    stack<int> pilha;

    // vector pra guardar a ordem dos vértices do ciclo
    vector<int> ciclo;

    // começa pelo vértice inicial
    pilha.push(start);


///// ALGORITMO DE HIERHOLZER ////////////////////////////////////////////

    // enquanto ainda houverem vertices a ser explorados
    while (!pilha.empty()) {

        // pega o vértice do topo da pilha
        int u = pilha.top();

        // se houver vértices vizinhos
        if (!adj[u].empty()) {

            // pega um vizinho (v) qualquer de u
            int v = *adj[u].begin();

            // remove as arestas de u pra v e de v pra u
            adj[u].erase(adj[u].begin());
            adj[v].erase(adj[v].find(u));
            
            // anda pra v
            pilha.push(v);
        
        // se não houver vértices vizinhos
        } else {

            // terminou as arestas de u
            ciclo.push_back(u);
            
            // remove da pilha
            pilha.pop();

        }
    }

    // ajeitar a ordem porque foi construído "de trás pra frente"
    reverse(ciclo.begin(), ciclo.end());

///// IMPRESSÃO DA SAÍDA /////////////////////////////////////////////////

    // indica que o ciclo foi encontrado
    cout << "1" << endl;

    // imprime os elementos do ciclo
    for (size_t i = 0; i < ciclo.size(); i++) {
        cout << ciclo[i];

        // imprime a vírgula se não for o último vértice
        if (i < ciclo.size() - 1) cout << ",";
    }

    return 0;
}