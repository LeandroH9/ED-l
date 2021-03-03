

//Respons�vel por ler um n� da �rvore. Foi criado para mostrar o n� quando a chave for encontrada.
void lerNo(NO_B *vetor){
    printf("Numero de chaves: %d \n", vetor->nroChavesArm);
    for(int i=0; i < vetor->nroChavesArm; i++)
         printf("Numero de chave %d = %d \n", i, vetor->chave[i]);
    for(int i=0; i < vetor->nroChavesArm+1; i++)
         printf("Numero de indice %d =  %d \n", i, vetor->indice[i]);
    puts("\n");
    return;
}

//fun��o respons�vel por adicionar n�s, ou seja, ele preenche a struct "NO_B" e salva dentro de um arquivo "f".
void inserirNo(FILE *f, int nroChaves, bool folha, int *chave, int *indice){
    NO_B aux;
    aux.nroChavesArm = nroChaves;
    aux.folha = folha;
    int i=0;
    for(; i < nroChaves; i++){
        aux.chave[i] = *(chave + i);
        aux.indice[i] = *(indice + i);
    }
    aux.indice[i] = *(indice + i);
    fwrite(&aux, sizeof(NO_B), 1, f);
    return;
}

//esta fun��o � respons�vel por buscar uma determinada chave dentro do arquivo f. Se ele encontrar, � retornado a posi��o no n� em que ela se encontra. Se n�o, � retornada -1.
int buscar(FILE *f, NO_B *x, int chave){
    int i=0;
    while(i < x->nroChavesArm && chave > x->chave[i])
        i++;
    if (i < x->nroChavesArm  && chave == x->chave[i]){
        return i;
    }
    if (x->folha == true)
        return -1;
    else {
        fseek(f, x->indice[i]*sizeof(NO_B), SEEK_SET);
        fread(x, sizeof(NO_B), 1, f);
        return buscar(f, x, chave);
    }
}
