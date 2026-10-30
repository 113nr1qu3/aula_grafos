#include "dijkstra.h"

// --- Funções do Grafo ---

GrafoListaPonderado* criar_grafo(int num_vertices) {
    GrafoListaPonderado *g = (GrafoListaPonderado*) malloc(sizeof(GrafoListaPonderado));
    g->num_vertices = num_vertices;
    g->adj = (Aresta**) malloc(num_vertices * sizeof(Aresta*));
    for (int i = 0; i < num_vertices; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoListaPonderado *g, int u, int v, int peso) {
    Aresta *nova = (Aresta*) malloc(sizeof(Aresta));
    nova->destino = v;
    nova->peso = peso;
    nova->prox = g->adj[u];
    g->adj[u] = nova;
}

void liberar_grafo(GrafoListaPonderado *g) {
    for (int i = 0; i < g->num_vertices; i++) {
        Aresta *atual = g->adj[i];
        while (atual) {
            Aresta *temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->adj);
    free(g);
}

// --- Funções da MinHeap ---

MinHeap* criar_min_heap(int capacidade) {
    MinHeap *heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->capacidade = capacidade;
    heap->tamanho = 0;
    heap->dados = (NoHeap*) malloc(capacidade * sizeof(NoHeap));
    heap->posicao = (int*) malloc(capacidade * sizeof(int));
    for (int i = 0; i < capacidade; i++) {
        heap->posicao[i] = -1;
    }
    return heap;
}

void trocar_nos(MinHeap *heap, int i, int j) {
    heap->posicao[heap->dados[i].vertice] = j;
    heap->posicao[heap->dados[j].vertice] = i;

    NoHeap temp = heap->dados[i];
    heap->dados[i] = heap->dados[j];
    heap->dados[j] = temp;
}

void heapify(MinHeap *heap, int idx) {
    int menor = idx;
    int esq = 2 * idx + 1;
    int dir = 2 * idx + 2;

    if (esq < heap->tamanho && heap->dados[esq].distancia < heap->dados[menor].distancia)
        menor = esq;

    if (dir < heap->tamanho && heap->dados[dir].distancia < heap->dados[menor].distancia)
        menor = dir;

    if (menor != idx) {
        trocar_nos(heap, idx, menor);
        heapify(heap, menor);
    }
}

NoHeap extrair_minimo(MinHeap *heap) {
    if (heap->tamanho == 0) {
        NoHeap vazio = {-1, -1};
        return vazio;
    }

    NoHeap raiz = heap->dados[0];
    NoHeap ultimo_no = heap->dados[heap->tamanho - 1];

    heap->dados[0] = ultimo_no;
    heap->posicao[raiz.vertice] = -1;
    heap->posicao[ultimo_no.vertice] = 0;

    heap->tamanho--;
    heapify(heap, 0);

    return raiz;
}

void diminuir_chave(MinHeap *heap, int vertice, int nova_dist) {
    int i = heap->posicao[vertice];
    heap->dados[i].distancia = nova_dist;

    while (i > 0 && heap->dados[i].distancia < heap->dados[(i - 1) / 2].distancia) {
        trocar_nos(heap, i, (i - 1) / 2);
        i = (i - 1) / 2;
    }
}

int esta_na_heap(MinHeap *heap, int vertice) {
    return heap->posicao[vertice] != -1;
}

void liberar_heap(MinHeap *heap) {
    free(heap->dados);
    free(heap->posicao);
    free(heap);
}

// --- Algoritmo de Dijkstra ---

void dijkstra(GrafoListaPonderado *g, int origem, int *dist, int *pred) {
    int V = g->num_vertices;
    MinHeap *heap = criar_min_heap(V);

    for (int v = 0; v < V; v++) {
        dist[v] = INF;
        pred[v] = -1;
        heap->dados[v].vertice = v;
        heap->dados[v].distancia = INF;
        heap->posicao[v] = v;
    }

    dist[origem] = 0;
    heap->dados[origem].distancia = 0;
    heap->tamanho = V;

    diminuir_chave(heap, origem, 0);

    while (heap->tamanho > 0) {
        NoHeap min_no = extrair_minimo(heap);
        int u = min_no.vertice;

        if (dist[u] == INF) break;

        Aresta *atual = g->adj[u];
        while (atual != NULL) {
            int v = atual->destino;
            int peso = atual->peso;

            if (esta_na_heap(heap, v) && dist[u] != INF && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                pred[v] = u;
                diminuir_chave(heap, v, dist[v]);
            }
            atual = atual->prox;
        }
    }

    liberar_heap(heap);
}

void reconstruir_caminho(int origem, int destino, int *pred) {
    if (origem == destino) {
        printf("%d", origem);
        return;
    }

    if (pred[destino] == -1) {
        printf("Não existe caminho entre %d e %d.\n", origem, destino);
        return;
    }

    // Pilha auxiliar para inverter a ordem dos predecessores
    int caminho[1000];
    int tam = 0;
    int atual = destino;

    while (atual != -1) {
        caminho[tam++] = atual;
        atual = pred[atual];
    }

    printf("Caminho: ");
    for (int i = tam - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
}