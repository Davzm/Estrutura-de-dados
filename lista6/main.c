/* ============================================================
   main.c - Testes da Lista de exercicios, Aula 07
   Estrutura de Dados I - UFPB

   Cobre as Questoes 1 a 8.
   Compilar:
     gcc -Wall -Wextra -std=c11 listaCircular.c main.c -o prog
   Verificar memoria:
     valgrind --leak-check=full ./prog

   Observacao: se alguma funcao tiver laco infinito, o programa
   trava no teste dela (Ctrl+C). Isso tambem indica o defeito.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "listaCircular.h"

static int total = 0, falhas = 0;

/* Compara um valor obtido com o esperado e registra o resultado. */
static void confere(const char *descricao, int obtido, int esperado) {
    total++;
    if (obtido == esperado) {
        printf("  [OK]    %s\n", descricao);
    } else {
        falhas++;
        printf("  [FALHA] %s (obtido %d, esperado %d)\n",
               descricao, obtido, esperado);
    }
}

/* Cria um aluno so com matricula (notas zeradas). */
static struct aluno novo(int mat) {
    struct aluno al = {0};
    al.matricula = mat;
    return al;
}

/* Insere varias matriculas no final da lista, na ordem do vetor. */
static void preenche(Lista *li, const int mats[], int n) {
    for (int i = 0; i < n; i++)
        insere_lista_final(li, novo(mats[i]));
}

/* Confere o conteudo completo da lista: tamanho, ordem das matriculas
   e circularidade (a posicao n+1 tem de ser a primeira de novo). */
static void confere_lista(const char *descricao, Lista *li,
                          const int esperado[], int n) {
    int ok = (tamanho_lista(li) == n);
    struct aluno al;
    for (int i = 0; ok && i < n; i++) {
        if (!busca_lista_pos(li, i + 1, &al) || al.matricula != esperado[i])
            ok = 0;
    }
    if (ok && n > 0) {
        if (!busca_ciclica(li, n + 1, &al) || al.matricula != esperado[0])
            ok = 0;
    }
    total++;
    if (ok) {
        printf("  [OK]    %s\n", descricao);
    } else {
        falhas++;
        printf("  [FALHA] %s\n          esperado:", descricao);
        for (int i = 0; i < n; i++) printf(" %d", esperado[i]);
        printf("\n          obtido:  ");
        imprime_lista(li);
    }
}

/* ---------------- Questao 1: imprime_lista ---------------- */
static void testa_imprime_lista(void) {
    printf("\n=== Questao 1: imprime_lista (conferencia visual) ===\n");

    printf("Lista NULL (nada entre os colchetes):\n  Obtido:   [");
    imprime_lista(NULL);
    printf("]\n");

    Lista *vazia = cria_lista();
    printf("Lista vazia (nada entre os colchetes):\n  Obtido:   [");
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
    printf("Lista 12 16 23 40:\n  Esperado: 12 16 23 40\n  Obtido:   ");
    imprime_lista(li);
    printf("Segunda chamada (a lista nao pode ter mudado):\n  Obtido:   ");
    imprime_lista(li);
    libera_lista(li);
}

/* ---------------- Questao 2: maior_matricula ---------------- */
static void testa_maior_matricula(void) {
    printf("\n=== Questao 2: maior_matricula ===\n");
    int mat;

    mat = -1;
    confere("lista NULL devolve 0", maior_matricula(NULL, &mat), 0);
    confere("lista NULL nao altera *mat", mat, -1);

    Lista *vazia = cria_lista();
    mat = -1;
    confere("lista vazia devolve 0", maior_matricula(vazia, &mat), 0);
    confere("lista vazia nao altera *mat", mat, -1);
    libera_lista(vazia);

    Lista *um = cria_lista();
    int m1[] = {7};
    preenche(um, m1, 1);
    mat = -1;
    confere("um elemento devolve 1", maior_matricula(um, &mat), 1);
    confere("um elemento: maior = 7", mat, 7);
    libera_lista(um);

    Lista *li = cria_lista();
    int m2[] = {12, 16, 23, 40};
    preenche(li, m2, 4);
    mat = -1;
    confere("12 16 23 40 devolve 1", maior_matricula(li, &mat), 1);
    confere("12 16 23 40: maior = 40", mat, 40);
    libera_lista(li);

    Lista *ini = cria_lista();
    int m3[] = {90, 10, 20, 30};
    preenche(ini, m3, 4);
    mat = -1;
    maior_matricula(ini, &mat);
    confere("maior no inicio (90 10 20 30): maior = 90", mat, 90);
    libera_lista(ini);

    Lista *meio = cria_lista();
    int m4[] = {5, 80, 3, 41, 9};
    preenche(meio, m4, 5);
    mat = -1;
    maior_matricula(meio, &mat);
    confere("maior no meio (5 80 3 41 9): maior = 80", mat, 80);
    confere("tamanho continua 5", tamanho_lista(meio), 5);
    libera_lista(meio);
}

/* ---------------- Questao 3: conta_aprovados ---------------- */
static void insere_notas(Lista *li, int mat, float n1, float n2, float n3) {
    struct aluno al = novo(mat);
    al.n1 = n1; al.n2 = n2; al.n3 = n3;
    insere_lista_final(li, al);
}

static void testa_conta_aprovados(void) {
    printf("\n=== Questao 3: conta_aprovados ===\n");

    confere("lista NULL devolve 0", conta_aprovados(NULL), 0);

    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", conta_aprovados(vazia), 0);
    libera_lista(vazia);

    Lista *um = cria_lista();
    insere_notas(um, 1, 8.0f, 8.0f, 8.0f);
    confere("um aprovado", conta_aprovados(um), 1);
    libera_lista(um);

    Lista *um2 = cria_lista();
    insere_notas(um2, 1, 2.0f, 3.0f, 4.0f);
    confere("um reprovado", conta_aprovados(um2), 0);
    libera_lista(um2);

    Lista *li = cria_lista();
    insere_notas(li, 1, 9.0f, 8.0f, 10.0f);  /* media 9.0  -> aprova       */
    insere_notas(li, 2, 5.0f, 6.0f, 4.0f);   /* media 5.0  -> reprova      */
    insere_notas(li, 3, 7.0f, 7.0f, 7.0f);   /* media 7.0  -> aprova (>=)  */
    insere_notas(li, 4, 6.0f, 7.0f, 7.0f);   /* media 6.67 -> reprova      */
    confere("misto: 2 aprovados (incluindo media exatamente 7.0)",
            conta_aprovados(li), 2);
    libera_lista(li);

    Lista *ult = cria_lista();
    insere_notas(ult, 1, 1.0f, 1.0f, 1.0f);
    insere_notas(ult, 2, 1.0f, 1.0f, 1.0f);
    insere_notas(ult, 3, 10.0f, 10.0f, 10.0f);
    confere("aprovado so no ultimo elemento", conta_aprovados(ult), 1);
    libera_lista(ult);
}

/* ---------------- Questao 4: busca_ciclica ---------------- */
static void testa_busca_ciclica(void) {
    printf("\n=== Questao 4: busca_ciclica ===\n");
    struct aluno al;

    al.matricula = -1;
    confere("lista NULL devolve 0", busca_ciclica(NULL, 1, &al), 0);

    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", busca_ciclica(vazia, 1, &al), 0);
    libera_lista(vazia);

    Lista *li = cria_lista();
    int m[] = {12, 16, 23, 40};
    preenche(li, m, 4);

    al.matricula = -1;
    confere("k = 1 devolve 1", busca_ciclica(li, 1, &al), 1);
    confere("k = 1 -> 12", al.matricula, 12);
    busca_ciclica(li, 4, &al);
    confere("k = 4 -> 40", al.matricula, 40);
    busca_ciclica(li, 5, &al);
    confere("k = 5 -> 12 (volta ao inicio)", al.matricula, 12);
    busca_ciclica(li, 7, &al);
    confere("k = 7 -> 23", al.matricula, 23);
    busca_ciclica(li, 1000, &al);
    confere("k = 1000 -> 40", al.matricula, 40);

    al.matricula = -1;
    confere("k = 0 devolve 0", busca_ciclica(li, 0, &al), 0);
    confere("k = -3 devolve 0", busca_ciclica(li, -3, &al), 0);
    confere("k invalido nao altera *al", al.matricula, -1);
    confere("tamanho continua 4", tamanho_lista(li), 4);
    libera_lista(li);

    Lista *um = cria_lista();
    int m1[] = {7};
    preenche(um, m1, 1);
    busca_ciclica(um, 5, &al);
    confere("um elemento, k = 5 -> ele mesmo", al.matricula, 7);
    libera_lista(um);
}

/* ---------------- Questao 5: remove_lista_pos ---------------- */
static void testa_remove_lista_pos(void) {
    printf("\n=== Questao 5: remove_lista_pos ===\n");

    confere("lista NULL devolve 0", remove_lista_pos(NULL, 1), 0);

    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", remove_lista_pos(vazia, 1), 0);
    libera_lista(vazia);

    Lista *li = cria_lista();
    int m[] = {12, 16, 23, 40};
    preenche(li, m, 4);

    confere("pos = 0 devolve 0", remove_lista_pos(li, 0), 0);
    confere("pos = -1 devolve 0", remove_lista_pos(li, -1), 0);
    confere("pos = 5 (> tamanho) devolve 0", remove_lista_pos(li, 5), 0);
    confere_lista("posicoes invalidas nao alteram a lista", li, m, 4);

    confere("remove pos 2 devolve 1", remove_lista_pos(li, 2), 1);
    int e1[] = {12, 23, 40};
    confere_lista("depois de pos 2: 12 23 40", li, e1, 3);

    confere("remove pos 1 devolve 1", remove_lista_pos(li, 1), 1);
    int e2[] = {23, 40};
    confere_lista("depois de pos 1: 23 40 (inicio passa a ser 23)", li, e2, 2);

    confere("remove ultima (pos 2) devolve 1", remove_lista_pos(li, 2), 1);
    int e3[] = {23};
    confere_lista("depois da ultima: 23 (ainda circular)", li, e3, 1);

    confere("remove elemento unico devolve 1", remove_lista_pos(li, 1), 1);
    confere("lista fica vazia", lista_vazia(li), 1);

    confere("lista continua valida: insere 99", insere_lista_final(li, novo(99)), 1);
    int e4[] = {99};
    confere_lista("lista com 99", li, e4, 1);
    libera_lista(li);

    /* remove a ultima de uma lista maior */
    Lista *l2 = cria_lista();
    int m2[] = {1, 2, 3, 4, 5};
    preenche(l2, m2, 5);
    remove_lista_pos(l2, 5);
    int e5[] = {1, 2, 3, 4};
    confere_lista("1..5 remove pos 5 -> 1 2 3 4", l2, e5, 4);
    remove_lista_pos(l2, 3);
    int e6[] = {1, 2, 4};
    confere_lista("depois remove pos 3 -> 1 2 4", l2, e6, 3);
    libera_lista(l2);
}

/* ---------------- Questao 6: rotaciona_lista ---------------- */
static void testa_rotaciona_lista(void) {
    printf("\n=== Questao 6: rotaciona_lista ===\n");

    confere("lista NULL devolve 0", rotaciona_lista(NULL, 1), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", rotaciona_lista(vazia, 1), 0);
    libera_lista(vazia);

    int m[] = {12, 16, 23, 40};
    Lista *li = cria_lista();
    preenche(li, m, 4);
    confere("k = -1 devolve 0", rotaciona_lista(li, -1), 0);
    confere_lista("k = -1 nao altera a lista", li, m, 4);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 4);
    confere("k = 1 devolve 1", rotaciona_lista(li, 1), 1);
    int e1[] = {16, 23, 40, 12};
    confere_lista("k = 1 -> 16 23 40 12", li, e1, 4);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 4);
    rotaciona_lista(li, 4);
    confere_lista("k = 4 -> inalterada (volta completa)", li, m, 4);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 4);
    rotaciona_lista(li, 0);
    confere_lista("k = 0 -> inalterada", li, m, 4);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 4);
    rotaciona_lista(li, 6);
    int e2[] = {23, 40, 12, 16};
    confere_lista("k = 6 -> 23 40 12 16", li, e2, 4);
    libera_lista(li);

    li = cria_lista();
    int m1[] = {7};
    preenche(li, m1, 1);
    confere("um elemento, k = 3 devolve 1", rotaciona_lista(li, 3), 1);
    confere_lista("um elemento continua igual", li, m1, 1);
    libera_lista(li);
}

/* ---------------- Questao 7: concatena_listas ---------------- */
static void testa_concatena_listas(void) {
    printf("\n=== Questao 7: concatena_listas ===\n");

    Lista *a = cria_lista();
    confere("li1 NULL devolve 0", concatena_listas(NULL, a), 0);
    confere("li2 NULL devolve 0", concatena_listas(a, NULL), 0);
    confere("mesma lista duas vezes devolve 0", concatena_listas(a, a), 0);
    libera_lista(a);

    /* caso do enunciado */
    Lista *l1 = cria_lista(), *l2 = cria_lista();
    int ma[] = {1, 2}, mb[] = {3, 4};
    preenche(l1, ma, 2);
    preenche(l2, mb, 2);
    confere("1 2 + 3 4 devolve 1", concatena_listas(l1, l2), 1);
    int e1[] = {1, 2, 3, 4};
    confere_lista("li1 fica 1 2 3 4 (circular)", l1, e1, 4);
    confere("li2 fica vazia", lista_vazia(l2), 1);
    confere("li2 continua valida: insere 9", insere_lista_final(l2, novo(9)), 1);
    int e2[] = {9};
    confere_lista("li2 com 9", l2, e2, 1);
    libera_lista(l1);
    libera_lista(l2);

    /* li1 vazia */
    l1 = cria_lista(); l2 = cria_lista();
    preenche(l2, mb, 2);
    confere("li1 vazia: devolve 1", concatena_listas(l1, l2), 1);
    confere_lista("li1 vazia herda 3 4", l1, mb, 2);
    confere("li2 fica vazia", lista_vazia(l2), 1);
    libera_lista(l1);
    libera_lista(l2);

    /* li2 vazia */
    l1 = cria_lista(); l2 = cria_lista();
    preenche(l1, ma, 2);
    confere("li2 vazia: devolve 1", concatena_listas(l1, l2), 1);
    confere_lista("li1 continua 1 2", l1, ma, 2);
    confere("li2 continua vazia", lista_vazia(l2), 1);
    libera_lista(l1);
    libera_lista(l2);

    /* as duas vazias */
    l1 = cria_lista(); l2 = cria_lista();
    confere("as duas vazias: devolve 1", concatena_listas(l1, l2), 1);
    confere("li1 continua vazia", lista_vazia(l1), 1);
    confere("li2 continua vazia", lista_vazia(l2), 1);
    libera_lista(l1);
    libera_lista(l2);

    /* um elemento em cada */
    l1 = cria_lista(); l2 = cria_lista();
    int mc[] = {1}, md[] = {2};
    preenche(l1, mc, 1);
    preenche(l2, md, 1);
    concatena_listas(l1, l2);
    int e3[] = {1, 2};
    confere_lista("1 + 2 -> 1 2", l1, e3, 2);
    libera_lista(l1);
    libera_lista(l2);
}

/* ---------------- Questao 8: josephus ---------------- */
/* Resposta de referencia (formula recursiva, posicao a partir de 0). */
static int josephus_ref(int n, int k) {
    int r = 0;
    for (int i = 2; i <= n; i++)
        r = (r + k) % i;
    return r + 1;           /* matriculas 1..n */
}

static void testa_josephus(void) {
    printf("\n=== Questao 8: josephus ===\n");
    int sob;

    confere("lista NULL devolve 0", josephus(NULL, 3, &sob), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", josephus(vazia, 3, &sob), 0);
    libera_lista(vazia);

    Lista *li = cria_lista();
    int m7[] = {1, 2, 3, 4, 5, 6, 7};
    preenche(li, m7, 7);
    confere("k = 0 devolve 0", josephus(li, 0, &sob), 0);
    confere("k = -2 devolve 0", josephus(li, -2, &sob), 0);
    confere("k invalido nao altera a lista", tamanho_lista(li), 7);

    sob = -1;
    confere("1..7, k = 3 devolve 1", josephus(li, 3, &sob), 1);
    confere("1..7, k = 3 -> sobrevivente 4", sob, 4);
    confere("lista fica vazia", lista_vazia(li), 1);
    confere("lista continua valida: insere 5", insere_lista_final(li, novo(5)), 1);
    int e1[] = {5};
    confere_lista("lista com 5", li, e1, 1);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m7, 7);
    josephus(li, 1, &sob);
    confere("1..7, k = 1 -> sobrevivente 7", sob, 7);
    libera_lista(li);

    li = cria_lista();
    int m5[] = {1, 2, 3, 4, 5};
    preenche(li, m5, 5);
    josephus(li, 10, &sob);
    confere("1..5, k = 10 (k > n) -> sobrevivente 4", sob, 4);
    libera_lista(li);

    li = cria_lista();
    int m1[] = {42};
    preenche(li, m1, 1);
    sob = -1;
    confere("um elemento, k = 5 devolve 1", josephus(li, 5, &sob), 1);
    confere("um elemento: sobrevivente = 42", sob, 42);
    confere("lista fica vazia", lista_vazia(li), 1);
    libera_lista(li);

    /* varredura: n de 1 a 10 e k de 1 a 12, comparando com a formula */
    int erros = 0;
    for (int n = 1; n <= 10; n++) {
        for (int k = 1; k <= 12; k++) {
            Lista *l = cria_lista();
            for (int i = 1; i <= n; i++)
                insere_lista_final(l, novo(i));
            int s = -1;
            int r = josephus(l, k, &s);
            if (r != 1 || s != josephus_ref(n, k) || !lista_vazia(l)) {
                erros++;
                printf("    n=%d k=%d: obtido %d (ret %d), esperado %d\n",
                       n, k, s, r, josephus_ref(n, k));
            }
            libera_lista(l);
        }
    }
    confere("varredura n=1..10, k=1..12 contra a formula (erros)", erros, 0);
}

int main(void) {
    testa_imprime_lista();
    testa_maior_matricula();
    testa_conta_aprovados();
    testa_busca_ciclica();
    testa_remove_lista_pos();
    testa_rotaciona_lista();
    testa_concatena_listas();
    testa_josephus();

    printf("\n=== Resumo: %d teste(s) automatico(s), %d falha(s) ===\n", total, falhas);
    return falhas == 0 ? 0 : 1;
}