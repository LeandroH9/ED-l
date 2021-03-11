
#include "matriz_de_adjacencia.h"


//funcao utilizada para vizualizar o grafo na representacao de matriz
void graphMatrixView(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "graphMatrixView()");

    int nVertices = graph->numVertices, i, j;

    printf("\n  Numero de Vertices: %d\n\n       ", nVertices); //mostra o numero de vertices do grafo

    //mostra na tela a matriz de adjacencia do grafo em questao
    for(i=0; i < nVertices; i++)
        printf(" %3d ", i + 1);
    for(i=0; i < nVertices; i++){
        printf("\n\n%3d    ", i+1);
        for(j=0; j < nVertices; j++){
            printf(" %3d ", graph->matrix[i][j]);
        }
    }
    puts("\n");
    return;
}

//responsável por ler o arquivo 'arq' e salvar seus dados numa matriz de adjacencia que está sendo alocada dinamicamente.
GraphMatrix* graphMatrixReadArq(FILE *log, FILE *arq){
    fprintf(log, "%s\n", "graphMatrixReadArq()");

    int tipoGrafo, nVertices, i;
    GraphMatrix *graph;

    fseek(arq, 0, SEEK_SET);

    fscanf(arq, "%d", &tipoGrafo);
    fscanf(arq, "%d", &nVertices);

    graph = (GraphMatrix*) malloc(sizeof(GraphMatrix)); // Aloca estrutura inicial (numVertices, numArestas, matrix, etc...)

    graph->tipoGrafo = tipoGrafo;
    graph->numVertices = nVertices;
    if(tipoGrafo == 0) graph->numArcos = 0; //caso o grafo seja orientado, a variavel utilizada e graph->numArcos
    else graph->numArestas = 0; //caso contrário, a variavel utilizada e graph->numArestas

    graph->matrix = (int **) malloc(nVertices*sizeof(int*)); //aloca a matriz

    for(i=0; i<nVertices; i++)
        graph->matrix[i] = (int*) calloc(nVertices,sizeof(int)); // Aloca e preenche com zeros cada linha da matriz

    insertArqOrEdgesToGraphMatrix(log, arq, graph); //inserir os arcos/grafos na matriz de adjacencia

    return graph;
}

//responsavel por inserir os arcos/arestas na matriz de adjacencia
void insertArqOrEdgesToGraphMatrix(FILE *log, FILE *arq, GraphMatrix *graph){
    fprintf(log, "%s\n", "insertArqToGraphMatrix()");

    int entrada, saida, peso;
    char pular;

    while(!feof(arq)){
        fscanf(arq, "%d", &saida);
        if(saida == '\n') continue;
        fscanf(arq, "%c", &pular);
        fscanf(arq, "%d", &entrada);
        fscanf(arq, "%c", &pular);
        fscanf(arq, "%d", &peso);

        if (graph->tipoGrafo == 0) { //caso seja um grafo orientado
            graph->matrix[saida-1][entrada-1] = peso;
            graph->numArcos++;
        } else {
            if(saida != entrada) { //caso seja um grafo nao orientado
            graph->matrix[saida-1][entrada-1] += 1;
            graph->matrix[entrada-1][saida-1] += 1;
            } else graph->matrix[saida-1][entrada-1] += 1;
            graph->numArestas++;
        }
    }
    return;
}

//funcao utilizada no caso do usuario alterar o grafo durante o programa
void  graphMatrixWriteArq(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "graphMatrixWriteArq()");

    int i, j, numVertices = graph->numVertices, tipo = graph->tipoGrafo;
    FILE *arq;

    if(tipo == 0) //sera criado um novo arquivo .txt que ira conter as atualizacoes do grafo
        arq = fopen("txt/orientado_com_atualizacoes.txt", "w+");
    else arq = fopen("txt/nao_orientado_com_atualizacoes.txt", "w+");

    fseek(arq, 0, SEEK_SET);

    fprintf(arq, "%d\n", graph->tipoGrafo);
    fprintf(arq, "%d\n", numVertices);

    for(i=0; i < numVertices; i++){
        for(j=0; j < numVertices; j++){
            if(graph->matrix[i][j] > 0 && tipo == 0)
                fprintf(arq, "%d %d %d\n", i+1, j+1, graph->matrix[i][j]);
            else if(tipo == 1){
                if(graph->matrix[i][j] == 1 && j >= i )
                    fprintf(arq, "%d %d %d\n", i+1, j+1, 0);
                else if(graph->matrix[i][j] >= 2 && j >= i ){
                    fprintf(arq, "%d %d %d\n", i+1, j+1, 0);
                    fprintf(arq, "%d %d %d\n", j+1, i+1, 0);
                }
            }
        }
    }
    fclose(arq);
    return;
}



//Implementação de busca em grafo (Profundidade e Largura).

// funcao que vai salvar num arquivo .txt, a tabela gerada na busca de profundidade na matriz de adjacencia
void graphMatrixWriteArqDFS(FILE *log, GraphMatrix *graph, int *d, int *f){
    fprintf(log, "%s\n", "graphMatrixWriteArqDFS()");

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
void graphMatrixDFSVISIT(FILE *log, GraphMatrix *graph, int vertex, char *cor, int *d, int *f, int *tempo){
    fprintf(log, "%s\n", "graphMatrixDFSVISIT()");
    int numVertices = graph->numVertices;

    cor[vertex] = 'c';
    *tempo += 1;
    d[vertex] = *tempo;
    printf("-> Esta no vertice %d, muda ele para a cor CINZA, e registra o tempo de descoberta como %d\n", vertex+1, d[vertex]); //lista o caminhos da raiz/origem para os demais vertices

    for(int j=0; j < numVertices; j++){
        if(graph->matrix[vertex][j] > 0){
            if(cor[j] == 'b'){
                graphMatrixDFSVISIT(log, graph, j, cor, d, f, tempo);
            }
        }
    }
    cor[vertex] = 'p';
    f[vertex] = *tempo = *tempo + 1;
    printf("-> Esta no vertice %d, muda para a cor PRETO, e registra o tempo de finalizacao como %d\n", vertex+1, f[vertex]); //lista o caminhos da raiz/origem para os demais vertices
}

//funcao para percorrer/caminhar no grafo
void graphMatrixDFS(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "graphMatrixDFS()");

    int numVertices = graph->numVertices, i, j, tempo;
    char cor[numVertices];
    int d[numVertices], f[numVertices];

    for(i=0; i < numVertices; i++) d[i] = f[i] = 0;

    for(i=0 ; i < numVertices; i++) cor[i] = 'b';

    tempo = 0;
    printf("  Caminho: \n");
    for(i=0; i < numVertices; i++){
        if (cor[i] == 'b') {
            graphMatrixDFSVISIT(log, graph, i, cor, d, f, &tempo);
        }
    }

    graphMatrixWriteArqDFS(log, graph, d, f);

}

//cria um nova fila (FIFO - First in, First Out)
int* newFila(FILE *log, int n){
    fprintf(log, "%s\n", "newFila()");
    int *Q;
    Q = (int*) malloc(n * sizeof(int));
    for(int i=0; i < n; i++) Q[i] = -1;
    return Q;
}

//adicionar um vertice da fila
void enfileira(FILE *log, int *Q, int vertex, int n){
    fprintf(log, "%s\n", "enfileira()");
    for(int i=0; i < n; i++){
        if(Q[i] == -1) {
            Q[i] = vertex;
            return;
        }
    }
}

//remove um vertice da fila
int desenfileira(FILE *log, int *Q, int n){
    fprintf(log, "%s\n", "desenfileira()");
    int vertex;
    vertex = Q[0];
    for(int i=0; i < n-1; i++){
        Q[i] = Q[i+1];
    }
    Q[n-1] = -1;
    return vertex;
}

//verifica se a fila esta vazia, se sim -> 1, se nao -> 0
short vazia(FILE *log, int *Q, int n){
    fprintf(log, "%s\n", "vazia()");
    for(int i=0; i < n; i++)
        if(Q[i] != -1) return 0;
    return 1;
}

//funcao que vai salvar num arquivo .txt, a tabela gerada na busca de largura na matriz de adjacencia
void graphMatrixWriteArqBFS(FILE *log, GraphMatrix *graph, int raiz, int *d, int *f){
    fprintf(log, "%s\n", "graphMatrixWriteArqBFS()");

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
        fprintf(arq, "%4d   ", f[i]+1);
    }
    fclose(arq);
}

//realiza a busca em largura (breadth-first search - BFS)
void graphMatrixBFS(FILE *log, GraphMatrix *graph, int raiz){
    fprintf(log, "%s\n", "graphMatrixBFS()");

    int numVertices = graph->numVertices, v, u;
    char cor[numVertices];
    int d[numVertices], f[numVertices], *Q;

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
        for(v=0; v < numVertices; v++){
            if(graph->matrix[u][v] > 0){
                if(cor[v] == 'b'){
                    cor[v] = 'c';
                    d[v] = d[u]+1;
                    f[v] = u;
                    printf("-> Esta no vertice %d, muda ele para a cor CINZA, registra a distancia em relacao a raiz de %d, sendo seu antecessor o %d\n", v+1, d[v], f[v]+1);  //lista o caminhos da raiz/origem para os demais vertices
                    enfileira(log, Q, v, numVertices);
                }
            }
        }
        cor[u] = 'p';
        printf("-> Esta no vertice %d, muda para a cor PRETO, e registra a distancia em relacao a raiz de %d, sendo seu antecessor o %d\n", u+1, d[u], f[u]+1);
    }

    graphMatrixWriteArqBFS(log, graph, raiz, d, f);
}


//Atualização do grafo

//inserir vertices no grafo
//essa funcao cria um novo grafo com mais vertices, e passa os vertices, arcos/arestas do antigo grafo para o novo grafo
GraphMatrix* graphMatrixInsertVertex(FILE *log, GraphMatrix *graph, int qtd){
    fprintf(log, "%s\n", "graphMatrixInsertVertex()");

    GraphMatrix *graphcopy;
    int i, j, newNumVertices = graph->numVertices + qtd;

    graphcopy = (GraphMatrix*) malloc(sizeof(GraphMatrix));

    graphcopy->tipoGrafo = graph->tipoGrafo;
    graphcopy->numVertices = newNumVertices;

    if(graphcopy->tipoGrafo == 0) graphcopy->numArcos = graph->numArcos;
    else graphcopy->numArestas = graph->numArestas;

    graphcopy->matrix = (int **) malloc(newNumVertices*sizeof(int*));

    for(i=0; i<newNumVertices; i++)
        graphcopy->matrix[i] = (int*) calloc(newNumVertices,sizeof(int)); // Aloca e preenche com zeros cada linha da matriz

    for(i=0; i<newNumVertices - qtd; i++)
        for(j=0; j<newNumVertices - qtd; j++)
            graphcopy->matrix[i][j] = graph->matrix[i][j];

    free(graph);

    graphMatrixWriteArq(log, graphcopy); //salva no arquivo de atualizacoes

    return graphcopy;
}

//caso seja um grafo orientado, esta funcao e executado para adicionar um arco ao grafo
void graphMatrixInsertArc(FILE *log, GraphMatrix *graph, int ini, int fim, int peso){
    fprintf(log, "%s\n", "graphMatrixInsertArc()");

    graph->matrix[ini-1][fim-1] = peso;
    graph->numArcos++;

    graphMatrixWriteArq(log, graph);  //salva no arquivo de atualizacoes
    printf("\n\n Inserido com sucesso...");
    return;
}

//caso seja um grafo nao orientado, esta funcao e executado para adicionar uma aresta ao grafo
void graphMatrixInsertEdges(FILE *log, GraphMatrix *graph, int ini, int fim, int peso){
    fprintf(log, "%s\n", "graphMatrixInsertEdges()");

    graph->matrix[ini-1][fim-1] += 1;
    graph->matrix[fim-1][ini-1] += 1;
    graphMatrixWriteArq(log, graph);
    printf("\n\n Inserido com sucesso...");

    graph->numArestas++; //salva no arquivo de atualizacoes
    return;
}

void graphMatrixRemoveVertex(FILE *log, GraphMatrix *graph, int vertex){
    fprintf(log, "%s\n", "graphMatrixRemoveVertex()");
}

//caso seja um grafo orientado, esta funcao e executado para remover um arco ao grafo
void graphMatrixRemoveArc(FILE *log, GraphMatrix *graph, int ini, int fim){
    fprintf(log, "%s\n", "graphMatrixRemoveArc()");

    if(graph->matrix[ini-1][fim-1] > 0){
        graph->matrix[ini-1][fim-1] = 0;
        graph->numArcos--;
        graphMatrixWriteArq(log, graph);
        printf("\n\n Removido com sucesso...");
    } else {
        printf("\n\nERRO: NAO E POSSIVEL REMOVER ESTE ARCO, POIS ELE NAO EXISTE");
    }
    return;
}

//caso seja um grafo nao orientado, esta funcao e executado para remover uma aresta ao grafo
void graphMatrixRemoveEdges(FILE *log, GraphMatrix *graph, int ini, int fim){
    fprintf(log, "%s\n", "graphMatrixRemoveEdges()");

    if(graph->matrix[ini-1][fim-1] > 0){
        graph->matrix[ini-1][fim-1] -= 1;
        graph->matrix[fim-1][ini-1] -= 1;
        graph->numArestas--;
        graphMatrixWriteArq(log, graph);
        printf("\n\n Removido com sucesso...");
    } else {
        printf("\n\nERRO: NAO E POSSIVEL REMOVER ESTA ARESTA, POIS ELA NAO EXISTE");
    }
    return;
}

//Verificação de propriedades

//verifica o grau dos vertices em grafos orientados
void grauVertexGraphMatrixOrd(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "grauVertexGraphMatrixOrd()");

    int nVertices = graph->numVertices;
    int i, j, grauentrada=0, grausaida=0;

    printf("\n\n  Vertice   Grau de Entrada  Grau de saida\n");
    for(i=0; i < nVertices; i++){
        printf("  %3d       ", i+1);
        for(j=0; j < nVertices; j++){
            if(graph->matrix[i][j] > 0)
                grausaida += 1;
            if(graph->matrix[j][i] > 0)
                grauentrada += 1;
        }
        printf("%7d          %6d\n", grauentrada, grausaida);
        grauentrada = grausaida = 0;
    }
    return;
}

//verifica o grau dos vertices em grafos nao orientados
void grauVertexGraphMatrixNOrd(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "grauVertexGraphMatrixNOrd()");

    int nVertices = graph->numVertices;
    int i, j, grau = 0;

    printf("\n\n  Vertice   Grau\n");
    for(i=0; i < nVertices; i++){
        printf("  %3d       ", i+1);
        for(j=0; j < nVertices; j++){
            if(graph->matrix[i][j] > 0)
                grau += graph->matrix[i][j];
        }
        printf("%2d\n", grau);
        grau = 0;
    }
    return;
}

//mostra a ordem e o tamanho do grafo
void orderAndSizeGraphMatrix(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "orderAndSizeGraphMatrix()");

    int order = graph->numVertices, size;

    if(graph->tipoGrafo == 0) size = order + graph->numArcos;
    else size = order + graph->numArestas;

    printf("\n  Ordem: %d\n  Tamanho: %d \n" , order, size);
    return;
}

//lista todos os vertices e arestas do grafo orientado
void listVertexAndArcGraphMatrix(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "listVertexAndArcGraphMatrix()");

    int numVertices = graph->numVertices;
    int i, j;

    printf("\n  Vertices: {");
    for(i=0; i < numVertices; i++)
        printf(" %d ", i+1);
    printf("}");

    printf("\n  Arcos: {");
    for(i=0; i < numVertices; i++){
        for(j=0; j < numVertices; j++){
            if(graph->matrix[i][j] > 0 ) //PEGA TODOS OS ARCOS (ENTRADA E SAIDA)
                printf(" (%d, %d) ", i+1, j+1);
        }
    }
    printf("}\n");
    return;
}

//lista todos os vertices e arestas do grafo nao orientado
void listVertexAndEdgesGraphMatrix(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "listVertexAndEdgesGraphMatrix()");

    int numVertices = graph->numVertices;
    int i, j;

    printf("\n  Vertices: {");
    for(int i=0; i < numVertices; i++)
        printf(" %d ", i+1);
    printf("}");

    printf("\n  Arestas: {");
    for(i=0; i < numVertices; i++){
        for(j=0; j < numVertices; j++){
            if(graph->matrix[i][j] == 1 && j >= i )
                printf(" (%d, %d) ", i+1, j+1);
            if(graph->matrix[i][j] == 2 && j >= i )
                printf(" (%d, %d) (%d, %d) ", i+1, j+1, j+1 , i+1);
        }
    }
    printf("}\n");
    return;
}

//verifica todos os lacos dos grafos
void checkLacesGraphMatrix(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "checkLacesGraphMatrix()");

    int numVertices = graph->numVertices, i;
    int lacos[numVertices], aux = 0;
    for(i=0; i < numVertices; i++){
        if(graph->matrix[i][i] > 0){
            lacos[i] = 1;
            aux = 1;
        }
    }
    if(aux != 0){
        printf("\n  Vertices com lacos: {");
        for(i=0; i < numVertices; i++)
            if(lacos[i] == 1)
                printf(" %d ", i+1);
        printf("}\n");
    } else printf("\n  Nao existe nenhum laco \n");
}

//verifica as arestas multiplas do grafo
void checkMultipleEdgesGraphMatrix(FILE *log, GraphMatrix *graph){
    fprintf(log, "%s\n", "checkMultipleEdgesGraphMatrix()");

    int numVertices = graph->numVertices, i, j, aux=0;
    printf("\n  Arestas multiplas: {");
    for(i=0; i < numVertices; i++){
        for(j=0; j < numVertices; j++){
            if(graph->matrix[i][j] >= 2){
                printf(" (%d, %d) ", i+1, j+1);
                aux =1;
            }
        }
    }
    printf("}\n");
    if(!aux) printf("\n  Nao existe nenhuma aresta multipla \n");
}


