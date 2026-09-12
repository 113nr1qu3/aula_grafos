#include <stdio.h>
#include <stdlib.h>
#include "busca_largura.h"
#include "busca_profundidade.h"

int main() {
    int n = 6;
    GrafoLista *g = criar_grafo(n);

    adicionar_aresta(g, 0, 1);
    adicionar_aresta(g, 0, 2);
    adicionar_aresta(g, 1, 3);
    adicionar_aresta(g, 2, 3);
    adicionar_aresta(g, 4, 5);

    int *dist = (int*) malloc(n * sizeof(int));
    int *pred = (int*) malloc(n * sizeof(int));

    bfs(g, 0, dist, pred);
    printf("--- Teste BFS (Origem: 0) ---\n");
    for (int i = 0; i < n; i++) {
        printf("Vertice %d | Distancia: %d | Predecessor: %d\n", i, dist[i], pred[i]);
    }

    printf("\nNumero de componentes conexos: %d\n", contar_componentes(g));
    printf("Possui ciclo? %s\n", tem_ciclo(g) ? "Sim" : "Nao");
    printf("Eh bipartido? %s\n", eh_bipartido(g) ? "Sim" : "Nao");

    free(dist);
    free(pred);
    destruir_grafo(g);

    return 0;
}