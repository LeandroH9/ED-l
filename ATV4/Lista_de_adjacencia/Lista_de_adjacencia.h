#ifndef LISTA_DE_ADJACENCIA_H_INCLUDED
#define LISTA_DE_ADJACENCIA_H_INCLUDED

typedef struct no *No;

struct no{
   int vertice;
   No next;
};

typedef struct {
    int tipoGrafo; //0 para dígrafo e 1 para grafo não orientado
    int numVertices; //numero de vertices do grafo
    int numArcos; //se o grafo for um dígrafo, esta variavel sera utilizada
    int numArestas; //se for um grafo nao orientado, esta variavel sera utilizada
    No *lista; //armazena a lista de adjacencia
} Grafo;




#endif // LISTA_DE_ADJACENCIA_H_INCLUDED
