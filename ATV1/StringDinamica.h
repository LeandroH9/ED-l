#ifndef STRING_DINAMICA_H_INCLUDED
#define STRING_DINAMICA_H_INCLUDED
//definição do tipo
struct strdim{
    char c;
    struct strdim *prox;
    struct strdim *ant;
};

struct lista{
    struct strdim *priElem;
    struct strdim *ultElem;
};

typedef struct lista Lista;

//cabeçalho das funções
short Menu();
void inicializaString(Lista *S);
void reinicializaString(Lista *S);
void imprimeString(Lista *S);
int tamanhoString(Lista *S);
void insereCaracter(Lista *S, char caracter);
void copiaString(Lista *S1, Lista *S2);
void concatenaString(Lista *S1, Lista *S2, Lista *S3);
struct strdim* encontrarPosicaoStart(Lista *S, int start);
bool removerNCaracteresAposStart(Lista *S, int n, int start);
bool insereSubstringNaStringAposStart(Lista *subString, Lista *S, int start);
bool verificaSeUmaStringEMenorQueOutraString(Lista *S1, Lista *S2);
bool verificaSeUmaStringEIgualOutraString(Lista *S1, Lista *S2);
void verificarSeStringEstaContidaEmOutraString(Lista *SPadrao, Lista *S, int *local);

#endif // STRING_DINAMICA_H_INCLUDED
