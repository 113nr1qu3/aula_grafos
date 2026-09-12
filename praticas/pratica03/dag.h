#ifndef DAG_H
#define DAG_H

#include <stdbool.h>

// Estrutura para os nós da lista de adjacência
typedef struct No {
    int destino;
    struct No *prox;
} No;

// Estrutura do Grafo representado por Lista de Adjacência
typedef struct {
    int num_vertices;
    No **adj;
} GrafoLista;

// Funções de manipulação do Grafo
GrafoLista* criar_grafo(int num_vertices);
void adicionar_aresta(GrafoLista *g, int orig, int dest);
void destruir_grafo(GrafoLista *g);

// Funções da Prática
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho);
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho);
bool eh_dag(GrafoLista *g);

#endif // DAG_H