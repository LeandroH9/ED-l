#include <stdio.h>
#include <stdlib.h>
#include "Lista_de_adjacencia.h"


//mostra na tela o grafo na representação de uma lista de adjacencia
void mostrarGrafo(Grafo *grafo){
    int nVertices = grafo->numVertices, i, j;
    No p;

    printf("Numero de Vertices: %d\n\n", nVertices);

    printf(" LISTA  ");
    for(i=1; i <= nVertices; i++){
        printf("\n| %2d | -> ", i);
        for(p = grafo->lista[i]; p != NULL; p = p->next)
           printf("%3d -> ", p->vertice);
    }
    printf("\n");
    return;
}

//aloca na memoria a representacao computacional (LISTA DE ADJACENCIA)
Grafo* alocaGrafo(FILE *arq){
    int tipoGrafo, nVertices, i;
    Grafo *grafo;

    fscanf(arq, "%d", &tipoGrafo);
    fscanf(arq, "%d", &nVertices);

    grafo = (Grafo*) malloc(sizeof(Grafo));

    grafo->tipoGrafo = tipoGrafo;
    grafo->numVertices = nVertices;
    grafo->numArcos = 0;
    grafo->numArestas = 0;

    grafo->lista = malloc( nVertices * sizeof(No*));

    for(i=1; i <= nVertices; i++)
        grafo->lista[i] = NULL;

    return grafo;
}

//insere na lista o arco / aresta
void inserirArcoOuAresta(Grafo *grafo, int saida, int entrada) {
   No p, novo;
   for(p = grafo->lista[saida]; p != NULL; p = p->next){
      if (p->vertice == entrada) return;
   }
   novo = malloc(sizeof(struct no));
   novo->vertice = entrada;
   novo->next = grafo->lista[saida];
   grafo->lista[saida] = novo;

   return;
}

//funcao para ler o arquivo e armazenar as informações na lista de adjacencia
void construirGrafo(FILE *arq, Grafo *grafo){
    int entrada, saida;
    char pular;

    while(!feof(arq)){
        fscanf(arq, "%d", &saida);
        if(saida == '\n') continue;
        fscanf(arq, "%c", &pular);
        fscanf(arq, "%d", &entrada);


        if(grafo->tipoGrafo == 0){ //se for um digrafo, os arcos que sai recebem -1
            inserirArcoOuAresta(grafo, saida, entrada);
            grafo->numArcos++;
        } else {
            inserirArcoOuAresta(grafo, saida, entrada);
            inserirArcoOuAresta(grafo, entrada, saida);
            grafo->numArestas++;
        }
    }
    return;
}

//mostra na tela os vertices do grafo (orientado ou nao)
void listarVertices(Grafo *grafo){
    int numVertices = grafo->numVertices;
    printf("\nVertices: {");
    for(int i=1; i <= numVertices; i++)
        printf(" %d ", i);
    printf("}\n");
    return;
}

void listarArcos(Grafo *grafo){
    int nVertices = grafo->numVertices, i;
    No p;
    printf("\nArcos: {");
    for(i=1; i <= nVertices; i++){
        for(p = grafo->lista[i]; p != NULL; p = p->next)
           printf(" (%d, %d) ", i, p->vertice);
    }
    printf("}\n");
}

void listarArestas(Grafo *grafo){
    int nVertices = grafo->numVertices, i;
    No p;
    printf("\nArestas: {");
    for(i=1; i <= nVertices; i++){
        for(p = grafo->lista[i]; p != NULL; p = p->next)
           printf(" (%d, %d) ", i, p->vertice);
    }
    printf("}\n");
}


void grauVerticesDoDigrafo(Grafo *grafo){
    int nVertices = grafo->numVertices;
    int i, j;
    int grauentrada=0, grausaida=0;
    No p;

    for(i=1; i <= nVertices; i++){
        printf("\nVertice %d: \n", i);
        for(p = grafo->lista[i]; p != NULL; p = p->next)
            grausaida++;
        for(j=1; j <= nVertices; j++){
            for(p = grafo->lista[j]; p != NULL; p = p->next)
                if(p->vertice == i) grauentrada++;
        }
        printf(" Grau de entrada: %d \n Grau de saida: %d \n", grauentrada, grausaida);
        grauentrada = grausaida = 0;
    }
    return;
}

void grauVerticesGrafoNaoOrientado(Grafo *grafo){
    int nVertices = grafo->numVertices;
    int i, j;
    int grau=0;
    No p;
    for(i=1; i <= nVertices; i++){
        printf("\nVertice %d: \n", i);
        for(p = grafo->lista[i]; p != NULL; p = p->next)
            grau++;
        printf(" Grau : %d \n", grau);
        grau = 0;
    }
    return;
}

void ordemETamanho(Grafo *grafo){
    int ordem = grafo->numVertices, tamanho;
    if(grafo->tipoGrafo == 0)
        tamanho = ordem + grafo->numArcos;
    else tamanho = ordem + grafo->numArestas;
    printf("\n Ordem: %d, Tamanho: %d \n" , ordem, tamanho);
    return;
}


