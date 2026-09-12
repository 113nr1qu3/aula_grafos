#include "busca_largura.h"

// --- Funções Auxiliares do Grafo ---
GrafoLista* criar_grafo(int num_vertices) {
    GrafoLista *g = (GrafoLista*) malloc(sizeof(GrafoLista));
    g->num_vertices = num_vertices;
    g->listas = (No**) calloc(num_vertices, sizeof(No*));
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v) {
    No *novo1 = (No*) malloc(sizeof(No));
    novo1->vizinho = v;
    novo1->prox = g->listas[u];
    g->listas[u] = novo1;

    No *novo2 = (No*) malloc(sizeof(No));
    novo2->vizinho = u;
    novo2->prox = g->listas[v];
    g->listas[v] = novo2;
}

void destruir_grafo(GrafoLista *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        No *atual = g->listas[i];
        while (atual) {
            No *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listas);
    free(g);
}

// --- Funções da Fila ---
Fila* criar_fila(int capacidade) {
    Fila *f = (Fila*) malloc(sizeof(Fila));
    f->dados = (int*) malloc(capacidade * sizeof(int));
    f->capacidade = capacidade;
    f->inicio = 0;
    f->fim = -1;
    f->tamanho = 0;
    return f;
}

void destruir_fila(Fila *f) {
    free(f->dados);
    free(f);
}

int fila_vazia(Fila *f) {
    return f->tamanho == 0;
}

void enfileirar(Fila *f, int v) {
    if (f->tamanho == f->capacidade) return;
    f->fim = (f->fim + 1) % f->capacidade;
    f->dados[f->fim] = v;
    f->tamanho++;
}

int desenfileirar(Fila *f) {
    if (fila_vazia(f)) return -1;
    int v = f->dados[f->inicio];
    f->inicio = (f->inicio + 1) % f->capacidade;
    f->tamanho--;
    return v;
}

// --- Algoritmos ---
void bfs(GrafoLista *g, int origem, int *dist, int *pred) {
    for (int i = 0; i < g->num_vertices; i++) {
        dist[i] = -1;
        pred[i] = -1;
    }

    Fila *f = criar_fila(g->num_vertices);
    dist[origem] = 0;
    enfileirar(f, origem);

    while (!fila_vazia(f)) {
        int u = desenfileirar(f);
        for (No *atual = g->listas[u]; atual != NULL; atual = atual->prox) {
            int v = atual->vizinho;
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                pred[v] = u;
                enfileirar(f, v);
            }
        }
    }
    destruir_fila(f);
}

int eh_bipartido(GrafoLista *g) {
    int *cor = (int*) malloc(g->num_vertices * sizeof(int));
    for (int i = 0; i < g->num_vertices; i++) cor[i] = -1;

    Fila *f = criar_fila(g->num_vertices);

    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] == -1) {
            cor[i] = 0;
            enfileirar(f, i);

            while (!fila_vazia(f)) {
                int u = desenfileirar(f);
                for (No *atual = g->listas[u]; atual != NULL; atual = atual->prox) {
                    int v = atual->vizinho;
                    if (cor[v] == -1) {
                        cor[v] = 1 - cor[u];
                        enfileirar(f, v);
                    } else if (cor[v] == cor[u]) {
                        free(cor);
                        destruir_fila(f);
                        return 0;
                    }
                }
            }
        }
    }
    free(cor);
    destruir_fila(f);
    return 1;
}