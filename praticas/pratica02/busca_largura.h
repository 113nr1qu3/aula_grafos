#ifndef BUSCA_LARGURA_H
#define BUSCA_LARGURA_H

#include <stdio.h>
#include <stdlib.h>

// Estrutura do Grafo
typedef struct No {
    int vizinho;
    struct No *prox;
} No;

typedef struct {
    int num_vertices;
    No **listas;
} GrafoLista;

// Fila (FIFO) para BFS
typedef struct {
    int *dados;
    int capacidade, inicio, fim, tamanho;
} Fila;

// Funções do Grafo
GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int u, int v);
void destruir_grafo(GrafoLista *g);

// Funções da Fila
Fila* criar_fila(int capacidade);
void destruir_fila(Fila *f);
int fila_vazia(Fila *f);
void enfileirar(Fila *f, int v);
int desenfileirar(Fila *f);

// Funções de Busca em Largura e Aplicações
void bfs(GrafoLista *g, int origem, int *dist, int *pred);
int eh_bipartido(GrafoLista *g);

#endif