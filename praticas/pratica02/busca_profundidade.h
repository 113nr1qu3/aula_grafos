#ifndef BUSCA_PROFUNDIDADE_H
#define BUSCA_PROFUNDIDADE_H

#include "busca_largura.h" // Importa GrafoLista e No

// Pilha (LIFO) para DFS iterativa
typedef struct {
    int *dados;
    int topo, capacidade;
} Pilha;

// Funções da Pilha
Pilha* criar_pilha(int capacidade);
void destruir_pilha(Pilha *p);
int pilha_vazia(Pilha *p);
void empilhar(Pilha *p, int v);
int desempilhar(Pilha *p);

// Funções de Busca em Profundidade e Aplicações
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred);
int contar_componentes(GrafoLista *g);
int tem_ciclo(GrafoLista *g);

#endif