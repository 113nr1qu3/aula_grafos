#include "busca_profundidade.h"

// --- Funções da Pilha ---
Pilha* criar_pilha(int capacidade) {
    Pilha *p = (Pilha*) malloc(sizeof(Pilha));
    p->dados = (int*) malloc(capacidade * sizeof(int));
    p->topo = -1;
    p->capacidade = capacidade;
    return p;
}

void destruir_pilha(Pilha *p) {
    free(p->dados);
    free(p);
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void empilhar(Pilha *p, int v) {
    if (p->topo < p->capacidade - 1) {
        p->dados[++(p->topo)] = v;
    }
}

int desempilhar(Pilha *p) {
    if (pilha_vazia(p)) return -1;
    return p->dados[(p->topo)--];
}

// --- Algoritmos ---
void dfs_recursiva(GrafoLista *g, int u, int *visitado, int *pred) {
    visitado[u] = 1;
    for (No *atual = g->listas[u]; atual != NULL; atual = atual->prox) {
        int v = atual->vizinho;
        if (!visitado[v]) {
            if (pred != NULL) pred[v] = u;
            dfs_recursiva(g, v, visitado, pred);
        }
    }
}

int contar_componentes(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));
    int componentes = 0;

    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            componentes++;
            dfs_recursiva(g, i, visitado, NULL);
        }
    }
    free(visitado);
    return componentes;
}

static int tem_ciclo_rec(GrafoLista *g, int u, int *visitado, int pai) {
    visitado[u] = 1;
    for (No *atual = g->listas[u]; atual != NULL; atual = atual->prox) {
        int v = atual->vizinho;
        if (!visitado[v]) {
            if (tem_ciclo_rec(g, v, visitado, u)) return 1;
        } else if (v != pai) {
            return 1;
        }
    }
    return 0;
}

int tem_ciclo(GrafoLista *g) {
    int *visitado = (int*) calloc(g->num_vertices, sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) {
        if (!visitado[i]) {
            if (tem_ciclo_rec(g, i, visitado, -1)) {
                free(visitado);
                return 1;
            }
        }
    }
    free(visitado);
    return 0;
}