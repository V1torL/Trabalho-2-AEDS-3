#include <stdio.h>
#include <stdlib.h>

int** criarPovos(int p){
    int** povos = (int**)malloc((p)*sizeof(int*));
    for(int i = 0; i < p; i++) {
        povos[i] = (int*)malloc((3)*sizeof(int*));
        for(int j = 0; j < 3; j++) {
            povos[i][j] = 0;
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

void inserePovos(FILE **arquivo, int **povos, int p){
    for(int i = 0; i < p; i++){
        for(int j = 0; j < 3; j++){
            fscanf(*arquivo,"%d", &povos[i][j]);
        }
    }
}

/*void imprimirPovos(FILE **arquivo,int **povos, int p){
    for(int i = 0; i < p; i++){
        for(int j = 0; j < 3; j++){
            fprintf(*arquivo,"%d ",povos[i][j]);
        }
        fprintf(*arquivo,"\n");
    }
}*/

int** iniciaGrafo(int p){
    int** matriz = (int**)malloc((p)*sizeof(int*));
    for(int i = 0; i < p; i++) {
        matriz[i] = (int*)malloc((p)*sizeof(int*));
        for(int j = 0; j < p; j++) {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void destroiGrafo(int **matriz, int p){
    for(int i = 0; i < p; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void adicionarAresta(int **matriz, int i, int j, int distancia){
    matriz[i-1][j-1] = distancia;
    matriz[j-1][i-1] = distancia;
}

void criarGrafo(FILE **arquivo, int **matriz, int p, int c) {
    int i, j, distancia;
    for (int x = 0; x < c; x++){
        fscanf(*arquivo,"%d %d %d", &i, &j, &distancia);
        adicionarAresta(matriz,i,j,distancia);
    }
}

/*void imprimirGrafo(FILE **arquivo,int **matriz, int p){
    for(int i = 0; i < p; i++){
        for(int j = 0; j < p; j++){
            if (matriz[i][j] > 0){
                fprintf(*arquivo,"Matriz[%d,%d]=%d\n", i+1,j+1,matriz[i][j]);
            }
        }
    }
}*/

void heuristica(FILE **arquivo,int **povos, int p, int w){
    int soldados, pesoPovo, pesoNave, habilidade;
    int melhor = 0;
    for (int i = 1; i < p; i++){
		if (povos[i][2]/povos[i][2] > povos[i][2]/povos[i][2]){
			melhor = i;
		}
	}
    soldados = w / povos[melhor][1];
    pesoPovo = soldados * povos[melhor][1];
    pesoNave = w - pesoPovo;
    habilidade = povos[melhor][2] * soldados;

    fprintf(*arquivo,"%d", habilidade);
    fprintf(*arquivo," %d %d", melhor+1 , soldados);
}