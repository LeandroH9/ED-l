#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "StringDinamica.c"

int main(){
int op, nro, start, limite, local;
struct lista str1, str2, str3, subs, padrao;
char letra;
    inicializaString(&str1);
    inicializaString(&str2);
    inicializaString(&str3);
    inicializaString(&subs);
    inicializaString(&padrao);
    do{
        op = Menu();
        system("cls");
        switch(op){
            case 1: reinicializaString(&str1);
                    printf("\n  Todos os elementos contidos na Str1 foram removidos...");
                    break;
            case 2: printf("\n Str1 = ");
                    imprimeString(&str1);
                    printf("\n Str2 = ");
                    imprimeString(&str2);
                    printf("\n Str3 = ");
                    imprimeString(&str3);
                    break;
            case 3: printf("\n Tamanho da Str1 = %d", tamanhoString(&str1));
                    printf("\n Tamanho da Str2 = %d", tamanhoString(&str2));
                    printf("\n Tamanho da Str3 = %d", tamanhoString(&str3));
                    break;
            case 4: printf("\n Insira um determinado caracter (c) na Str1\n\n");
                    do{
                        setbuf(stdin, NULL);
                        printf("Caracter (Aperte a tecla '+' para finalizar): ");
                        scanf("%c", &letra);
                        if(letra != '+' && letra != '\n') insereCaracter(&str1, letra);
                    } while(letra != '+');
                    imprimeString(&str1);
                    break;
            case 5: reinicializaString(&str2);
                    copiaString(&str1, &str2);
                    printf("\n Str1 copiada para a Str2 com sucesso...\n");
                    printf("\n Str2 = ");
                    imprimeString(&str2);
                    break;
            case 6: concatenaString(&str1, &str2, &str3);
                    printf("\n Concatenacao entre Str1 e Str2 realizado com sucesso...");
                    printf("\n Str1 + Str2 = Str3 ");
                    imprimeString(&str3);
                    break;
            case 7: printf("\n String 1 = ");
                    imprimeString(&str1);
                    printf("\n A partir de que posicao voce deseja remover (Entre 1 e %d): ", tamanhoString(&str1));
                    scanf("%d", &start);
                    printf("\n Quantos caracteres voce deseja remover (Numero maximo possivel = %d): ", tamanhoString(&str1) - start + 1);
                    scanf("%d", &nro);
                    if(removerNCaracteresAposStart(&str1, nro, start)){
                        printf("\n Foi removido com sucesso...");
                        printf("\n Resultado da String 1 = ");
                        imprimeString(&str1);
                    } else printf("\n  Nao foi possivel remover, pois os dados foram enviados incorretamente");
                    break;
            case 8: printf("\n Insira o texto desejado para inserir na String (Aperte ENTER para parar de inserir) \n String: ");
                    setbuf(stdin, NULL);
                    do{
                        letra = getchar();
                        if(letra != '\n') insereCaracter(&subs, letra);
                    } while(letra != '\n');
                    printf("\n Str1 = ");
                    imprimeString(&str1);
                    printf("\n Substring = ");
                    imprimeString(&subs);
                    printf("\n\n A partir de que posicao voce deseja adicionar este texto [1, %d]: ", tamanhoString(&str1)+1);
                    scanf("%d", &start);
                    if(insereSubstringNaStringAposStart(&subs, &str1, start)){
                        printf("\n Substring inserida com sucesso");
                        printf("\n Str1 com a Substring = ");
                        imprimeString(&str1);
                    }
                    else printf("\n Houve um erro na insercao da Substring");
                    reinicializaString(&subs);
                    break;
            case 9: printf("\n Tamanho da Str1 = %d", tamanhoString(&str1));
                    printf("\n Tamanho da Str2 = %d", tamanhoString(&str2));
                    if(verificaSeUmaStringEMenorQueOutraString(&str1, &str2))
                        printf("\n\n  A Str1 e menor que a Str2");
                    else printf("\n\n  A Str1 nao e menor que a Str2");
                    break;
            case 10:printf("\n Str1 = ");
                    imprimeString(&str1);
                    printf("\n Str2 = ");
                    imprimeString(&str2);
                    if(verificaSeUmaStringEIgualOutraString(&str1, &str2))
                        printf("\n\n  A String 1 e igual a String 2");
                    else printf("\n\n  A String 1 nao e igual a String 2");
                    break;
            case 11:local = 1;
                    printf("\n Insira a String Padrao (Aperte ENTER para parar de inserir) \n String: ");
                    setbuf(stdin, NULL);
                    do{
                        letra = getchar();
                        if(letra != '\n') insereCaracter(&padrao, letra);
                    } while(letra != '\n');
                    verificarSeStringEstaContidaEmOutraString(&padrao, &str1, &local);
                    if(local == 0)
                        printf("\n A String Padrao nao esta dentro da String (str1)");
                    else {
                        printf("\n Str1 = ");
                        imprimeString(&str1);
                        printf("\n Padrao = ");
                        imprimeString(&padrao);
                        printf("\n\n A String Padrao esta dentro da String (str1) e a sua posicao de inicio e: [%d]", local);
                    }
                    reinicializaString(&padrao);
                    break;
        }
        puts("\n");
        system("pause");
    } while(op);
    return(0);
}
