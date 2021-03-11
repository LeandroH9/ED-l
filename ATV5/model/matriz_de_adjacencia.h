#ifndef MATRIZ_DE_ADJACENCIA_H_INCLUDED
#define MATRIZ_DE_ADJACENCIA_H_INCLUDED

typedef struct{
    int tipoGrafo; //0 para dígrafo e 1 para grafo não orientado
    int numVertices; //numero de vertices do grafo
    int numArcos; //se o grafo for um dígrafo, esta variavel sera utilizada
    int numArestas; //se for um grafo não orientado, está variavel será utilizada
    int **matrix; //armazena a matriz de adjacencia
} GraphMatrix;


void graphMatrixView(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

GraphMatrix* graphMatrixReadArq(FILE *log, FILE *arq);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//FILE *arq -> arquivo que contem os dados do grafo orientado ou não orientado.

void insertArqOrEdgesToGraphMatrix(FILE *log, FILE *arq, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//FILE *arq -> arquivo que contem os dados do grafo orientado ou não orientado.
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void graphMatrixWriteArq(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void graphMatrixWriteArqDFS(FILE *log, GraphMatrix *graph, int *d, int *f);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int *d -> um ponteiro para uma lista que armazena o tempo de descoberta de cada vertice
//int *f -> um ponteiro para uma lista que armazena o tempo de finalização de cada vertice

void graphMatrixDFSVISIT(FILE *log, GraphMatrix *graph, int vertex, char *cor, int *d, int *f, int *tempo);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int vertex -> indica o vertice que está sendo visitado
//int *cor -> um ponteiro para uma lista que armazena a cor de cada vertice
//int *d -> um ponteiro para uma lista que armazena o tempo de descoberta de cada vertice
//int *f -> um ponteiro para uma lista que armazena o tempo de finalização de cada vertice
//int *tempo -> um ponteiro para uma variavel inteira que armazena o tempo


void graphMatrixDFS(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

int* newFila(FILE *log, int n);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//int n -> tamanho da fila

void enfileira(FILE *log, int *Q, int vertex, int n);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//int *Q -> um ponteiro para uma lista que armazena a fila
//int vertex -> indica o vertice que será adicionado a fila
//int n -> tamanho da fila

int desenfileira(FILE *log, int *Q, int n);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//int *Q -> um ponteiro para uma lista que armazena a fila
//int n -> tamanho da fila

short vazia(FILE *log, int *Q, int n);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//int *Q -> um ponteiro para uma lista que armazena a fila
//int n -> tamanho da fila

void graphMatrixWriteArqBFS(FILE *log, GraphMatrix *graph, int raiz, int *d, int *f);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int raiz -> raiz da busca
//int *d -> um ponteiro para uma lista que armazena a distancia de cada vertice a origem(raiz)
//int *f -> um ponteiro para uma lista que armazena o vertice predecessor de cada vertice

void graphMatrixBFS(FILE *log, GraphMatrix *graph, int raiz);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int raiz -> raiz da busca

GraphMatrix* graphMatrixInsertVertex(FILE *log, GraphMatrix *graph, int qtd);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int qtd -> indica a quantidade de vertices que serão inseridos no grafo

void graphMatrixInsertArc(FILE *log, GraphMatrix *graph, int ini, int fim, int peso);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int ini -> indica o vertice inicial do arco
//int fim -> indica o vertice final do arco
//int peso -> indica o peso do arco


void graphMatrixInsertEdges(FILE *log, GraphMatrix *graph, int ini, int fim, int peso);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int ini -> indica o vertice inicial da aresta
//int fim -> indica o vertice final do aresta
//int peso -> indica o peso do arco

void graphMatrixRemoveVertex(FILE *log, GraphMatrix *graph, int vertex);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int vertex -> indica o vertice que deve ser removido

void graphMatrixRemoveArc(FILE *log, GraphMatrix *graph, int ini, int fim);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int ini -> indica o vertice inicial da aresta
//int fim -> indica o vertice final do aresta

void graphMatrixRemoveEdges(FILE *log, GraphMatrix *graph, int ini, int fim);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.
//int ini -> indica o vertice inicial da aresta
//int fim -> indica o vertice final do aresta

void grauVertexGraphMatrixOrd(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void grauVertexGraphMatrixNOrd(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void orderAndSizeGraphMatrix(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void listVertexAndArcGraphMatrix(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void listVertexAndEdgesGraphMatrix(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void checkLacesGraphMatrix(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

void checkMultipleEdgesGraphMatrix(FILE *log, GraphMatrix *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphMatrix *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a matriz de adjacencia.

#endif // MATRIZ_DE_ADJACENCIA_H_INCLUDED
