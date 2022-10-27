#include <stdio.h>
#include <stdlib.h>

int** criarPovos(int p);
void destroiPovos(int **povos, int p);
void inserePovos(FILE **arquivo, int **povos, int p);
//void imprimirPovos(FILE **arquivo,int **povos, int p);
int** iniciaGrafo(int p);
void destroiGrafo(int **matriz, int p);
void adicionarAresta(int **matriz, int i, int j, int distancia);
void criarGrafo(FILE **arquivo, int **matriz, int p, int c);
//void imprimirGrafo(FILE **arquivo,int **matriz, int p);
void heuristica(FILE **arquivo,int **povos, int p, int w);