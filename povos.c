#include <stdio.h>
#include <stdlib.h>
#include "povos.h"

int** criarPovos(FILE **arquivo,int p){
    int** povos = (int**)malloc((p)*sizeof(int*));
    for(int i = 0; i < p; i++) {
        int** povos = (int**)malloc((3)*sizeof(int*));
        for(int j = 0; j < 3; j++) {
            fscanf(*arquivo,"%d", &povos[i][j]);
        }
    }
    return povos;
}

void destroiPovos(int **povos, int p){
    for(int i = 0; i < p; i++) {
        free(povos[i]);
    }
    free(povos);
}

void iniciaGrafo(Grafo* g, int vertice){
    g->matriz = malloc (vertice*sizeof(int*));
    g->matriz[0] = NULL;
    for (int i = 1; i < vertice; i++){
        g->matriz = malloc (i*sizeof(int));    
    }
    g->vertice = vertice;
}

void destroiGrafo(Grafo *g) {
    for (int i = 1; i < g->vertice; i++){
        free(g->matriz[i]);
    }
    free(g->matriz);
}

void adicionarAresta(Grafo *g, int i, int j, int distancia) {
    g->matriz[i][j] = distancia;
}

void criarGrafo(FILE **arquivoE, FILE **arquivoS, Grafo *g, int p, int c) {
    int i, j, distancia;
    iniciaGrafo(g, p);
    for (int x = 0; x < c; x++){
        fscanf(*arquivoE,"%d %d %d", &i, &j, &distancia);
        adicionarAresta(g,i,j,distancia);
        fprintf(*arquivoS,"Matriz[%d%d]=%d\n", i,j,distancia);
    }
}

void heuristica(int **povos, int p, int w){
    float maior = 0, razao = 0;
    int x = 1;
    int* list = (int*)malloc((p)*sizeof(int*));
    int *list = NULL;
    for(int i = 0; i < p; i++){
        razao = povos[i][2] / povos[i][1];
        if (razao = maior){
            list[x] = i;
            x++;
        }
        if (razao > maior){
            maior = razao;
            free(list);
            list[0] = i;
        }
    }
    int div, mult, sub, maiors;
    for(int y = 0; y < p; y++) {
        if (list[y] != NULL){
            div = w / povos[y][1];
            mult = div * povos[y][1];
            sub = w - mult;
            for(int s = 0; s < p; s++){
                if (s != y) {
                    if (w >= povos[s][1]) {
                        div = w / povos[s][1];
                        if (div > maiors) {
                            maiors = div;
                            //Parei aqui e não estou conseguindo entender;
                        }
                    }
                }
            }
            //encontrar o caminho e retornar o total da habilidade;

        }
    }
}






