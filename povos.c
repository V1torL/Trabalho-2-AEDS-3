#include <stdio.h>
#include <stdlib.h>

float** criarPovos(int p){
    float** povos = (float**)malloc((p)*sizeof(float*));
    for(int i = 0; i < p; i++) {
        povos[i] = (float*)malloc((3)*sizeof(float*));
        for(int j = 0; j < 3; j++) {
            povos[i][j] = 0;
        }
    }
    return povos;
}

void destroiPovos(float **povos, int p){
    for(int i = 0; i < p; i++) {
        free(povos[i]);
    }
    free(povos);
}

void inserePovos(FILE **arquivo, float **povos, int p){
    for(int i = 0; i < p; i++){
        for(int j = 0; j < 3; j++){
            fscanf(*arquivo,"%f", &povos[i][j]);
        }
    }
}

void imprimirPovos(FILE **arquivo,int **povos, int p){
    for(int i = 0; i < p; i++){
        for(int j = 0; j < 3; j++){
            fprintf(*arquivo,"%d ",povos[i][j]);
        }
        fprintf(*arquivo,"\n");
    }
}

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

void imprimirGrafo(FILE **arquivo,int **matriz, int p){
    for(int i = 0; i < p; i++){
        for(int j = 0; j < p; j++){
            if (matriz[i][j] > 0){
                fprintf(*arquivo,"Matriz[%d,%d]=%d\n", i+1,j+1,matriz[i][j]);
            }
        }
    }
}

int melhorPovo(float **povos, int p, int peso){
    float razao = 0, maiorRazao = 0;
    int povo;
    for(int i = 0; p > i; i++){
        if(peso >= povos[i][1]) {
            razao = povos[i][2] / povos[i][1];
            if(razao > maiorRazao){
                maiorRazao = razao;
                povo = i;
            }
        }
    }
    return povo;
}

int percorrerGrafo(FILE **arquivo,int **matriz, float**povos, int pesoNave, int inicio, int final, int habilidade, int *povo, int *soldado, int contador, int d, int p) {
    int soldados, pesoPovo, caso = 0;
    for(int i = 0; p > i; i++){
        if ((matriz[inicio][i] > 0) && (d>=0)) {
            d = d - matriz[inicio][i];
            povo[contador] = i + 1;
            soldado[contador] = 0;
            contador++;
            if (matriz[i][final] > 0 && d >= 0) {
                d = d - matriz[i][final];
                if(d >= 0){
                    soldados = pesoNave / povos[final][1];
                    pesoPovo = soldados * povos[final][1];
                    pesoNave = pesoNave - pesoPovo;
                    habilidade = habilidade + (povos[final][2] * soldados);
                    povo[contador] = final + 1;
                    soldado[contador] = soldados;
                    contador++;
                    caso++;
                    fprintf(*arquivo,"%d", habilidade);
                    for(int i = 0; contador > i; i++) {
                        fprintf(*arquivo," %d %d", povo[i], soldado[i]);
                    }
                    return 1;
                }
                else{
                    d = d + matriz[inicio][final];
                    povos[final][1] = pesoNave + 1;
                    final = melhorPovo(povos,p,pesoNave);
                    if (final > 0){
                        percorrerGrafo(arquivo,matriz,povos,pesoNave,inicio,final,habilidade,povo,soldado,contador,d,p);
                    }
                    else {
                        caso++;
                        fprintf(*arquivo,"%d", habilidade);
                        for(int i = 0; contador > i; i++) {
                            fprintf(*arquivo," %d %d", povo[i], soldado[i]);
                        }
                    }
                }
            }
            else {
                percorrerGrafo(arquivo,matriz,povos,pesoNave,i,final,habilidade,povo,soldado,contador,d,p);
                d = d + matriz[inicio][i];
            }
        }
    }
}


void heuristica(FILE **arquivo,float **povos, int **matriz, int p, int d, int w){
    int povo[p];
    int soldado[p];
    int soldados, pesoPovo, pesoNave, habilidade, contador, distancia, retorna;

    contador = 0;
    int melhor = melhorPovo(povos,p,w);

    soldados = w / povos[melhor][1];
    pesoPovo = soldados * povos[melhor][1];
    pesoNave = w - pesoPovo;
    habilidade = povos[melhor][2] * soldados;
    povo[contador] = melhor + 1;
    soldado[contador] = soldados;
    contador++;

    if (pesoNave > 0) {
        int sequencia = melhorPovo(povos,p,pesoNave);
        distancia = d - matriz[melhor][sequencia];
        if (matriz[melhor][sequencia] > 0 && distancia > 0){
            soldados = pesoNave / povos[sequencia][1];
            pesoPovo = soldados * povos[sequencia][1];
            pesoNave = pesoNave - pesoPovo;
            habilidade = habilidade + (povos[sequencia][2] * soldados);
            povo[contador] = sequencia + 1;
            soldado[contador] = soldados;
            contador++;
            fprintf(*arquivo,"%d", habilidade);
            for(int i = 0; contador > i; i++) {
                fprintf(*arquivo," %d %d", povo[i], soldado[i]);
            }
        }
        else {
            retorna = percorrerGrafo(arquivo,matriz,povos,pesoNave,melhor,sequencia,habilidade,povo,soldado,contador,d,p);
            if (retorna != 1) {
                fprintf(*arquivo,"%d", habilidade);
                for(int i = 0; contador > i; i++) {
                    fprintf(*arquivo," %d %d", povo[i], soldado[i]);
                }
            }
        }
    }
    else {
        fprintf(*arquivo,"%d", habilidade);
        for(int i = 0; contador > i; i++) {
            fprintf(*arquivo," %d %d", povo[i], soldado[i]);
        }
    }
}