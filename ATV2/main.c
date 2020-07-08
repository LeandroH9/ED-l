#include <stdio.h>
#include <stdlib.h>
#include "Hashing.c"

int main(){
    struct tabelaHash tbHash;
    struct reg reg;
    int key, pos;

    printf("\n======INICIALIZACAO DA TABELA HASH=============\n");
    initialize(&tbHash);
    puts("");
    show(&tbHash);

    printf("\n======INSERCAO DE ELEMENTOS=============\n");
    reg.key = 1;
    strcpy(reg.name, "Leandro");
    insert(&tbHash, &reg);

    reg.key = 2;
    strcpy(reg.name, "Leiliane");
    insert(&tbHash, &reg);

    reg.key = 3;
    strcpy(reg.name, "Luis");
    insert(&tbHash, &reg);

    reg.key = 4;
    strcpy(reg.name, "Luisa");
    insert(&tbHash, &reg);

    reg.key = 5;
    strcpy(reg.name, "Luana");
    insert(&tbHash, &reg);

    reg.key = 6;
    strcpy(reg.name, "Lorena");
    insert(&tbHash, &reg);

    reg.key = 7;
    strcpy(reg.name, "Lucas");
    insert(&tbHash, &reg);

    reg.key = 8;
    strcpy(reg.name, "Lizandre");
    insert(&tbHash, &reg);

    reg.key = 9;
    strcpy(reg.name, "Lorrayne");
    insert(&tbHash, &reg);

    reg.key = 10;
    strcpy(reg.name, "Luquinha");
    insert(&tbHash, &reg);

    puts("");
    show(&tbHash);

    printf("\n======REMOCAO DE ELEMENTOS=============\n");
    removed(&tbHash, 1);
    removed(&tbHash, 9);
    removed(&tbHash, 4);
    removed(&tbHash, 100);

    reg.key = 11;
    strcpy(reg.name, "Lorran");
    insert(&tbHash, &reg);

    reg.key = 12;
    strcpy(reg.name, "Larissa");
    insert(&tbHash, &reg);

    removed(&tbHash, 10);

    reg.key = 10;
    strcpy(reg.name, "Lucinda");
    insert(&tbHash, &reg);

    reg.key = 10;
    strcpy(reg.name, "Laynara");
    insert(&tbHash, &reg);

    puts("");
    show(&tbHash);

    printf("\n======BUSCA DE ELEMENTOS=============\n");
    printf("\n  Insira uma chave para busca: ");
    scanf("%d", &key);
    pos = search(&tbHash, key);
    if (pos != -1 && pos < startOverflow)
        showInfo(&tbHash, pos);
    else if(pos != -1) {
        printf("\n  Elemento na area de Overflow");
        showInfo(&tbHash, pos);
    }
    else printf("\n  A chave %d nao foi encontrada", key);
    puts("");


    return 0;
}
