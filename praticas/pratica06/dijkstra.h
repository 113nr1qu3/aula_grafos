#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF INT_MAX

// Estrutura para os nós da lista de adjacência
typedef struct Aresta {
    int destino;
    int peso;
    struct Aresta *prox;
} Aresta;

// Estrutura do Grafo com Lista de Adjacência
typedef struct {
    int num_vertices;
    Aresta **adj;
} GrafoListaPonderado;

// Estruturas obrigatórias da prática
typedef struct {
    int vertice;
    int distancia;
} NoHeap;

typedef struct {
    NoHeap *dados;
    int capacidade;
    int tamanho;
    int *posicao; // mapeia vértice -> índice no heap
} MinHeap;

// Protótipos das funções do Grafo
GrafoListaPonderado* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso);
void liberar_grafo(GrafoListaPonderado *g);

// Protótipos das funções da Heap
MinHeap* criar_min_heap(int capacidade);
void trocar_nos(MinHeap *heap, int i, int j);
void heapify(MinHeap *heap, int idx);
NoHeap extrair_minimo(MinHeap *heap);
void diminuir_chave(MinHeap *heap, int vertice, int nova_dist);
int esta_na_heap(MinHeap *heap, int vertice);
void liberar_heap(MinHeap *heap);

// Algoritmo de Dijkstra e Reconstrução
void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred);
void reconstruir_caminho(int origem, int destino, int *pred);

#endif