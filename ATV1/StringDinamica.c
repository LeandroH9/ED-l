#include <stdio.h>
#include "StringDinamica.h"

short Menu(){
int op;
    do{
        system("cls");
        printf("\n=======OPERACOES COM STRING DINAMICA=========\n\n");
        printf(" [1] Reinicializa a string (str1)\n");
        printf(" [2] Imprime a string dinamica \n");
        printf(" [3] Tamanho da string dinamica \n");
        printf(" [4] Insere um determinado caracter (c) na string (str1)\n");
        printf(" [5] Copia o conteudo da string (str1) para a string (str2) \n");
        printf(" [6] Concatena a string (str1) com a string (str2)\n");
        printf(" [7] Remove da string (str1), a quantidade N caracteres a partir da posicao(start)\n");
        printf(" [8] Insere na string (str1) uma substring (subs) a partir da posicao (start)\n");
        printf(" [9] Verifica se uma string (str1) e menor que outra (str2)\n");
        printf(" [10] Verifica se uma string (str1) e igual a outra (str2)\n");
        printf(" [11] Busca a posicao na string (str1) em que a string (padrao) se inicia\n");
        printf("\n Obs: Todas as String Dinamicas utilizadas ja foram inicializadas.");
        printf("\n  Escolha uma opcao: ");
        scanf("%d", &op);
    } while(op < 1 || op > 11);
    return (op);
}

void inicializaString(Lista *S){
    S->priElem = NULL;
    S->ultElem = NULL;
}

void reinicializaString(Lista *S){
    struct strdim *p;
    if(S->priElem == NULL) return;
    p = S->priElem;
    p = p->prox;
    while(p != NULL){
        free(p->ant);
        p = p->prox;
    }
    free(S->ultElem);
    inicializaString(S);
}

void imprimeString(Lista *S){
    struct strdim *p;
    p = S->priElem;
    printf("[");
    while(p != NULL){
        printf("%c", p->c);
        p = p->prox;
    }
    printf("]");
}

int tamanhoString(Lista *S){
    int tam=0;
    struct strdim *p;
    p = S->priElem;
    while(p != NULL){
        tam++;
        p = p->prox;
    }
    return tam;
}

void insereCaracter(Lista *S, char caracter){
    struct strdim *p;
    p = (struct strdim*) malloc(sizeof(struct strdim));
    if (p == NULL) printf("\nHouve um erro na insercao do elemento\n");
    else {
        p->c = caracter;
        p->ant = p->prox = NULL;
        if(S->priElem == NULL)
            S->priElem = p;
        else {
            p->ant = S->ultElem;
            S->ultElem->prox = p;
        }
        S->ultElem = p;
    }
}

void copiaString(Lista *S1, Lista *S2){
    struct strdim *p;
    p = S1->priElem;
    while(p != NULL){
        insereCaracter(S2, p->c);
        p = p->prox;
    }
}

void concatenaString(Lista *S1, Lista *S2, Lista *S3){
    if(!verificaSeUmaStringEIgualOutraString(S1, S3)){
        reinicializaString(S3);
        copiaString(S1, S3);
    }
    copiaString(S2, S3);
}

struct strdim* encontrarPosicaoStart(Lista *S, int start){
    int pos = 1;
    struct strdim *p = S->priElem;
    while(pos < start){
        p = p->prox;
        pos++;
    }
    return p;
}

bool removerNCaracteresAposStart(Lista *S, int n, int start){
    struct strdim *p, *aux, *ant;
    int pos, ind, limite, tamanho = tamanhoString(S);
    limite = tamanho - start + 1;
    if(start < 1 || start > tamanho || n > limite || n < 0) return false;
    if(start == 1 && n == tamanho) reinicializaString(S);
    else{
        p = encontrarPosicaoStart(S, start);
        aux = p->ant;
        ant = p;
        while(n > 0 && p!=NULL){
            p = p->prox;
            free(ant);
            ant = p;
            n--;
        }
        if(start == 1) {S->priElem = p; p->ant = NULL;}
        else if(p == NULL) {S->ultElem = aux; aux->prox = NULL;}
        else {p->ant = aux; aux->prox = p;}
    }
    return true;
}

bool insereSubstringNaStringAposStart(Lista *subString, Lista *S, int start){
    struct strdim *p, *subs;
    int tamanho = tamanhoString(S)+1;
    subs = subString->priElem;
    if(start <= 0 || start > tamanho) return false;
    if(start == tamanho) concatenaString(S, subString, S);
    else{
        p = encontrarPosicaoStart(S, start);
        while(subs != NULL){
            if(p != NULL){
                p->c = subs->c;
                p = p->prox;
            }
            else insereCaracter(S, subs->c);
            subs = subs->prox;
        }
    }
    return true;
}

bool verificaSeUmaStringEMenorQueOutraString(Lista *S1, Lista *S2){
    if(tamanhoString(S1) < tamanhoString(S2)) return true;
    return false;
}

bool verificaSeUmaStringEIgualOutraString(Lista *S1, Lista *S2){
    struct strdim *p1, *p2;
    p1 = S1->priElem;
    p2 = S2->priElem;
    if(verificaSeUmaStringEMenorQueOutraString(S1, S2) || verificaSeUmaStringEMenorQueOutraString(S2, S1))
        return false;
    while(p1 != NULL){
        if(p1->c != p2->c) return false;
        p1 = p1->prox;
        p2 = p2->prox;
    }
    return true;
}

void verificarSeStringEstaContidaEmOutraString(Lista *SPadrao, Lista *S, int *local){
    struct strdim *p1, *p2;
    struct lista Scopy;
    int i=0;
    p1 = S->priElem;
    if(!verificaSeUmaStringEMenorQueOutraString(S, SPadrao))
        while(p1 != NULL){
            p2 = SPadrao->priElem;
            while(p1->c == p2->c){
                p1 = p1->prox;
                p2 = p2->prox;
                if(p2 == NULL) return;
            }
            p1 = p1->prox;
            *local = *local + 1;
        }
    *local = 0;
    return;
}


