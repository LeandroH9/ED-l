#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Hashing.h"

//inicializar
// tratamento de colisao
//inserçao
//busca
//remover


void initialize(struct tabelaHash *tbHash){
    int i = 0;
    tbHash->disp = 7;
    for(; i<MAX; i++){
        tbHash->tabHash[i].key = -1;
        tbHash->tabHash[i].next = -1;
        if(i >= startOverflow && i < MAX-1)
            tbHash->tabHash[i].next = i + 1;
    }
}

int hash(int key){
    int sum = 0, i = 0;
    char str[10];
    itoa(key, str, 10);
    int size = strlen(str);
    for(; i < size; i++)
        sum += str[i];
    return (sum % startOverflow);
}

void show(struct tabelaHash *tbHash){
    int i = 0;
    for(; i < MAX; i++){
        printf("Posicao [%2d] -> Chave [%2d] aponta para [%2d] \n", i, tbHash->tabHash[i].key, tbHash->tabHash[i].next);
    }
    return;
}

void showInfo(struct tabelaHash *tbHash, int pos){
    printf("\n  Posicao na tabela Hash: %d", pos);
    printf("\n  Chave: %d", tbHash->tabHash[pos].key);
    printf("\n  Nome: %s", tbHash->tabHash[pos].name);
}


void insert(struct tabelaHash *tbHash, struct reg *reg){
    int x = hash(reg->key), aux;
    if(search(tbHash, reg->key) != -1)
        printf("\n  Aviso: Nao foi possivel inserir o elemento com a chave %d pois este ja foi inserido!\n ", reg->key);
    else if(tbHash->tabHash[x].key == -1){
        tbHash->tabHash[x].key = reg->key;
        strcpy(tbHash->tabHash[x].name, reg->name);
    } else if(tbHash->disp != -1) {
            if(tbHash->tabHash[x].next == -1){
                tbHash->tabHash[x].next = tbHash->disp;
            } else {
                aux = tbHash->tabHash[x].next;
                while(tbHash->tabHash[aux].next != -1){
                    aux = tbHash->tabHash[aux].next;
                }
                tbHash->tabHash[aux].next = tbHash->disp;
            }
            aux = tbHash->tabHash[tbHash->disp].next;
            tbHash->tabHash[tbHash->disp].key = reg->key;
            strcpy(tbHash->tabHash[tbHash->disp].name, reg->name);
            tbHash->tabHash[tbHash->disp].next = -1;
            tbHash->disp = aux;
    } else printf("\n  Aviso: Nao ha espaco disponivel, area de Overflow esta cheia !!!\n");
    return;
}

void removed(struct tabelaHash *tbHash, int key){
    int x = hash(key);
    int aux, ant = x;
    if(tbHash->tabHash[x].key == key)
        tbHash->tabHash[x].key = -1;
    else if(tbHash->tabHash[x].next != -1){ //verificar se existe elemento na area de Overflow
        aux = tbHash->tabHash[x].next;
        while(aux != -1){ //buscar o elemento na area de Overflow
            if(tbHash->tabHash[aux].key == key){ //verificar chave por chave
                tbHash->tabHash[ant].next = tbHash->tabHash[aux].next; //mudar o encadiamento
                tbHash->tabHash[aux].key = -1;
                tbHash->tabHash[aux].next = tbHash->disp;
                tbHash->disp = aux; //atualiza esta posicao como disponivel
            }
            ant = aux;
            aux = tbHash->tabHash[aux].next;
        }
    } else printf("\n  Aviso: a chave [%d] nao pode ser removida pois ela nao existe\n", key);
}

int search(struct tabelaHash *tbHash, int key){
    int x = hash(key), aux;
    if(tbHash->tabHash[x].key == key)
        return x;
    else if(tbHash->tabHash[x].next != -1){
        aux = tbHash->tabHash[x].next;
        while(aux != -1){
            if(tbHash->tabHash[aux].key == key)
                return aux;
            aux = tbHash->tabHash[aux].next;
        }
    } else return -1;
}




