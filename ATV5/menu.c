

int firstMenu(FILE *log){
    fprintf(log, "%s\n", "firstMenu()");
    int option;
    do {
        system("cls");
        printf("\n\n=========TRABALHO PRATICO FINAL===========\n\n");
        printf(" [1] Grafo orientado (digrafo) \n");
        printf(" [2] Grafo nao orientado\n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 2);
    return option;
}

int secondMenu(FILE *log){
    fprintf(log, "%s\n", "secondMenu()");
    int option;
    do {
        system("cls");
        printf("\n\n=========TRABALHO PRATICO FINAL===========\n\n");
        printf(" [1] Leitura do arquivo para matriz de adjancencia \n");
        printf(" [2] Leitura do arquivo para lista de adjacencia \n");
        printf(" [3] Voltar \n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 3);
    return option;
}

int mainMenu(FILE *log){
    fprintf(log, "%s\n", "mainMenu()");
    int option;
    do {
        system("cls");
        printf("\n\n=========TRABALHO PRATICO FINAL===========\n\n");
        printf(" [1] Mostrar grafo \n");
        printf(" [2] Busca em grafo \n");
        printf(" [3] Atualizacao de grafo\n");
        printf(" [4] Verificacao de propriedades\n");
        printf(" [5] Caminho em digrafo\n");
        printf(" [6] Sair \n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 6);
    return option;
}

int menuGraphSearch(FILE *log){
    fprintf(log, "%s\n", "menuGraphSearch()");
    int option;
    do {
        system("cls");
        printf("\n\n=========BUSCA EM GRAFO===========\n\n");
        printf(" [1] Profundidade \n");
        printf(" [2] Largura\n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 2);
    return option;
}

int menuUpdateGraph(FILE *log){
    fprintf(log, "%s\n", "menuUpdateGraph()");
    int option;
    do {
        system("cls");
        printf("\n\n=========ATUALIZACAO DE GRAFO===========\n\n");
        printf(" [1] Insercao de vertices \n");
        printf(" [2] Insercao de arestas/arcos \n");
        printf(" [3] Remocao de vertices \n");
        printf(" [4] Remocao de arestas/arcos \n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 4);
    return option;
}

int menuVerificationOfProperties(FILE *log){
    fprintf(log, "%s\n", "menuVerificationOfProperties()");
    int option;
    do {
        system("cls");
        printf("\n\n=========VERIFICACAO DE PROPRIEDADES===========\n\n");
        printf(" [1] Grau dos vertices \n");
        printf(" [2] Ordem e tamanho \n");
        printf(" [3] Listar vertices e arcos/arestas\n");
        printf(" [4] Verificar o numero de lacos \n");
        printf(" [5] Verificar o numero de arestas multiplas \n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 5);
    return option;
}

int exitProgram(FILE *log){
    fprintf(log, "%s\n", "exitProgram()");
    int option;
    do {
        system("cls");
        printf("\n\n [1] Continuar no programa\n");
        printf(" [2] Fechar o programa \n\n");
        printf(" Escolha um opcao: ");
        scanf("%d", &option);
    } while (option < 1 || option > 2);
    return option;
}


