#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.c"

int main() {
    int num_vertices = 5;
    GrafoListaPonderado *g = criar_grafo(num_vertices);

    // Grafo direcionado ponderado
    adicionar_aresta(g, 0, 1, 10);
    adicionar_aresta(g, 0, 4, 3);
    adicionar_aresta(g, 1, 2, 2);
    adicionar_aresta(g, 1, 4, 4);
    adicionar_aresta(g, 2, 3, 9);
    adicionar_aresta(g, 3, 2, 7);
    adicionar_aresta(g, 4, 1, 1);
    adicionar_aresta(g, 4, 2, 8);
    adicionar_aresta(g, 4, 3, 2);

    int origem = 0;
    int dist[num_vertices];
    int pred[num_vertices];

    dijkstra(g, origem, dist, pred);

    printf("=== Menor Caminho a partir da Origem (%d) ===\n", origem);
    for (int i = 0; i < num_vertices; i++) {
        printf("Distância até o vértice %d: ", i);
        if (dist[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d | ", dist[i]);
            reconstruir_caminho(origem, i, pred);
        }
    }

    liberar_grafo(g);
    return 0;
}