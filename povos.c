#include <stdio.h>
#include <povos.h>

int* criarPovos(FILE **arquivo,int p){
    int** povos = (int**)malloc((p)*sizeof(int*));
    for(int i = 0; i < p; i++) {
        int** povos = (int**)malloc((3)*sizeof(int*));
        for(int j = 0; j < 3; j++) {
            fscanf(*arquivo,"%d", &povos[i][j]);
        }
    }
    return povos;
}

void iniciaGrafo(Grafo* g, int vertice){
    g->matriz = malloc (vertice, sizeof(int*));
    g->matriz[0] = NULL;
    for (int i = 1; i < vertice; i++){
        g->matriz = malloc (i, sizeof(int));    
    }
    g->vertice = vertice;
}

void destroiGrafo(Grafo *g) {
    for (int i = 1; i < g->vertice; i++){
        free(g->matriz[i]);
    }
    free(g->matriz);
}

void adicionaAresta(Grafo *g, int i, int j, int distancia) {
    g->matriz[i][j] = distancia;
}

void criaGrafo(FILE **arquivo, Grafo *g, int p, int c) {
    int i, j, distancia;
    iniciaGrafo(&g, p);
    for (int x = 0; x < c; x++){
        fscanf(*arquivo,"%d %d %d", &i, &j, &distancia);
        adicionarAresta(&g,i,j,distancia);
    }
}