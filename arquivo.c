#include <stdio.h>

void abrirEntrada(FILE **arquivo,char *argv[]){
    *arquivo = fopen(argv[2],"r");
}
void abrirSaida(FILE **arquivo){
    *arquivo = fopen("saida.txt","w");
}
void fecharArquivo(FILE **arquivo){
    fclose(*arquivo);
}