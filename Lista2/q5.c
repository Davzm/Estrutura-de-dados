/*
linha 11 - sizeof errado (retorna o tamanho de um ponteiro)
linha 16 - tentativa de acessar endereço já esvaziado
linha 19 - alocação nova sem antes liberar o endereço
linhas 22/23 - duplo free
linha 26 - loop tenta acessar posição não alocada
*/

#include <stdio.h>
#include <stdlib.h>
 
typedef struct {
    int   matricula;
    char  nome[32];
    float media;
} Aluno;
 
int main(void) {
    Aluno *a = malloc(sizeof(Aluno));
    if (a == NULL) {
        return 1;
    }
    a->matricula = 20260145;
    a->media = 8.7f;

    printf("%.1f\n", a->media);
    free(a);
    a = NULL;

    Aluno *b = malloc(sizeof(Aluno));
    if (b == NULL) {
        return 1;
    }
    b->matricula = 20260200;

    free(b);
    b = NULL;

    int *v = malloc(5 * sizeof(int));
    if (v == NULL) {
        return 1;
    }
    for (int i = 0; i < 5; i++) {
        v[i] = i * i;
    }
    free(v);
    v = NULL;

    return 0;
}