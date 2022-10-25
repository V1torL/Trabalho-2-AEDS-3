#include <stdio.h>

struct grafo {
    int vertice;
    int **matriz;
};
typedef struct grafo Grafo;

int* criarPovos(FILE **arquivo,int p);
void iniciaGrafo(Grafo* g, int vertice);
void destroiGrafo(Grafo *g);
void adicionaAresta(Grafo *g, int i, int j, int distancia);
void criaGrafo(FILE **arquivo, Grafo *g, int p, int c);