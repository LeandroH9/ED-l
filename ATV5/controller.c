#include "model/matriz_de_adjacencia.c"
#include "model/lista_de_adjacencia.c"


GraphMatrix *graphmatrix;
GraphList *graphlist;


void createGraph(FILE *log, FILE *arq, int optionModel){
    fprintf(log, "%s\n", "createGraph()");
    if(optionModel == 1){
        graphmatrix = graphMatrixReadArq(log, arq);
    } else {
        graphlist = graphListReadArq(log, arq);
    }
}

void viewGraphMatrix(FILE *log){
    fprintf(log, "%s\n", "viewGraphMatrix()");

    graphMatrixView(log, graphmatrix);
}

void DFSMatrix(FILE *log){

    fprintf(log, "%s\n", "DFSMatrix()");

    printf("\n\n ======== BUSCA EM GRAFO (PROFUNDIDADE) =========\n\n");

    graphMatrixDFS(log, graphmatrix);

    printf("\n\nBusca realizada com sucesso, confira o arquivo para ver os resultados...\n\n");
}

void BFSMatrix(FILE *log){
    fprintf(log, "%s\n", "BFSMatrix()");
    int raiz;
    printf("\n\n ======== BUSCA EM GRAFO (LARGURA) =========\n\n");
    printf("Escolha o vertice raiz: [1, %d]: ", graphmatrix->numVertices);
    scanf("%d", &raiz);

    graphMatrixBFS(log, graphmatrix, raiz-1);

    printf("\n\nBusca realizada com sucesso, confira o arquivo para ver os resultados...\n\n");
}


void insertVertexMatrix(FILE *log){
    fprintf(log, "%s\n", "insertVertexMatrix()");

    int qtd;
    printf("\n\n Defina a quantidade de vertices que deseja inserir: ");
    scanf("%d", &qtd);

    graphmatrix = graphMatrixInsertVertex(log, graphmatrix, qtd);

    printf("\n\n Inserido com sucesso...");
}

void insertArqOrEdgesMatrix(FILE *log, int optionType){
    fprintf(log, "%s\n", "insertArqOrEdgesMatrix()");

    int ini, fim, peso=0;
    int numVertices = graphmatrix->numVertices;
    printf("\n\n Defina o arco/aresta que deseja inserir:");
    printf("\n\nVertice inicial [1, %d]: ", numVertices);
    scanf("%d", &ini);
    printf("\nVertice final [1, %d]: ", numVertices);
    scanf("%d", &fim);

    if(ini > numVertices || fim > numVertices || ini < 1 || fim < 1) {
        printf("\n\n ERRO: Nao foi possivel inserir, pois os valores estao incorretos \n\n");
        return;
    }

    if(optionType == 1){
        printf("\nPeso: ");
        scanf("%d", &peso);
        graphMatrixInsertArc(log, graphmatrix, ini, fim, peso);
    } else {
        graphMatrixInsertEdges(log, graphmatrix, ini, fim, peso);
    }
}


void removeVertexMatrix(FILE *log){
    fprintf(log, "%s\n", "removeVertexMatrix()");

    int vertex, numVertices = graphmatrix->numVertices;
    printf("\n\n Defina qual vertice deseja remover [1, %d]: ", numVertices );
    scanf("%d", &vertex);

    if( vertex > numVertices || vertex < 1) {
        printf("\n\n ERRO: Nao foi possivel remover, pois o valor esta incorreto \n\n");
        return;
    }

    graphMatrixRemoveVertex(log, graphmatrix, vertex);

    printf("\n Removido com sucesso...");
}

void removeArqOrEdgesMatrix(FILE *log, int optionType){
    fprintf(log, "%s\n", "removeArqOrEdgesMatrix()");

    int ini, fim;
    int numVertices = graphmatrix->numVertices;

    viewGraphMatrix(log);
    printf("\n\n Defina o arco/aresta que deseja remover:");
    printf("\n\nVertice inicial [1, %d]: ", numVertices);
    scanf("%d", &ini);
    printf("\nVertice final [1, %d]: ", numVertices);
    scanf("%d", &fim);

    if(ini > numVertices || fim > numVertices || ini < 1 || fim < 1) {
        printf("\n\n ERRO: Nao foi possivel inserir, pois os valores estao incorretos \n\n");
        return;
    }

    if(optionType == 1){
        graphMatrixRemoveArc(log, graphmatrix, ini, fim);
    } else {
        graphMatrixRemoveEdges(log, graphmatrix, ini, fim);
    }
}

void grauVertexMatrix(FILE *log, int optionType){
    fprintf(log, "%s\n", "grauVertexMatrix()");

    if(optionType == 1){
        grauVertexGraphMatrixOrd(log, graphmatrix);
    } else {
        grauVertexGraphMatrixNOrd(log, graphmatrix);
    }
}

void orderAndSizeMatrix(FILE *log){
    fprintf(log, "%s\n", "orderAndSizeMatrix()");

    orderAndSizeGraphMatrix(log, graphmatrix);
}

void listVertexAndEdgesOrArcMatrix(FILE *log, int optionType){
    fprintf(log, "%s\n", "listVertexAndEdgesOrArcMatrix()");

    if(optionType == 1){
        listVertexAndArcGraphMatrix(log, graphmatrix);
    } else {
        listVertexAndEdgesGraphMatrix(log, graphmatrix);
    }
}

void checkLacesMatrix(FILE *log){
    fprintf(log, "%s\n", "checkLacesMatrix()");

    checkLacesGraphMatrix(log, graphmatrix);
}

void checkMultipleEdgesMatrix(FILE *log, int optionType){
    fprintf(log, "%s\n", "checkMultipleEdgesMatrix()");

    if(optionType == 1) printf("\n\n Nao existem arestas multiplas em grafos orientados");
    else {
        checkMultipleEdgesGraphMatrix(log, graphmatrix);
    }
}

void viewGraphList(FILE *log){
    graphListView(log, graphlist);
}

void DFSList(FILE *log){
    fprintf(log, "%s\n", "DFSList()");

    printf("\n\n ======== BUSCA EM GRAFO (PROFUNDIDADE) =========\n\n");
    graphListDFS(log, graphlist);

    printf("\n\nBusca realizada com sucesso, confira o arquivo para ver os resultados...\n\n");
}

void BFSList(FILE *log){
    fprintf(log, "%s\n", "BFSList()");

    int raiz;
    printf("\n\n ======== BUSCA EM GRAFO (LARGURA) =========\n\n");
    printf("Escolha o vertice raiz: [1, %d]: ", graphlist->numVertices);
    scanf("%d", &raiz);

    graphListBFS(log, graphlist, raiz-1);

    printf("\n\nBusca realizada com sucesso, confira o arquivo para ver os resultados...\n\n");
}

void insertVertexList(FILE *log){
    fprintf(log, "%s\n", "insertVertexList()");

    int qtd;
    printf("\n\n Defina a quantidade de vertices que deseja inserir: ");
    scanf("%d", &qtd);

    graphlist = graphListInsertVertex(log, graphlist, qtd);

    printf("\n\n Inserido com sucesso...");
}

void insertArqOrEdgesList(FILE *log){
    fprintf(log, "%s\n", "insertArqOrEdgesList()");

    int ini, fim, peso=0;
    int numVertices = graphlist->numVertices;
    printf("\n\n Defina o arco/aresta que deseja inserir:");
    printf("\n\nVertice inicial [1, %d]: ", numVertices);
    scanf("%d", &ini);
    printf("\nVertice final [1, %d]: ", numVertices);
    scanf("%d", &fim);
    printf("\nPeso: ");
    scanf("%d", &peso);

    if(ini > numVertices || fim > numVertices || ini < 1 || fim < 1) {
        printf("\n\n ERRO: Nao foi possivel inserir, pois os valores estao incorretos \n\n");
        return;
    }

    insertArqOrEdgesGraphList(log, graphlist, ini-1, fim-1, peso);

    printf("\n\n Inserido com sucesso...");
}

void removeVertexList(FILE *log){
    fprintf(log, "%s\n", "removeVertexList()");

    int vertex, numVertices = graphlist->numVertices;
    printf("\n\n Defina qual vertice deseja remover [1, %d]: ", numVertices );
    scanf("%d", &vertex);

    if( vertex > numVertices || vertex < 1) {
        printf("\n\n ERRO: Nao foi possivel remover, pois o valor esta incorreto \n\n");
        return;
    }

    graphListRemoveVertex(log, graphlist, vertex);

    printf("\n Removido com sucesso...");
}

void removeArqOrEdgesList(FILE *log, int optionType){
    fprintf(log, "%s\n", "removeArqOrEdgesList()");

    int ini, fim;
    int numVertices = graphlist->numVertices;

    viewGraphList(log);
    printf("\n\n Defina o arco/aresta que deseja remover:");
    printf("\n\nVertice inicial [1, %d]: ", numVertices);
    scanf("%d", &ini);
    printf("\nVertice final [1, %d]: ", numVertices);
    scanf("%d", &fim);

    if(ini > numVertices || fim > numVertices || ini < 1 || fim < 1) {
        printf("\n\n ERRO: Nao foi possivel inserir, pois os valores estao incorretos \n\n");
        return;
    }

    graphListRemoveArcOrEdges(log, graphlist, ini-1, fim-1);

    printf("\n\n Removido com sucesso...");
}

void grauVertexList(FILE *log, int optionType){
    fprintf(log, "%s\n", "grauVertexList()");

    if(optionType == 1){
        grauVertexGraphListOrd(log, graphlist);
    } else {
        grauVertexGraphListNOrd(log, graphlist);
    }
}

void orderAndSizeList(FILE *log){
    fprintf(log, "%s\n", "orderAndSizeList()");

    orderAndSizeGraphList(log, graphlist);
}

void listVertexAndEdgesOrArcList(FILE *log, int optionType){
    fprintf(log, "%s\n", "listVertexAndEdgesOrArcList()");

    if(optionType == 1){
        listVertexAndArcGraphList(log, graphlist);
    } else {
        listVertexAndEdgesGraphList(log, graphlist);
    }
}

void checkLacesList(FILE *log){
    fprintf(log, "%s\n", "checkLacesList()");

    checkLacesGraphList(log, graphlist);
}

void checkMultipleEdgesList(FILE *log, int optionType){
    fprintf(log, "%s\n", "checkMultipleEdgesList()");

    if(optionType == 1) printf("\n\n Nao existem arestas multiplas em grafos orientados");
    else {
        checkMultipleEdgesGraphList(log, graphlist);
    }
}

