#include <stdio.h>
#include <stdlib.h>
#include "PilhaDupla.h"

int main(void){
    PilhaDupla *pd;
    pd = cria_PilhaDupla(5);
    struct aluno al;

    al.matricula = 10;
    insere_PilhaDupla(pd, 1, al);
    al.matricula = 90;
    insere_PilhaDupla(pd, 2, al);
    al.matricula = 20;
    insere_PilhaDupla(pd, 1, al);
    al.matricula = 80;
    insere_PilhaDupla(pd, 2, al);
    al.matricula = 30;
    insere_PilhaDupla(pd, 1, al);
    al.matricula = 70;
    insere_PilhaDupla(pd, 2, al);

    remove_PilhaDupla(pd, 2);
    al.matricula = 40;
    insere_PilhaDupla(pd, 1, al);
    return 0;
}