#include <stdio.h>
#include <stdlib.h>
#include "Matriz_de_adjacencia.h"


//mostra na tela o grafo na representação de uma matriz
void mostrarGrafo(Grafo *grafo){
    int nVertices = grafo->numVertices, i, j;

    printf("Numero de Vertices: %d\n\n", nVertices);

    for(i=0; i < nVertices; i++){
        printf("%3d    ", i+1);
        for(j=0; j < nVertices; j++){
            printf(" %3d ", grafo->matrix[i][j]);
        }
        printf("\n");
    }
    return;
}

//aloca na memoria a representacao computacional (MATRIZ DE ADJACENCIA)
Grafo* alocaGrafo(FILE *arq){
    int tipoGrafo, nVertices, i;
    Grafo *grafo;

    fscanf(arq, "%d", &tipoGrafo);
    fscanf(arq, "%d", &nVertices);

    grafo = (Grafo*) malloc(sizeof(Grafo)); // Aloca estrutura inicial (numVertices, numArestas, p)

    grafo->tipoGrafo = tipoGrafo;
    grafo->numVertices = nVertices;
    grafo->numArcos = 0;
    grafo->numArestas = 0;

    grafo->matrix = (int **) malloc(nVertices*sizeof(int*));
    // Aloca um vetor de ponteiros para cada linha da matriz

    for(i=0; i<nVertices; i++){
        grafo->matrix[i] = (int*) calloc(nVertices,sizeof(int)); // Aloca e preenche com zeros cada linha da matriz
    }

    return grafo;
}

//funcao para ler o arquivo e armazenar as informações na matriz de adjacencia
void construirGrafo(FILE *arq, Grafo *grafo){
    int entrada, saida;
    char pular;

    while(!feof(arq)){
        fscanf(arq, "%d", &saida);
        if(saida == '\n') continue;
        fscanf(arq, "%c", &pular);
        fscanf(arq, "%d", &entrada);

        if(grafo->tipoGrafo == 0){ //se for um digrafo, os arcos que sai recebem -1
            grafo->matrix[saida-1][entrada-1] = -1;
            grafo->numArcos++;
        } else {
            grafo->matrix[saida-1][entrada-1] = 1;
            grafo->numArestas++;
        }

        grafo->matrix[entrada-1][saida-1] = 1;
    }
    return;
}

//mostra na tela os vertices do grafo (orientado ou nao)
void listarVertices(Grafo *grafo){
    int numVertices = grafo->numVertices;
    printf("\nVertices: {");
    for(int i=0; i < numVertices; i++)
        printf(" %d ", i+1);
    printf("}\n");
    return;
}

//mostra os arcos do digrafo
void listarArcos(Grafo *grafo){
    int nVertices = grafo->numVertices;
    int i, j;
    printf("\nArcos: {");
    for(i=0; i < nVertices; i++){
        for(j=0; j < nVertices; j++){
            if(grafo->matrix[i][j] == -1 ) //PEGA TODOS OS ARCOS (ENTRADA E SAIDA)
                printf(" (%d, %d) ", i+1, j+1);
        }
    }
    printf("}\n");
    return;
}

//mostra as arestas do grafo nao orientado
void listarArestas(Grafo *grafo){
    int nVertices = grafo->numVertices;
    int i, j;

    printf("\nArestas: {");
    for(i=0; i < nVertices; i++){
        for(j=0; j < nVertices; j++){
            if(grafo->matrix[i][j] == 1 && j >= i)
                printf(" (%d, %d) ", i+1, j+1);
        }
    }
    printf("}\n");
    return;
}

//mostra o grau de cada vertice do digrafo
void grauVerticesDoDigrafo(Grafo *grafo){
    int nVertices = grafo->numVertices;
    int i, j;
    int grauentrada=0, grausaida=0;

    for(i=0; i < nVertices; i++){
        printf("\nVertice %d: \n", i+1);
        for(j=0; j < nVertices; j++){
            if(grafo->matrix[i][j] == 1)
                grauentrada += 1;
            if(grafo->matrix[i][j] == -1)
                grausaida += 1;
        }
        printf(" Grau de entrada: %d \n Grau de saida: %d \n", grauentrada, grausaida);
        grauentrada = grausaida = 0;
    }
    return;
}

//mostra o grau de cada vertice do grafo nao orientado
void grauVerticesGrafoNaoOrientado(Grafo *grafo){
    int nVertices = grafo->numVertices;
    int i, j, grau=0;

    for(i=0; i < nVertices; i++){
        printf("\nGrau do Vertice %d: ", i+1);
        for(j=0; j < nVertices; j++){
            if(grafo->matrix[i][j] == 1)
                grau += 1;
        }
        printf("%d \n", grau);
        grau = 0;
    }
    return;
}

//mostra a ordem e o tamanho do grafo (orientado ou nao orientado)
void ordemETamanho(Grafo *grafo){
    int ordem = grafo->numVertices, tamanho;
    if(grafo->tipoGrafo == 0)
        tamanho = ordem + grafo->numArcos;
    else tamanho = ordem + grafo->numArestas;
    printf("\n Ordem: %d, Tamanho: %d \n" , ordem, tamanho);
    return;
}
