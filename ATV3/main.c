#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "arvoreB.h"
#include "arvoreB.c"

int main(){
    FILE *f;

    //abre um arquivo no modo escrita.
    f = fopen("arvoreB.dat", "wb");
    int chave[n], indice[n+1];


    //ADICIONA OS NÓS DA ARVORE B NUM ARQUIVO CHAMADO "arvoreB.dat"!
    chave[0] = 3;
    chave[1] = 5;
    indice[0] = 1;
    indice[1] = 2;
    indice[2] = 3;
    inserirNo(f, 2, false, chave, indice);

    chave[0] = 1;
    chave[1] = 2;
    indice[0] = -1;
    indice[1] = -1;
    indice[2] = -1;
    inserirNo(f, 2, true, chave, indice);

    chave[0] = 4;
    inserirNo(f, 1, true, chave, indice);

    chave[0] = 6;
    chave[1] = 7;
    inserirNo(f, 2, true, chave, indice);

    fclose(f);

    printf("\n-------TREE SEARCH----------\n\n");

    //abre o arquivo para leitura
    f = fopen("arvoreB.dat", "rb");
    int ind, k;
    NO_B x;

    fseek(f, 0, SEEK_SET);
    fread(&x, sizeof(NO_B), 1, f);
    k = 3;
    ind = buscar(f, &x, k);
    //se "ind" for igual a -1, entao a chave "k" nao foi encontrada.
    if(ind != -1){
        printf("A chave %d bhjbhjbhfoi encontrada na posicao %d do no: \n", k, ind);
        lerNo(&x);
    }
    else printf("A chave %d nao foi encontrada!", k);

    fseek(f, 0, SEEK_SET);
    fread(&x, sizeof(NO_B), 1, f);
    k = 7;
    ind = buscar(f, &x, k);
    if(ind != -1){
        printf("A chave %d foi encontrada na posicao %d do no: \n", k, ind);
        lerNo(&x);
    }
    else printf("A chave %d nao foi encontrada!", k);

    fseek(f, 0, SEEK_SET);
    fread(&x, sizeof(NO_B), 1, f);
    k = 10;
    ind = buscar(f, &x, k);
    if(ind != -1){
        printf("A chave %d foi encontrada na posicao %d do no: \n", k, ind);
        lerNo(&x);
    }
    else printf("A chave %d nao foi encontrada!", k);

    fclose(f);

    puts("\n");
    return(0);
}
