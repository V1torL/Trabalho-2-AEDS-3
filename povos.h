#include <stdio.h>

struct grafo {
    int vertice;
    int **matriz;
};
typedef struct grafo Grafo;

int** criarPovos(FILE **arquivo,int p);
void destroiPovos(int **povos, int p);
void iniciaGrafo(Grafo* g, int vertice);
void destroiGrafo(Grafo *g);
void adicionarAresta(Grafo *g, int i, int j, int distancia);
void criarGrafo(FILE **arquivoE, FILE **arquivoS,Grafo *g, int p, int c);