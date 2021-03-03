#ifndef MATRIZ_DE_ADJACENCIA_H_INCLUDED
#define MATRIZ_DE_ADJACENCIA_H_INCLUDED

typedef struct{
    int tipoGrafo; //0 para dígrafo e 1 para grafo não orientado
    int numVertices; //numero de vertices do grafo
    int numArcos; //se o grafo for um dígrafo, esta variavel sera utilizada
    int numArestas; //se for um grafo nao orientado, esta variavel sera utilizada
    int **matrix; //armazena a matriz de adjacencia
} Grafo;

void mostrarGrafo(Grafo *grafo);
Grafo* alocaGrafo(FILE *arq);
void construirGrafo(FILE *arq, Grafo *grafo);
void listarVertices(Grafo *grafo);
void listarArcos(Grafo *grafo);
void listarArestas(Grafo *grafo);
void grauVerticesDoDigrafo(Grafo *grafo);
void grauVerticesGrafoNaoOrientado(Grafo *grafo);
void ordemETamanho(Grafo *grafo);

#endif // MATRIZ_DE_ADJACENCIA_H_INCLUDED
