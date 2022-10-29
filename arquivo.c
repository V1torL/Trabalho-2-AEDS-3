#include <stdio.h>

void abrirEntrada(FILE **arquivo,char *argv[]){  //Função para abrir o arquivo entrada.txt;
    *arquivo = fopen(argv[2],"r");
}
void abrirSaida(FILE **arquivo){    //Função para abrir o arquivo saida.txt;
    *arquivo = fopen("saida.txt","w");
}
void fecharArquivo(FILE **arquivo){     //Função para fechar os arquivos;
    fclose(*arquivo);
}