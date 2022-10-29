#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/resource.h>
#include "arquivo.h"
#include "povos.h"
#include "tempo.h"

int main(int argc,char *argv[]){
    struct rusage start, end;
    FILE *arquivoE = NULL;
    FILE *arquivoS = NULL;
    int **povos = NULL;
    int **matriz = NULL;
    int k, p, d, w, c;

    getrusage(RUSAGE_SELF, &start);

    abrirEntrada(&arquivoE,argv); //Abre o arquivo de entrada;
    abrirSaida(&arquivoS);  //Abre o arquivo de saida;

    fscanf(arquivoE,"%d",&k);
    for(int x = 0; x < k; x++) {
        fscanf(arquivoE,"%d %d %d %d",&p, &d, &w, &c);
        povos = criarPovos(p);  //Cria os povos;
        inserePovos(&arquivoE,povos,p); //Insere os dados dos povos;
        matriz = iniciaGrafo(p);    //Inicia o grafo;
        criarGrafo(&arquivoE,matriz,p,c);   //Cria e insere os dados no grafo;
        heuristica(&arquivoS,povos,matriz,p,d,w);   //Solução heurística;
        //imprimirPovos(&arquivoS,povos,p);     //Imprime os dados dos povos;
        //imprimirGrafo(&arquivoS,matriz,p);       //Imprime os dados do grafo;
        destroiPovos(povos, p);     //Destroi os povos criados;
        destroiGrafo(matriz, p);       //Destroi o grafo;
        fprintf(arquivoS,"\n");
    }

    fecharArquivo(&arquivoE);   //Fecha o arquivo de entrada;
    fecharArquivo(&arquivoS);   //Fecha o arquivo de saida;

    getrusage(RUSAGE_SELF, &end);
    
    printf("Tempo de usuário: %.06f s\nTempo de sistema: %.06f s\n",diffUserTime(&start, &end), diffSystemTime(&start, &end));
    
    return 0;
}