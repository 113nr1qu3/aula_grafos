#include <stdio.h>
#include <stdlib.h>
#include "dag.h"

void imprimir_ordem(const char *algoritmo, int *ordem, int tamanho) {
    if (!ordem) {
        printf("%s: Ciclo detectado! Não é um DAG.\n", algoritmo);
        return;
    }
    printf("%s: ", algoritmo);
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", ordem[i]);
    }
    printf("\n");
}

int main() {
    printf("=== Teste 1: Grafo Acíclico (DAG) ===\n");
    GrafoLista *g1 = criar_grafo(6);
    adicionar_aresta(g1, 5, 2);
    adicionar_aresta(g1, 5, 0);
    adicionar_aresta(g1, 4, 0);
    adicionar_aresta(g1, 4, 1);
    adicionar_aresta(g1, 2, 3);
    adicionar_aresta(g1, 3, 1);

    printf("É DAG? %s\n", eh_dag(g1) ? "Sim" : "Não");

    int tam_kahn = 0, tam_dfs = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(g1, &tam_kahn);
    int *ordem_dfs = ordenacao_topologica_dfs(g1, &tam_dfs);

    imprimir_ordem("Kahn", ordem_kahn, tam_kahn);
    imprimir_ordem("DFS ", ordem_dfs, tam_dfs);

    free(ordem_kahn);
    free(ordem_dfs);
    destruir_grafo(g1);

    printf("\n=== Teste 2: Grafo com Ciclo ===\n");
    GrafoLista *g2 = criar_grafo(3);
    adicionar_aresta(g2, 0, 1);
    adicionar_aresta(g2, 1, 2);
    adicionar_aresta(g2, 2, 0); // Cria o ciclo 0 -> 1 -> 2 -> 0

    printf("É DAG? %s\n", eh_dag(g2) ? "Sim" : "Não");

    int *ordem_ciclo = ordenacao_topologica_kahn(g2, &tam_kahn);
    imprimir_ordem("Kahn", ordem_ciclo, tam_kahn);

    destruir_grafo(g2);
    return 0;
}