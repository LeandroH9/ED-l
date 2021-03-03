#include <stdio.h>
#include <stdlib.h>
#include "Matriz_de_adjacencia.c"

int main(){
    FILE *arq1, *arq2;
    char c;
    int nV;
    Grafo *grafo;

    arq1 = fopen("digrafo.txt", "r");
    arq2 = fopen("naoorientado.txt", "r");

    //MATRIZ DE ADJACENCIA

    if (arq1 != NULL && arq2 != NULL){


        //GRAFO ORIENTADO (DIGRAFO)
        printf("\n\n===================GRAFO NAO ORIENTADO (DIGRAFO) ==========================\n\n");

        fseek(arq1, 0, SEEK_SET);

        grafo = alocaGrafo(arq1);

        construirGrafo(arq1, grafo);

        mostrarGrafo(grafo);

        listarVertices(grafo);

        listarArcos(grafo);

        grauVerticesDoDigrafo(grafo);

        ordemETamanho(grafo);

        //GRAFO NAO ORIENTADO
        printf("\n\n===================GRAFO NAO ORIENTADO==========================\n\n");

        fseek(arq2, 0, SEEK_SET);

        grafo = alocaGrafo(arq2);

        construirGrafo(arq2, grafo);

        mostrarGrafo(grafo);

        listarVertices(grafo);

        listarArestas(grafo);

        grauVerticesGrafoNaoOrientado(grafo);

        ordemETamanho(grafo);

    } else printf("Erro na leitura\n");



    fclose(arq1);
    fclose(arq2);
    return(0);
}
