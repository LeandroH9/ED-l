#ifndef HASHING_H_INCLUDED
#define HASHING_H_INCLUDED

#define MAX 10
#define startOverflow 7


struct reg{
    int key;
    char name[35];
    int next;
};

struct tabelaHash{
    struct reg tabHash[MAX];
    int disp;
};


void initialize(struct tabelaHash *tbHash);
int hash(int key);
void show(struct tabelaHash *tbHash);
void showInfo(struct tabelaHash *tbHash, int pos);
void insert(struct tabelaHash *tbHash, struct reg *reg);
void removed(struct tabelaHash *tbHash, int key);
int search(struct tabelaHash *tbHash, int key);


#endif // HASHING_H_INCLUDED
