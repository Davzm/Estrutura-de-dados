#include <stdio.h>
#include <stdlib.h>
#include "listaCircular.h"
 
static int total = 0, falhas = 0;
 
/* Compara um valor obtido com o esperado e registra o resultado. */
static void confere(const char *descricao, int obtido, int esperado) {
    total++;
    if (obtido == esperado) {
        printf("  [OK]   %s\n", descricao);
    } else {
        falhas++;
        printf("  [FALHA] %s (obtido %d, esperado %d)\n",
               descricao, obtido, esperado);
    }
}
 
/* Insere varias matriculas no final da lista, na ordem do vetor. */
static void preenche(Lista *li, const int mats[], int n) {
    for (int i = 0; i < n; i++) {
        struct aluno al = {0};
        al.matricula = mats[i];
        insere_lista_final(li, al);
    }
}
 
/* ---------------- Questao 1: imprime_lista ---------------- */
static void testa_imprime_lista(void) {
    printf("\n=== Questao 1: imprime_lista ===\n");
 
    /* Aqui a conferencia e visual: compare a linha "Obtido" com a "Esperado". */
    printf("Lista NULL (nao deve imprimir nada):\n");
    printf("  Obtido:   [");
    imprime_lista(NULL);
    printf("]\n");
 
    Lista *vazia = cria_lista();
    printf("Lista vazia (nao deve imprimir nada):\n");
    printf("  Obtido:   [");
    imprime_lista(vazia);
    printf("]\n");
    libera_lista(vazia);
 
    Lista *um = cria_lista();
    int m1[] = {7};
    preenche(um, m1, 1);
    printf("Um elemento:\n  Esperado: 7\n  Obtido:   ");
    imprime_lista(um);
    libera_lista(um);
 
    Lista *li = cria_lista();
    int m2[] = {12, 16, 23, 40};
    preenche(li, m2, 4);
    printf("Lista 12 16 23 40 (sem espaco sobrando no fim):\n");
    printf("  Esperado: 12 16 23 40\n  Obtido:   ");
    imprime_lista(li);
    /* Imprime duas vezes: o resultado deve ser igual, a lista nao pode mudar. */
    printf("Segunda chamada (a lista nao pode ter sido alterada):\n  Obtido:   ");
    imprime_lista(li);
    libera_lista(li);
}
 
/* ---------------- Questao 2: maior_matricula ---------------- */
static void testa_maior_matricula(void) {
    printf("\n=== Questao 2: maior_matricula ===\n");
    int mat;
 
    /* Lista invalida: devolve 0 e NAO altera *mat. */
    mat = -1;
    confere("lista NULL devolve 0", maior_matricula(NULL, &mat), 0);
    confere("lista NULL nao altera *mat", mat, -1);
 
    /* Lista vazia: devolve 0 e NAO altera *mat. */
    Lista *vazia = cria_lista();
    mat = -1;
    confere("lista vazia devolve 0", maior_matricula(vazia, &mat), 0);
    confere("lista vazia nao altera *mat", mat, -1);
    libera_lista(vazia);
 
    /* Um unico elemento. */
    Lista *um = cria_lista();
    int m1[] = {7};
    preenche(um, m1, 1);
    mat = -1;
    confere("um elemento devolve 1", maior_matricula(um, &mat), 1);
    confere("um elemento: maior = 7", mat, 7);
    libera_lista(um);
 
    /* Exemplo do enunciado: o maior esta no final. */
    Lista *li = cria_lista();
    int m2[] = {12, 16, 23, 40};
    preenche(li, m2, 4);
    mat = -1;
    confere("12 16 23 40 devolve 1", maior_matricula(li, &mat), 1);
    confere("12 16 23 40: maior = 40", mat, 40);
    libera_lista(li);
 
    /* O maior esta no inicio (pega erro de percorrer so a partir do 2o). */
    Lista *ini = cria_lista();
    int m3[] = {90, 10, 20, 30};
    preenche(ini, m3, 4);
    mat = -1;
    maior_matricula(ini, &mat);
    confere("maior no inicio (90 10 20 30): maior = 90", mat, 90);
    libera_lista(ini);
 
    /* O maior esta no meio e a lista nao esta ordenada. */
    Lista *meio = cria_lista();
    int m4[] = {5, 80, 3, 41, 9};
    preenche(meio, m4, 5);
    mat = -1;
    maior_matricula(meio, &mat);
    confere("maior no meio (5 80 3 41 9): maior = 80", mat, 80);
 
    /* A lista nao pode ser alterada pela funcao. */
    confere("tamanho continua 5 apos a busca", tamanho_lista(meio), 5);
    libera_lista(meio);
}
 
int main(void) {
    testa_imprime_lista();
    testa_maior_matricula();
 
    printf("\n=== Resumo: %d teste(s) automatico(s), %d falha(s) ===\n",
           total, falhas);
    return falhas == 0 ? 0 : 1;
}