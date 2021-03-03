#ifndef ARVOREB_H_INCLUDED
#define ARVOREB_H_INCLUDED

#define n 2

//struct utilizada para armazenar os dados referentes aos nos da arvore B.
typedef struct {
    int nroChavesArm;
    bool folha; //1 -> true, 0 -> false
    int chave[n];
    int indice[n + 1];
} NO_B;

//prototipo das funcoes utilizadas
void lerNo(NO_B *vetor);
void inserirNo(FILE *f, int nroChaves, bool folha, int *chave, int *indice);
int buscar(FILE *f, NO_B *x, int chave);


#endif // ARVOREB_H_INCLUDED
