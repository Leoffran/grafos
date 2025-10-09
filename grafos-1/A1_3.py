import math
import sys

class Grafo:
    def __init__(self, arquivo=None):
        self.vertices = {}
        self.arestas = {}
        self.graus = {}
        self.rotulos = {}
        self.lista_vizinhos = {}
        
        if arquivo:
            self.ler(arquivo)
    
    def qtdVertices(self):
        return len(self.vertices)
    
    def qtdArestas(self):
        return len(self.arestas) // 2
    
    def grau(self, v):
        return self.graus.get(v, 0)
    
    def rotulo(self, v):
        return self.rotulos.get(v, "")
    
    def vizinhos(self, v):
        return self.lista_vizinhos.get(v, [])
    
    def haAresta(self, u, v):
        return (u, v) in self.arestas
    
    def peso(self, u, v):
        return self.arestas.get((u, v), math.inf)
    
    def ler(self, arquivo):
        with open(arquivo, 'r') as f:
            lines = f.readlines()
        
        mode = None
        for line in lines:
            line = line.strip()
            if not line:
                continue
            
            if line.startswith('*vertices'):
                mode = 'vertices'
                n = int(line.split()[1])
                for i in range(1, n+1):
                    self.vertices[i] = True
                    self.graus[i] = 0
                    self.lista_vizinhos[i] = []
                continue
            elif line.startswith('*edges'):
                mode = 'edges'
                continue
            
            if mode == 'vertices':
                parts = line.split(maxsplit=1)
                v = int(parts[0])
                rotulo = parts[1] if len(parts) > 1 else str(v)
                self.rotulos[v] = rotulo
            elif mode == 'edges':
                u, v, peso = line.split()
                u = int(u)
                v = int(v)
                peso = float(peso)
                self.arestas[(u, v)] = peso
                self.arestas[(v, u)] = peso
                self.lista_vizinhos[u].append(v)
                self.lista_vizinhos[v].append(u)
                self.graus[u] += 1
                self.graus[v] += 1

def grafo_conexo(grafo):
    if not grafo.vertices:
        return True
    
    visitados = {v: False for v in grafo.vertices}
    pilha = [next(iter(grafo.vertices))]
    visitados[pilha[0]] = True
    
    while pilha:
        u = pilha.pop()
        for v in grafo.vizinhos(u):
            if not visitados[v]:
                visitados[v] = True
                pilha.append(v)
    
    return all(visitados[v] for v in grafo.vertices if grafo.grau(v) > 0)

def tem_ciclo_euleriano(grafo):
    for v in grafo.vertices:
        if grafo.grau(v) % 2 != 0:
            return False
    if not grafo_conexo(grafo):
        return False
    return True

def encontrar_ciclo_euleriano(grafo):
    if not tem_ciclo_euleriano(grafo):
        return None
    
    arestas_restantes = {(u, v): True for (u, v) in grafo.arestas}
    ciclo = []
    pilha = []
    atual = next(iter(grafo.vertices))
    
    while True:
        vizinho = None
        for v in grafo.vizinhos(atual):
            if arestas_restantes.get((atual, v), False):
                vizinho = v
                break
        
        if vizinho is not None:
            pilha.append(atual)
            arestas_restantes[(atual, vizinho)] = False
            arestas_restantes[(vizinho, atual)] = False
            atual = vizinho
        else:
            ciclo.append(atual)
            if not pilha:
                break
            atual = pilha.pop()
    
    return ciclo

def main():
    if len(sys.argv) < 2:
        print("Uso: python3 programa.py <arquivo_grafo>")
        return
    
    arquivo = sys.argv[1]
    grafo = Grafo(arquivo)
    
    if tem_ciclo_euleriano(grafo):
        ciclo = encontrar_ciclo_euleriano(grafo)
        print(1)
        print(','.join(map(str, ciclo)))
    else:
        print(0)

if __name__ == "__main__":
    main()
