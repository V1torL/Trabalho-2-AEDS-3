#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arquivo.h"
#include "povos.h"

int main(int argc,char *argv[]){
    FILE *arquivoE = NULL;
    FILE *arquivoS = NULL;
    Grafo *g = NULL;
    int k, p, d, w, c;
    abrirEntrada(&arquivoE,argv);
    abrirSaida(&arquivoS);

    fscanf(arquivoE,"%d",&k);
    for(int x = 0; x < k; x++) {
        bool executar = true;
        while (executar) {
            fscanf(arquivoE,"%d %d %d %d",&p, &d, &w, &c);
            //Criar mochila (peso e autonomia);
            criarPovos(&arquivoE,p);
            criarGrafo(&arquivoE,&arquivoS,g,p,c);
            //Criar os caminho entre os povos
            //Executar o caminho do zork
            executar = false;
        }
        
    }

    fecharArquivo(&arquivoE);
    fecharArquivo(&arquivoS);

    return 0;
}