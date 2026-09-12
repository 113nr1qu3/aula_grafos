#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "dag.h"

enum Cor { BRANCO = 0, CINZA = 1, PRETO = 2 };

GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->adj = (No**) calloc(num_vertices, sizeof(No*));
    return g;
}

void adicionar_aresta(GrafoLista *g, int orig, int dest) {
    if (!g || orig < 0 || orig >= g->num_vertices || dest < 0 || dest >= g->num_vertices) return;
    
    No *novo = (No*) malloc(sizeof(No));
    novo->destino = dest;
    novo->prox = g->adj[orig];
    g->adj[orig] = novo;
}

void destruir_grafo(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->adj[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

// Algoritmo de Kahn (BFS baseado no grau de entrada)
int* ordenacao_topologica_kahn(GrafoLista *g, int *tamanho) {
    if (!g || !tamanho) return NULL;

    int v = g->num_vertices;
    int *grau_entrada = (int*) calloc(v, sizeof(int));
    int *ordem = (int*) malloc(v * sizeof(int));
    int *fila = (int*) malloc(v * sizeof(int));
    int inicio = 0, fim = 0, idx = 0;

    // 1. Calcula os graus de entrada de cada vértice
    for (int i = 0; i < v; i++) {
        No *atual = g->adj[i];
        while (atual) {
            grau_entrada[atual->destino]++;
            atual = atual->prox;
        }
    }

    // 2. Insere na fila todos os vértices com grau de entrada 0
    for (int i = 0; i < v; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    // 3. Processamento BFS
    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[idx++] = u;

        No *atual = g->adj[u];
        while (atual) {
            int dest = atual->destino;
            grau_entrada[dest]--;
            if (grau_entrada[dest] == 0) {
                fila[fim++] = dest;
            }
            atual = atual->prox;
        }
    }

    free(grau_entrada);
    free(fila);

    // Se processou todos os vértices, não há ciclos
    if (idx == v) {
        *tamanho = idx;
        return ordem;
    }

    // Houve ciclo: desaloca e retorna NULL
    free(ordem);
    *tamanho = 0;
    return NULL;
}

// Função auxiliar DFS para detecção de ciclos e ordenação
static void dfs_visitar(GrafoLista *g, int u, int *cor, int *pilha, int *topo, bool *tem_ciclo) {
    if (*tem_ciclo) return;

    cor[u] = CINZA; // Marcado como "em visita"

    No *atual = g->adj[u];
    while (atual) {
        int dest = atual->destino;
        if (cor[dest] == CINZA) { // Aresta de retorno encontrada (ciclo)
            *tem_ciclo = true;
            return;
        }
        if (cor[dest] == BRANCO) {
            dfs_visitar(g, dest, cor, pilha, topo, tem_ciclo);
        }
        atual = atual->prox;
    }

    cor[u] = PRETO; // Finalizado
    pilha[(*topo)++] = u; // Empilha ao terminar o vértice
}

// Algoritmo DFS com pós-ordem invertida
int* ordenacao_topologica_dfs(GrafoLista *g, int *tamanho) {
    if (!g || !tamanho) return NULL;

    int v = g->num_vertices;
    int *cor = (int*) calloc(v, sizeof(int));
    int *pilha = (int*) malloc(v * sizeof(int));
    int topo = 0;
    bool tem_ciclo = false;

    for (int i = 0; i < v; i++) {
        if (cor[i] == BRANCO) {
            dfs_visitar(g, i, cor, pilha, &topo, &tem_ciclo);
            if (tem_ciclo) break;
        }
    }

    free(cor);

    if (tem_ciclo) {
        free(pilha);
        *tamanho = 0;
        return NULL;
    }

    // Inverte a pilha para obter a ordem correta
    int *ordem = (int*) malloc(v * sizeof(int));
    for (int i = 0; i < v; i++) {
        ordem[i] = pilha[topo - 1 - i];
    }

    free(pilha);
    *tamanho = v;
    return ordem;
}

// Verifica se é um DAG (Grafo Acíclico Dirigido)
bool eh_dag(GrafoLista *g) {
    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);
    if (ordem != NULL) {
        free(ordem);
        return true;
    }
    return false;
}