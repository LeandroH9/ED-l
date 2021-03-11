#include "lista_de_adjacencia.h"

//funcao utilizada para vizualizar o grafo na representacao de lista
void graphListView(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "graphListView()");
    int nVertices = graph->numVertices, i, j;
    No p;

    printf("Numero de Vertices: %d\n\n", nVertices);

    printf(" LISTA ");
    for(i=0; i < nVertices; i++){
        printf("\n| %2d | -> ", i+1);
        for(p = graph->lista[i]; p != NULL; p = p->next)
           printf("%d,%d  -> ", p->vertice+1, p->peso);
    }

    printf("\n");
    return;
}

//responsável por ler o arquivo 'arq' e salvar seus dados numa lista de adjacencia que está sendo alocada dinamicamente.
GraphList* graphListReadArq(FILE *log, FILE *arq){
    fprintf(log, "%s\n", "graphListReadArq()");
    int tipoGrafo, nVertices, i;
    GraphList *graph;


    fseek(arq, 0, SEEK_SET);

    fscanf(arq, "%d", &tipoGrafo);
    fscanf(arq, "%d", &nVertices);

    graph = (GraphList*) malloc(sizeof(GraphList));

    graph->tipoGrafo = tipoGrafo;
    graph->numVertices = nVertices;
    if(tipoGrafo == 0) graph->numArcos = 0;
    else graph->numArestas = 0;


    graph->lista = malloc( nVertices * sizeof(No*));

    for(i=0; i < nVertices; i++)
        graph->lista[i] = NULL;

    insertArqOrEdgesToGraphList(log, arq, graph);

    return graph;
}

//responsavel por inserir os arcos/arestas na list de adjacencia
void insertArqOrEdgesToGraphList(FILE *log, FILE *arq, GraphList *graph){
    fprintf(log, "%s\n", "insertArqOrEdgesToGraphList()");
    int ini, fim, peso;
    char pular;

    while(!feof(arq)){
        fscanf(arq, "%d", &ini);
        if(ini == '\n') continue;
        fscanf(arq, "%c", &pular);
        fscanf(arq, "%d", &fim);
        fscanf(arq, "%c", &pular);
        fscanf(arq, "%d", &peso);

        if(graph->tipoGrafo == 0){ //se for um digrafo, os arcos que sai recebem -1
            insertArqOrEdgesGraphList(log, graph, ini-1, fim-1, peso);
            graph->numArcos++;
        } else {
            insertArqOrEdgesGraphList(log, graph, ini-1, fim-1, peso);
            insertArqOrEdgesGraphList(log, graph, fim-1, ini-1, peso);
            graph->numArestas++;
        }
    }
    return;
}

//funcao utilizada no caso do usuario alterar o grafo durante o programa
void  graphListWriteArq(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "graphListWriteArq()");

    int i, j, numVertices = graph->numVertices;
    FILE *arq;
    No p;

    if(graph->tipoGrafo == 0)
        arq = fopen("txt/orientado_com_atualizacoes.txt", "w+");
    else arq = fopen("txt/nao_orientado_com_atualizacoes.txt", "w+");

    fseek(arq, 0, SEEK_SET);

    fprintf(arq, "%d\n", graph->tipoGrafo);
    fprintf(arq, "%d\n", numVertices);

    for(i=0; i < numVertices; i++){
        for(p = graph->lista[i]; p != NULL; p = p->next){
            fprintf(arq, "%d %d %d\n", i+1, p->vertice+1, p->peso);
        }
    }

    fclose(arq);
    return;
}

//Implementação de busca em grafo (Profundidade e Largura).

// funcao que vai salvar num arquivo .txt, a tabela gerada na busca de profundidade na lista de adjacencia
void graphListWriteArqDFS(FILE *log, GraphList *graph, int *d, int *f){
    fprintf(log, "%s\n", "graphListWriteArqDFS()");

    FILE *arq;
    int numVertices = graph->numVertices, i;

    arq = fopen("txt/tabela_busca_profundidade.txt", "w+");

    fseek(arq, 0, SEEK_SET);

    if(graph->tipoGrafo == 0) fprintf(arq, "%s\n\n", "Arquivo: digrafo.txt");
    else fprintf(arq, "%s\n\n", "Arquivo: nao_orientado.txt");

    fprintf(arq, "%8s   ", "vertices");

    for(i=0; i < numVertices; i++)
        fprintf(arq, "%3d   ", i+1);

    fprintf(arq, "\n%8c   ", 'd');

    for(i=0; i < numVertices; i++)
        fprintf(arq, "%3d   ", d[i]);

    fprintf(arq, "\n%8s   ", "f");

    for(i=0; i < numVertices; i++)
        fprintf(arq, "%3d   ", f[i]);

    fclose(arq);

}

// funcao responsavel por visitar os vertices
void graphListDFSVISIT(FILE *log, GraphList *graph, int vertex, char *cor, int *d, int *f, int *tempo){
    fprintf(log, "%s\n", "graphListDFSVISIT()");
    int numVertices = graph->numVertices;
    No p;
    cor[vertex] = 'c';
    *tempo += 1;
    d[vertex] = *tempo;
    printf("-> Esta no vertice %d, muda ele para a cor CINZA, e registra o tempo de descoberta como %d\n", vertex, d[vertex]);

    for(p = graph->lista[vertex]; p != NULL; p = p->next){
        if(cor[p->vertice] == 'b'){
            graphListDFSVISIT(log, graph, p->vertice, cor, d, f, tempo);
        }
    }

    cor[vertex] = 'p';
    f[vertex] = *tempo = *tempo + 1;
    printf("-> Esta no vertice %d, muda para a cor PRETO, e registra o tempo de finalizacao como %d\n", vertex, f[vertex]);
}

//funcao para percorrer/caminhar no grafo
void graphListDFS(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "graphListDFS()");

    int numVertices = graph->numVertices, i, j, tempo;
    char cor[numVertices];
    int d[numVertices], f[numVertices];

    for(i=0; i < numVertices; i++) d[i] = f[i] = 0;

    for(i=0 ; i < numVertices; i++) cor[i] = 'b';

    tempo = 0;
    printf("  Caminho: \n");
    for(i=0; i < numVertices; i++){
        if (cor[i] == 'b') {
            graphListDFSVISIT(log, graph, i, cor, d, f, &tempo);
        }
    }

    graphListWriteArqDFS(log, graph, d, f);


}

//funcao que vai salvar num arquivo .txt, a tabela gerada na busca de largura na lista de adjacencia
void graphListWriteArqBFS(FILE *log, GraphList *graph, int raiz, int *d, int *f){
    fprintf(log, "%s\n", "graphListWriteArqBFS()");

    FILE *arq;
    int numVertices = graph->numVertices, i;

    arq = fopen("txt/tabela_busca_largura.txt", "w+");

    fseek(arq, 0, SEEK_SET);

    if(graph->tipoGrafo == 0) fprintf(arq, "%s\n", "Arquivo: digrafo.txt");
    else fprintf(arq, "%s\n", "Arquivo: nao_orientado.txt");

    fprintf(arq, "%s: %d\n\n", "Raiz", raiz+1);

    fprintf(arq, "%8s   %4s   ", "vertices", "raiz");

    for(i=0; i < numVertices; i++){
        if(i == raiz) continue;
        fprintf(arq, "%4d   ", i+1);
    }

    fprintf(arq, "\n%8c   %4d   ", 'd', d[raiz]);

    for(i=0; i < numVertices; i++){
        if(i == raiz) continue;
        fprintf(arq, "%4d   ", d[i]);
    }

    fprintf(arq, "\n%8s   %4d   ", "pi", f[raiz]);

    for(i=0; i < numVertices; i++){
        if(i == raiz) continue;
        fprintf(arq, "%4d   ", f[i]);
    }
    fclose(arq);
}

//realiza a busca em largura (breadth-first search - BFS)
void graphListBFS(FILE *log, GraphList *graph, int raiz){
    fprintf(log, "%s\n", "graphListBFS()");

    int numVertices = graph->numVertices, v, u;
    char cor[numVertices];
    int d[numVertices], f[numVertices], *Q;
    No p;
    for(u=0; u < numVertices; u++){
        if(u == raiz) continue;
        cor[u] = 'b';
        d[u] = -1;
        f[u] = -1;
    }
    cor[raiz] = 'c';
    d[raiz] = 0;
    f[raiz] = -1;

    printf("-> Esta no vertice raiz %d, muda ele para a cor CINZA, registra a distancia em relacao a raiz de %d, sendo seu antecessor o %d\n", raiz+1, d[raiz], f[raiz]+1);  //lista o caminhos da raiz/origem para os demais vertices

    Q = newFila(log, numVertices);

    enfileira(log, Q, raiz, numVertices);

    while (!vazia(log, Q, numVertices)){
        u = desenfileira(log, Q, numVertices);
        for(p = graph->lista[u]; p != NULL; p = p->next){
            v = p->vertice;
            if(cor[v] == 'b'){
                cor[v] = 'c';
                d[v] = d[u]+1;
                f[v] = u;
                printf("-> Esta no vertice %d, muda ele para a cor CINZA, registra a distancia em relacao a raiz de %d, sendo seu antecessor o %d\n", v+1, d[v], f[v]+1);
                enfileira(log, Q, v, numVertices);
            }
        }
        cor[u] = 'p';
        printf("-> Esta no vertice %d, muda para a cor PRETO, e registra a distancia em relacao a raiz de %d, sendo seu antecessor o %d\n", u+1, d[u], f[u]+1);
    }

    graphListWriteArqBFS(log, graph, raiz, d, f);
}


//Atualização do grafo
//inserir vertices no grafo
//essa funcao cria um novo grafo com mais vertices, e passa os vertices, arcos/arestas do antigo grafo para o novo grafo
GraphList* graphListInsertVertex(FILE *log, GraphList *graph, int qtd){
    fprintf(log, "%s\n", "graphListInsertVertex()");

    GraphList *graphcopy;
    int i, j, newNumVertices = graph->numVertices + qtd;

    graphcopy = (GraphList*) malloc(sizeof(GraphList));

    graphcopy->tipoGrafo = graph->tipoGrafo;
    graphcopy->numVertices = newNumVertices;

    if(graphcopy->tipoGrafo == 0) graphcopy->numArcos = graph->numArcos;
    else graphcopy->numArestas = graph->numArestas;

    graphcopy->lista = malloc( newNumVertices * sizeof(No*));

    for(i=0; i < newNumVertices; i++)
        graphcopy->lista[i] = NULL;

    for(i=0; i<newNumVertices - qtd; i++)
        graphcopy->lista[i] = graph->lista[i];

    free(graph);

    graphListWriteArq(log, graphcopy);

    return graphcopy;
}

//funcao responsavel por adicionar um arco/aresta no grafo
void insertArqOrEdgesGraphList(FILE *log, GraphList *graph, int ini, int fim, int peso){
    fprintf(log, "%s\n", "insertArqOrEdgesGraphList()");
    No p, novo;
   for(p = graph->lista[ini]; p != NULL; p = p->next)
        if(p->vertice == fim) return;
   novo = malloc(sizeof(struct no));
   novo->vertice = fim;
   novo->peso = peso;
   novo->next = graph->lista[ini];
   graph->lista[ini] = novo;
    graphListWriteArq(log, graph);
   return;
}

void graphListRemoveVertex(FILE *log, GraphList *graph, int vertex){
    fprintf(log, "%s\n", "graphListRemoveVertex()");
}

//esta funcao e executado para remover um arco/aresta do grafo
void graphListRemoveArcOrEdges(FILE *log, GraphList *graph, int ini, int fim){
    fprintf(log, "%s\n", "graphListRemoveArc()");
    No p, ant;
    int firstVertex = 1;

    for(p = graph->lista[ini]; p != NULL; p = p->next){
        if(p->vertice == fim) break;
        firstVertex  = 0;
        ant = p;
    }

    if(p == NULL) {
        printf("ERRO: NAO E POSSIVEL REMOVER ESTE ARCO/ARESTA, POIS ELE NAO EXISTE");
        return;
    }

    if(firstVertex) graph->lista[ini] = p->next; //caso seja o unico arco deste vertice
    else ant->next = p->next;
    free(p);


    if(graph->tipoGrafo == 0) graph->numArcos--;
    else graph->numArestas--;


    graphListWriteArq(log, graph);

    return;
}

//Verificação de propriedades

//verifica o grau dos vertices em grafos orientados
void grauVertexGraphListOrd(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "grauVertexGraphListOrd()");
    int nVertices = graph->numVertices;
    int i, j, grauentrada=0, grausaida=0;
    No p;

    printf("\n\n  Vertice   Grau de Entrada  Grau de saida\n");
    for(i=0; i < nVertices; i++){
        printf("  %3d       ", i+1);
        for(p = graph->lista[i]; p != NULL; p = p->next)
            grausaida++;
        for(j=0; j < nVertices; j++){
            for(p = graph->lista[j]; p != NULL; p = p->next)
                if(p->vertice == i) grauentrada++;
        }
        printf("%7d          %6d\n", grauentrada, grausaida);
        grauentrada = grausaida = 0;
    }
    return;
}

//verifica o grau dos vertices em grafos nao orientados
void grauVertexGraphListNOrd(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "grauVertexGraphListNOrd()");
    int nVertices = graph->numVertices;
    int i, j, grau=0;
    No p;
    printf("\n\n  Vertice   Grau\n");
    for(i=0; i < nVertices; i++){
        printf("  %3d       ", i+1);
        for(p = graph->lista[i]; p != NULL; p = p->next) grau++;
        printf("%2d\n", grau);
        grau = 0;
    }
    return;
}

//mostra a ordem e o tamanho do grafo
void orderAndSizeGraphList(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "orderAndSizeGraphList()");

    int order = graph->numVertices, size;

    if(graph->tipoGrafo == 0) size = order + graph->numArcos;
    else size = order + graph->numArestas;

    printf("\n  Ordem: %d\n  Tamanho: %d \n" , order, size);
    return;
}

//lista todos os vertices e arestas do grafo orientado
void listVertexAndArcGraphList(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "listVertexAndArcGraphList()");

    int numVertices = graph->numVertices;
    int i, j;
    No p;

    printf("\n  Vertices: {");
    for(i=0; i < numVertices; i++)
        printf(" %d ", i+1);
    printf("}");

    printf("\n  Arcos: {");
    for(i=0; i < numVertices; i++){
        for(p = graph->lista[i]; p != NULL; p = p->next)
            printf(" (%d, %d) ", i+1, p->vertice+1);
    }
    printf("}\n");
    return;
}

//lista todos os vertices e arestas do grafo nao orientado
void listVertexAndEdgesGraphList(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "listVertexAndEdgesGraphList()");

    int numVertices = graph->numVertices;
    int i, j;
    No p;

    printf("\n  Vertices: {");
    for(int i=0; i < numVertices; i++)
        printf(" %d ", i+1);
    printf("}");

    printf("\n  Arestas: {");
    for(i=0; i < numVertices; i++){
        for(p = graph->lista[i]; p != NULL; p = p->next)
            if(i <= p->vertice)
            printf(" (%d, %d) ", i+1, p->vertice+1);
    }
    printf("}\n");
    return;
}

//verifica todos os lacos dos grafos
void checkLacesGraphList(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "checkLacesGraphList()");

    int numVertices = graph->numVertices, i, quant=0;
    No p;

    printf("\n  Vertices com lacos: {");
    for(i=0; i < numVertices; i++){
        for(p = graph->lista[i]; p != NULL; p = p->next)
            if(i == p->vertice) {
                printf(" %d ", i+1);
                quant++;
            }
    }
    printf("}\n");
    if (quant == 0) printf("\n  Nao existe nenhum laco \n");
    else printf("\n  Existem %d lacos \n", quant);

}

//verifica as arestas multiplas do grafo
void checkMultipleEdgesGraphList(FILE *log, GraphList *graph){
    fprintf(log, "%s\n", "checkMultipleEdgesGraphList()");

    int numVertices = graph->numVertices, i, aux=0;
    No p, q;

    printf("\n  Arestas multiplas: {");
    for(i=0; i < numVertices; i++){
        for(p = graph->lista[i]; p != NULL; p = p->next){
            for(q = graph->lista[p->vertice]; q != NULL; q = q->next){
                if(i == q->vertice){
                    printf(" (%d, %d) ", i, p->vertice);
                    aux = 1;
                }
            }
        }
    }
    printf("}\n");
    if(!aux) printf("\n  Nao existe nenhuma aresta multipla \n");
}
