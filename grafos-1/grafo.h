#pragma once

#include <bits/stdc++.h>
/*
#include <iostream>    
#include <fstream>     
#include <sstream>    
#include <string>  
#include <vector>       
#include <utility>     
#include <limits>
*/

using namespace std;

// variável pra representar o infinito
inline constexpr double INF = std::numeric_limits<double>::infinity();

// Representação de um grafo
class Grafo {
    
    // vértices
    int n;

    // arestas
    int m;

    // vetor que armazena o rótulo de cada vertice
    vector<string> labels;

    // matriz pra armazenar as distancias entre os vertices
    // (vertice1, vertice2, distancia)
    vector<vector<double>> matriz; 

    // precisa desses 2 armazenamentos diferentes porque o professor pede pra otimizar quando puder

public:

    // vetor para cada vértice que contém os pares (vertice, "distância")
    vector<vector<pair<int,double>>> adjacentes;

    // lê o arquivo e inicializa tudo
    Grafo(string arquivo) {
        
        //// abre o arquivo pra leitura
        ifstream in(arquivo);

        // verifica se abriu corretamente
        if (!in.is_open()) {
            cerr << "Erro ao abrir o arquivo: " << arquivo << endl;
            exit(1);
        }

        string linha;

        //// pega a primeira linha inteira
        getline(in, linha);
        stringstream ss(linha);

        // pra receber "*vertices"
        string temp;

        // pega o número de vértices
        ss >> temp >> n;
        
        //// inicializa as estruturas de dados com os tamanhos corretos

        // label dos rótulos (vai de 1 a n)
        labels.resize(n+1);

        // lista de adjacência vazia pra cada vértice
        adjacentes.assign(n+1, {});

        // matriz inicializada com infinito em cada posição
        matriz.assign(n+1, vector<double>(n+1, INF));

        //// distância entre cada vértice pra ele mesmo é 0
        for (int i = 0; i <= n; i++) {
            matriz[i][i] = 0;
        }

        //// lê os rótulos de cada vértice
        for (int i = 1; i <= n; i++) {

            // lê a linha inteira
            getline(in, linha);

            // cria um stream pra separar índice e rótulo
            stringstream ss_vertice(linha);

            // cria as variáveis
            int index;
            string label;

            // separa índice e rótulo
            ss_vertice >> index >> label;

            // armazena o rótulo
            labels[index] = label;
        }

        // pega a linha "*edges" e ignora
        getline(in, linha);

        // inicializa o número de arestas com 0
        m = 0;

        //// lê todas as arestas até o final do arquivo
        while (getline(in, linha)) {

            // toda vez que ficar nesse loop conta uma aresta
            m++;

            // cria um stream pra pegar as arestas
            stringstream ss_aresta(linha);

            // os dois vértices
            int u, v;

            // o peso da aresta entre eles
            double w;

            // pega os vértices e o peso da stream
            ss_aresta >> u >> v >> w;

            // adiciona na lista de adjacência
            adjacentes[u].push_back({v, w});
            adjacentes[v].push_back({u, w});

            // adiciona na matriz de adjacência
            matriz[u][v] = w;
            matriz[v][u] = w;
        }

        // fecha o arquivo
        in.close();
    };
    
    // retorna a quantidade de vértices
    int qtdVertices() {
        return n;
    }

    // retorna a quantidade de arestas
    int qtdArestas() {
        return m;
    }
    
    // retorna o grau de um vértice
    int grau(int v) {
        return adjacentes[v].size();
    }

    // retorna o rotulo de um vértice
    string rotulo(int v) {
        return labels[v];
    }

    // retorna os vizinhos
    vector<int> vizinhos(int v) {
        vector<int> res;
        for (auto [vizinho, peso] : adjacentes[v]) {
            res.push_back(vizinho);
        }
        return res;
    }

    // retorna true se houver uma aresta
    bool haAresta(int u, int v) {

        // retorna true se a distância entre 2 vértices é diferente de infinito
        return matriz[u][v] != INF;
    }

    // retorna o peso da aresta (u, v), se não houver retorna infinito
    double peso(int u, int v) {
        return matriz[u][v];
    }

};