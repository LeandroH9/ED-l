#ifndef LISTA_DE_ADJACENCIA_H_INCLUDED
#define LISTA_DE_ADJACENCIA_H_INCLUDED

typedef struct no *No;

struct no{
   int vertice;
   int peso;
   No next;
};

typedef struct {
    int tipoGrafo; //0 para dígrafo e 1 para grafo não orientado
    int numVertices; //numero de vertices do grafo
    int numArcos; //se o grafo for um dígrafo, esta variavel sera utilizada
    int numArestas; //se for um grafo nao orientado, esta variavel sera utilizada
    No *lista; //armazena a lista de adjacencia
} GraphList;

void graphListView(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

GraphList* graphListReadArq(FILE *log, FILE *arq);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//FILE *arq -> arquivo que contem os dados do grafo orientado ou não orientado.

void insertArqOrEdgesToGraphList(FILE *log, FILE *arq, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//FILE *arq -> arquivo que contem os dados do grafo orientado ou não orientado.
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void  graphListWriteArq(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void graphListWriteArqDFS(FILE *log, GraphList *graph, int *d, int *f);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int *d -> um ponteiro para uma lista que armazena o tempo de descoberta de cada vertice
//int *f -> um ponteiro para uma lista que armazena o tempo de finalização de cada vertice

void graphListDFSVISIT(FILE *log, GraphList *graph, int vertex, char *cor, int *d, int *f, int *tempo);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int vertex -> indica o vertice que está sendo visitado
//int *cor -> um ponteiro para uma lista que armazena a cor de cada vertice
//int *d -> um ponteiro para uma lista que armazena o tempo de descoberta de cada vertice
//int *f -> um ponteiro para uma lista que armazena o tempo de finalização de cada vertice
//int *tempo -> um ponteiro para uma variavel inteira que armazena o tempo

void graphListDFS(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void graphListWriteArqBFS(FILE *log, GraphList *graph, int raiz, int *d, int *f);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int raiz -> raiz da busca
//int *d -> um ponteiro para uma lista que armazena a distancia de cada vertice a origem(raiz)
//int *f -> um ponteiro para uma lista que armazena o vertice predecessor de cada vertice

void graphListBFS(FILE *log, GraphList *graph, int raiz);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int raiz -> raiz da busca

GraphList* graphListInsertVertex(FILE *log, GraphList *graph, int qtd);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int qtd -> indica a quantidade de vertices que serão inseridos no grafo

void insertArqOrEdgesGraphList(FILE *log, GraphList *graph, int ini, int fim, int peso);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int ini -> indica o vertice inicial do arco/aresta
//int fim -> indica o vertice final do arco/aresta
//int peso -> indica o peso do arco

void graphListRemoveVertex(FILE *log, GraphList *graph, int vertex);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int vertex -> indica o vertice que deve ser removido

void graphListRemoveArcOrEdges(FILE *log, GraphList *graph, int ini, int fim);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.
//int ini -> indica o vertice inicial da arco/aresta
//int fim -> indica o vertice final do arco/aresta

void grauVertexGraphListOrd(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void grauVertexGraphListNOrd(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void orderAndSizeGraphList(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void listVertexAndArcGraphList(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void listVertexAndEdgesGraphList(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void checkLacesGraphList(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

void checkMultipleEdgesGraphList(FILE *log, GraphList *graph);
//FILE *log -> ponteiro para um arquivo em que será escrito o nome desta função (log do processamento)
//GraphList *graph -> um ponteiro para a estrutura que armazena os dados do grafo e a lista de adjacencia.

#endif // LISTA_DE_ADJACENCIA_H_INCLUDED


