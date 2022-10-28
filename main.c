#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arquivo.h"
#include "povos.h"

int main(int argc,char *argv[]){
    FILE *arquivoE = NULL;
    FILE *arquivoS = NULL;
    int **povos = NULL;
    int **matriz = NULL;
    int k, p, d, w, c;
    abrirEntrada(&arquivoE,argv);
    abrirSaida(&arquivoS);
    fscanf(arquivoE,"%d",&k);
    for(int x = 0; x < k; x++) {
        fscanf(arquivoE,"%d %d %d %d",&p, &d, &w, &c);
        povos = criarPovos(p);
        inserePovos(&arquivoE,povos,p);
        matriz = iniciaGrafo(p);
        criarGrafo(&arquivoE,matriz,p,c);
        heuristica(&arquivoS,povos,matriz,p,d,w);
        //imprimirPovos(&arquivoS,povos,p);
        //imprimirGrafo(&arquivoS,matriz,p);
        destroiPovos(povos, p);
        destroiGrafo(matriz, p);
        fprintf(arquivoS,"\n");
    }
    fecharArquivo(&arquivoE);
    fecharArquivo(&arquivoS);
    return 0;
}