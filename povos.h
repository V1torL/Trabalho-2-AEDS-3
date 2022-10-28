#include <stdio.h>
#include <stdlib.h>

int** criarPovos(int p);
void destroiPovos(int **povos, int p);
void inserePovos(FILE **arquivo, int **povos, int p);
void imprimirPovos(FILE **arquivo,int **povos, int p);
int** iniciaGrafo(int p);
void destroiGrafo(int **matriz, int p);
void adicionarAresta(int **matriz, int i, int j, int distancia);
void criarGrafo(FILE **arquivo, int **matriz, int p, int c);
void imprimirGrafo(FILE **arquivo,int **matriz, int p);
int melhorPovo(int **povos, int p, int peso);
void percorrerGrafo(FILE **arquivo,int **matriz, float**povos, int pesoNave, int inicio, int final, int habilidade, int *povo, int *soldado, int contador, int d, int p);
void heuristica(FILE **arquivo,int **povos, int **matriz, int p, int d, int w);