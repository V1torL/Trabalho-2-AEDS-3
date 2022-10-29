#include <stdio.h>
#include <stdlib.h>

float** criarPovos(int p) {      //Cria uma matriz p x 3 de povos, onde i indica o povo e j indica peso e habilidade;
    float** povos = (float**)malloc((p)*sizeof(float*));    
    for(int i = 0; i < p; i++) {
        povos[i] = (float*)malloc((3)*sizeof(float*));
        for(int j = 0; j < 3; j++) {
            povos[i][j] = 0;
        }
    }
    return povos;
}

void destroiPovos(float **povos, int p){    //Destroi os povos criados;
    for(int i = 0; i < p; i++) {
        free(povos[i]);
    }
    free(povos);
}

void inserePovos(FILE **arquivo, float **povos, int p){     //Insere os dados dos povos;
    for(int i = 0; i < p; i++){
        for(int j = 0; j < 3; j++){
            fscanf(*arquivo,"%f", &povos[i][j]);
        }
    }
}

void imprimirPovos(FILE **arquivo,int **povos, int p){      //Imprime no terminal os povos criados;
    for(int i = 0; i < p; i++){
        for(int j = 0; j < 3; j++){
            fprintf(*arquivo,"%d ",povos[i][j]);
        }
        fprintf(*arquivo,"\n");
    }
}

int** iniciaGrafo(int p){   //Cria uma matriz p x p, onde i e j representa os vertices e consequentemente, os povos;
    int** matriz = (int**)malloc((p)*sizeof(int*));
    for(int i = 0; i < p; i++) {
        matriz[i] = (int*)malloc((p)*sizeof(int*));
        for(int j = 0; j < p; j++) {
            matriz[i][j] = 0;
        }
    }
    return matriz;
}

void destroiGrafo(int **matriz, int p){     //Destroi a matriz adjacente criada;
    for(int i = 0; i < p; i++) {
        free(matriz[i]);
    }
    free(matriz);
}

void adicionarAresta(int **matriz, int i, int j, int distancia){    //Insere a distancia de i para j e de j para i na matriz;
    matriz[i-1][j-1] = distancia;
    matriz[j-1][i-1] = distancia;
}

void criarGrafo(FILE **arquivo, int **matriz, int p, int c) {   //Função para adicionar as arestas so grafo;
    int i, j, distancia;
    for (int x = 0; x < c; x++){
        fscanf(*arquivo,"%d %d %d", &i, &j, &distancia);
        adicionarAresta(matriz,i,j,distancia);
    }
}

void imprimirGrafo(FILE **arquivo,int **matriz, int p){     //Imprime as distancias entres os povos;
    for(int i = 0; i < p; i++){
        for(int j = 0; j < p; j++){
            if (matriz[i][j] > 0){
                fprintf(*arquivo,"Matriz[%d,%d]=%d\n", i+1,j+1,matriz[i][j]);
            }
        }
    }
}

int melhorPovo(float **povos, int p, int peso){     //Função que retorna o melhor povo;
    float razao = 0, maiorRazao = 0;
    int povo;
    for(int i = 0; p > i; i++){
        if(peso >= povos[i][1]) {
            razao = povos[i][2] / povos[i][1];      //Razão é o habilidade do povo dividido por seu peso;
            if(razao > maiorRazao){
                maiorRazao = razao;
                povo = i;
            }
        }
    }
    return povo;
}

//A função percorre grafo, é usada para proucurar povos que não estão ligados diretamente no grafo;
int percorrerGrafo(FILE **arquivo,int **matriz, float**povos, int pesoNave, int inicio, int final, int habilidade, int *povo, int *soldado, int contador, int d, int p) {
    int soldados, pesoPovo;
    for(int i = 0; p > i; i++){
        if ((matriz[inicio][i] > 0) && (d>=0)) {    //Encontra os povos ligados ao inicio;
            d = d - matriz[inicio][i];      //Retira da autonomia da nave a distancia percorrida;
            povo[contador] = i + 1;     //Insere em um array, o povo que foi utilizado;
            soldado[contador] = 0;      //Insere em um array, a quantidade de soldados que irá utilizar do povo;
            contador++;     //Adiciona um espaço nos arrays;
            if (matriz[i][final] > 0 && d >= 0) {       //Verifica se o povo utilizado possui ligações com o final;
                d = d - matriz[i][final];   //Retira da autonomia da nave a distancia percorrida;
                if(d >= 0){
                    soldados = pesoNave / povos[final][1];      //Retorna a quantidade de soldados que vão ser utilizados;
                    pesoPovo = soldados * povos[final][1];      //Retorna o peso total dos soldados que irão entrar na nave;
                    pesoNave = pesoNave - pesoPovo;         //Retorna o peso da nave após a entrada dos soldados;
                    habilidade = habilidade + (povos[final][2] * soldados);     //Retorna a habilidade total do povo;
                    povo[contador] = final + 1;     //Insere em um array, o povo que foi utilizado;
                    soldado[contador] = soldados;   //Insere em um array, a quantidade de soldados que irá utilizar do povo;
                    contador++;       //Adiciona um espaço nos arrays;
                    fprintf(*arquivo,"%d", habilidade);       //Imprime os resultados na saida.txt
                    for(int i = 0; contador > i; i++) {
                        fprintf(*arquivo," %d %d", povo[i], soldado[i]);    //Imprime os resultados na saida.txt
                    }
                    return 1;
                }
                else{
                    d = d + matriz[inicio][final];      //Retira da autonomia da nave a distancia percorrida;
                    povos[final][1] = pesoNave + 1;     //Faz com que o povo tenha peso acima do peso da nave;
                    final = melhorPovo(povos,p,pesoNave);      //Encontra o melhor povo;
                    if (final > 0){
                        percorrerGrafo(arquivo,matriz,povos,pesoNave,inicio,final,habilidade,povo,soldado,contador,d,p);
                    }
                    else {
                        fprintf(*arquivo,"%d", habilidade);     //Imprime os resultados na saida.txt
                        for(int i = 0; contador > i; i++) {
                            fprintf(*arquivo," %d %d", povo[i], soldado[i]);       //Imprime os resultados na saida.txt
                        }
                    }
                }
            }
            else {
                percorrerGrafo(arquivo,matriz,povos,pesoNave,i,final,habilidade,povo,soldado,contador,d,p);
                d = d + matriz[inicio][i];      //Retoma a autonomia da nave que foi retirada;
            }
        }
    }
}


void heuristica(FILE **arquivo,float **povos, int **matriz, int p, int d, int w){
    int povo[p];    //Array para povo;
    int soldado[p];     //Array para soldado;
    int soldados, pesoPovo, pesoNave, habilidade, contador, distancia, retorna;

    contador = 0;
    int melhor = melhorPovo(povos,p,w);     //Encontra o melhor povo;

    soldados = w / povos[melhor][1];        //Retorna a quantidade de soldados que vão ser utilizados;
    pesoPovo = soldados * povos[melhor][1];     //Retorna o peso total dos soldados que irão entrar na nave;
    pesoNave = w - pesoPovo;        //Retorna o peso da nave após a entrada dos soldados;
    habilidade = povos[melhor][2] * soldados;       //Retorna a habilidade total do povo;
    povo[contador] = melhor + 1;         //Insere em um array, o povo que foi utilizado;
    soldado[contador] = soldados;       //Insere em um array, a quantidade de soldados que irá utilizar do povo;
    contador++;     //Adiciona um espaço nos arrays;

    if (pesoNave > 0) {     //Ocorra se estiver sobrando espaço na nave;
        int sequencia = melhorPovo(povos,p,pesoNave);       //Encontra o melhor povo;
        distancia = d - matriz[melhor][sequencia];      //Retira da autonomia da nave a distancia percorrida;
        if (matriz[melhor][sequencia] > 0 && distancia > 0){    //Verifica se os povos estão ligados diretamente;
            soldados = pesoNave / povos[sequencia][1];      //Retorna a quantidade de soldados que vão ser utilizados;
            pesoPovo = soldados * povos[sequencia][1];       //Retorna o peso total dos soldados que irão entrar na nave;
            pesoNave = pesoNave - pesoPovo;     //Retorna o peso da nave após a entrada dos soldados;
            habilidade = habilidade + (povos[sequencia][2] * soldados);     //Retorna a habilidade total do povo;
            povo[contador] = sequencia + 1;     //Insere em um array, o povo que foi utilizado;
            soldado[contador] = soldados;       //Insere em um array, a quantidade de soldados que irá utilizar do povo;
            contador++;     //Adiciona um espaço nos arrays;
            fprintf(*arquivo,"%d", habilidade);     //Imprime os resultados na saida.txt
            for(int i = 0; contador > i; i++) {
                fprintf(*arquivo," %d %d", povo[i], soldado[i]);    //Imprime os resultados na saida.txt
            }
        }
        else {
            retorna = percorrerGrafo(arquivo,matriz,povos,pesoNave,melhor,sequencia,habilidade,povo,soldado,contador,d,p);
            if (retorna != 1) {     //Retorna se foi feito alguma impressão;
                fprintf(*arquivo,"%d", habilidade);     //Imprime os resultados na saida.txt
                for(int i = 0; contador > i; i++) {
                    fprintf(*arquivo," %d %d", povo[i], soldado[i]);       //Imprime os resultados na saida.txt
                }
            }
        }
    }
    else {
        fprintf(*arquivo,"%d", habilidade);     //Imprime os resultados na saida.txt
        for(int i = 0; contador > i; i++) {
            fprintf(*arquivo," %d %d", povo[i], soldado[i]);        //Imprime os resultados na saida.txt
        }
    }
}