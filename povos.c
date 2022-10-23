#include <stdio.h>

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

int criarCaminhos(FILE **arquivo, int p, int c) {
    criarPovos(*arquivo,p);
}

int heuristica() {
    //
}
