/* ============================================================
   main.c - Testes da Lista de exercicios, Aula 08
   Estrutura de Dados I - UFPB - Lista duplamente encadeada

   COMO USAR: os testes de cada questao ficam desligados ate
   voce implementar a funcao. Para ligar, troque 0 por 1 no
   #define da questao (logo abaixo) e acrescente o prototipo da
   funcao no .h. Assim o programa sempre compila e linka com o
   que voce ja fez.

   Compilar:
     gcc -Wall -Wextra -std=c11 lista_duplamente_encadeada.c main.c -o prog
   Verificar memoria:
     valgrind --leak-check=full ./prog

   Dica: a lista so pode ser alterada pelas funcoes da biblioteca,
   entao daqui nao da para fabricar uma lista inconsistente de
   proposito. O que da para fazer e conferir, depois de CADA
   operacao, que lista_consistente devolve 1 (Questao 2).
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "lista_duplamente_encadeada.h"

/* ----- Ligue (1) ou desligue (0) o teste de cada questao ----- */
#ifndef TESTA_Q1
#define TESTA_Q1 1   /* imprime_lista_inversa (conferencia visual)  */
#endif
#ifndef TESTA_Q2
#define TESTA_Q2 1   /* lista_consistente                           */
#endif
#ifndef TESTA_Q3
#define TESTA_Q3 1   /* remove_lista corrigida                      */
#endif
#ifndef TESTA_Q4
#define TESTA_Q4 1   /* remove_lista_pos                            */
#endif
#ifndef TESTA_Q5
#define TESTA_Q5 0   /* move_para_inicio                            */
#endif
#ifndef TESTA_Q6
#define TESTA_Q6 0   /* remove_todos                                */
#endif
#ifndef TESTA_Q7
#define TESTA_Q7 0   /* inverte_lista                               */
#endif
#ifndef TESTA_Q8
#define TESTA_Q8 0   /* eh_palindromo                               */
#endif

static int total = 0, falhas = 0;

/* Compara um valor obtido com o esperado e registra o resultado. */
void confere(const char *descricao, int obtido, int esperado) {
    total++;
    if (obtido == esperado) {
        printf("  [OK]    %s\n", descricao);
    } else {
        falhas++;
        printf("  [FALHA] %s (obtido %d, esperado %d)\n",
               descricao, obtido, esperado);
    }
}

struct aluno novo(int mat) {
    struct aluno al = {0};
    al.matricula = mat;
    return al;
}

/* Insere as matriculas do vetor no final da lista, na ordem. */
void preenche(Lista *li, const int mats[], int n) {
    for (int i = 0; i < n; i++)
        insere_lista_final(li, novo(mats[i]));
}

/* Confere a lista inteira: tamanho e ordem das matriculas (lidos por
   prox) e, se a Questao 2 estiver ligada, os dois encadeamentos.
   Ordem correta por prox + lista_consistente == 1 garantem que o
   caminho de volta (ant) tambem esta correto. */
void confere_lista(const char *descricao, Lista *li,
                   const int esperado[], int n) {
    int ok = (tamanho_lista(li) == n);
    struct aluno al;
    for (int i = 0; ok && i < n; i++) {
        if (!busca_lista_pos(li, i + 1, &al) || al.matricula != esperado[i])
            ok = 0;
    }
#if TESTA_Q2
    if (!lista_consistente(li))
        ok = 0;
#endif
    total++;
    if (ok) {
        printf("  [OK]    %s\n", descricao);
    } else {
        falhas++;
        printf("  [FALHA] %s\n          esperado:", descricao);
        for (int i = 0; i < n; i++) printf(" %d", esperado[i]);
        printf("\n          obtido (tamanho %d):", tamanho_lista(li));
        for (int i = 1; i <= tamanho_lista(li); i++) {
            if (busca_lista_pos(li, i, &al)) printf(" %d", al.matricula);
        }
        printf("\n");
    }
}

/* ---------------- Questao 1: imprime_lista_inversa ---------------- */
#if TESTA_Q1
static void testa_q1(void) {
    printf("\n=== Questao 1: imprime_lista_inversa (conferencia visual) ===\n");

    printf("Lista NULL:\n  Esperado: (lista vazia)\n  Obtido:   ");
    imprime_lista_inversa(NULL);

    Lista *vazia = cria_lista();
    printf("Lista vazia:\n  Esperado: (lista vazia)\n  Obtido:   ");
    imprime_lista_inversa(vazia);
    libera_lista(vazia);

    Lista *um = cria_lista();
    int m1[] = {5};
    preenche(um, m1, 1);
    printf("Um elemento:\n  Esperado: 5\n  Obtido:   ");
    imprime_lista_inversa(um);
    libera_lista(um);

    Lista *li = cria_lista();
    int m3[] = {33, 23, 16};
    preenche(li, m3, 3);
    printf("Lista 33 23 16:\n  Esperado: 16 23 33\n  Obtido:   ");
    imprime_lista_inversa(li);
    printf("Segunda chamada (a lista nao pode ter sido alterada):\n");
    printf("  Esperado: 16 23 33\n  Obtido:   ");
    imprime_lista_inversa(li);
    confere_lista("a lista continua 33 23 16", li, m3, 3);
    libera_lista(li);
}
#endif

/* ---------------- Questao 2: lista_consistente ---------------- */
#if TESTA_Q2
static void testa_q2(void) {
    printf("\n=== Questao 2: lista_consistente ===\n");

    confere("lista NULL devolve 0", lista_consistente(NULL), 0);

    Lista *li = cria_lista();
    confere("lista vazia e consistente", lista_consistente(li), 1);

    insere_lista_final(li, novo(10));
    confere("um elemento e consistente", lista_consistente(li), 1);

    insere_lista_final(li, novo(20));
    insere_lista_final(li, novo(30));
    confere("inseridos no final: consistente", lista_consistente(li), 1);

    insere_lista_inicio(li, novo(5));
    confere("insere no inicio: consistente", lista_consistente(li), 1);

    insere_lista_ordenada(li, novo(25));
    confere("insere ordenada (meio): consistente", lista_consistente(li), 1);

    remove_lista_inicio(li);
    confere("remove inicio: consistente", lista_consistente(li), 1);
    remove_lista_final(li);
    confere("remove final: consistente", lista_consistente(li), 1);
    remove_lista(li, 20);
    confere("remove do meio: consistente", lista_consistente(li), 1);
    libera_lista(li);
}
#endif

/* ---------------- Questao 3: remove_lista corrigida ---------------- */
#if TESTA_Q3
static void testa_q3(void) {
    printf("\n=== Questao 3: remove_lista ===\n");
    int m[] = {33, 23, 16};

    confere("lista NULL devolve 0", remove_lista(NULL, 33), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", remove_lista(vazia, 33), 0);
    libera_lista(vazia);

    Lista *li = cria_lista();
    preenche(li, m, 3);
    confere("matricula ausente devolve 0", remove_lista(li, 99), 0);
    confere_lista("matricula ausente nao altera a lista", li, m, 3);

    confere("remove o primeiro (33) devolve 1", remove_lista(li, 33), 1);
    int e1[] = {23, 16};
    confere_lista("depois de remover 33: 23 16", li, e1, 2);

    confere("remove o ultimo (16) devolve 1", remove_lista(li, 16), 1);
    int e2[] = {23};
    confere_lista("depois de remover 16: 23", li, e2, 1);

    confere("remove o unico (23) devolve 1", remove_lista(li, 23), 1);
    confere("lista fica vazia", lista_vazia(li), 1);
    confere("lista continua valida: insere 7", insere_lista_final(li, novo(7)), 1);
    int e3[] = {7};
    confere_lista("lista com 7", li, e3, 1);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 3);
    confere("remove o do meio (23) devolve 1", remove_lista(li, 23), 1);
    int e4[] = {33, 16};
    confere_lista("depois de remover 23: 33 16", li, e4, 2);
    libera_lista(li);
}
#endif

/* ---------------- Questao 4: remove_lista_pos ---------------- */
#if TESTA_Q4
static void testa_q4(void) {
    printf("\n=== Questao 4: remove_lista_pos ===\n");
    int m[] = {10, 20, 30, 40};

    confere("lista NULL devolve 0", remove_lista_pos(NULL, 1), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", remove_lista_pos(vazia, 1), 0);
    libera_lista(vazia);

    Lista *li = cria_lista();
    preenche(li, m, 4);
    confere("pos = 0 devolve 0", remove_lista_pos(li, 0), 0);
    confere("pos = -2 devolve 0", remove_lista_pos(li, -2), 0);
    confere("pos = 5 (> tamanho) devolve 0", remove_lista_pos(li, 5), 0);
    confere_lista("posicoes invalidas nao alteram a lista", li, m, 4);

    confere("remove pos 2 (meio) devolve 1", remove_lista_pos(li, 2), 1);
    int e1[] = {10, 30, 40};
    confere_lista("depois: 10 30 40", li, e1, 3);

    confere("remove pos 1 (primeira) devolve 1", remove_lista_pos(li, 1), 1);
    int e2[] = {30, 40};
    confere_lista("depois: 30 40", li, e2, 2);

    confere("remove pos 2 (ultima) devolve 1", remove_lista_pos(li, 2), 1);
    int e3[] = {30};
    confere_lista("depois: 30", li, e3, 1);

    confere("remove o unico elemento devolve 1", remove_lista_pos(li, 1), 1);
    confere("lista fica vazia", lista_vazia(li), 1);
    confere("lista continua valida: insere 8", insere_lista_final(li, novo(8)), 1);
    int e4[] = {8};
    confere_lista("lista com 8", li, e4, 1);
    libera_lista(li);
}
#endif

/* ---------------- Questao 5: move_para_inicio ---------------- */
#if TESTA_Q5
static void testa_q5(void) {
    printf("\n=== Questao 5: move_para_inicio ===\n");
    int m[] = {10, 20, 30, 40};

    confere("lista NULL devolve 0", move_para_inicio(NULL, 10), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", move_para_inicio(vazia, 10), 0);
    libera_lista(vazia);

    Lista *li = cria_lista();
    preenche(li, m, 4);
    confere("matricula ausente devolve 0", move_para_inicio(li, 99), 0);
    confere_lista("ausente nao altera a lista", li, m, 4);

    confere("mat = 30 (meio) devolve 1", move_para_inicio(li, 30), 1);
    int e1[] = {30, 10, 20, 40};
    confere_lista("resultado: 30 10 20 40", li, e1, 4);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 4);
    confere("mat = 10 (ja e o primeiro) devolve 1", move_para_inicio(li, 10), 1);
    confere_lista("lista inalterada", li, m, 4);
    libera_lista(li);

    li = cria_lista();
    preenche(li, m, 4);
    confere("mat = 40 (ultimo) devolve 1", move_para_inicio(li, 40), 1);
    int e2[] = {40, 10, 20, 30};
    confere_lista("resultado: 40 10 20 30", li, e2, 4);
    libera_lista(li);

    li = cria_lista();
    int m1[] = {7};
    preenche(li, m1, 1);
    confere("um elemento: devolve 1", move_para_inicio(li, 7), 1);
    confere_lista("um elemento continua igual", li, m1, 1);
    libera_lista(li);

    /* varios acessos seguidos, como em um cache LRU */
    li = cria_lista();
    preenche(li, m, 4);
    move_para_inicio(li, 40);
    move_para_inicio(li, 20);
    move_para_inicio(li, 40);
    int e3[] = {40, 20, 10, 30};
    confere_lista("acessos 40, 20, 40 -> 40 20 10 30", li, e3, 4);
    libera_lista(li);
}
#endif

/* ---------------- Questao 6: remove_todos ---------------- */
#if TESTA_Q6
static void testa_q6(void) {
    printf("\n=== Questao 6: remove_todos ===\n");

    confere("lista NULL devolve 0", remove_todos(NULL, 7), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 0", remove_todos(vazia, 7), 0);
    libera_lista(vazia);

    int m[] = {7, 3, 7, 7, 5, 7};
    Lista *li = cria_lista();
    preenche(li, m, 6);
    confere("7 3 7 7 5 7, mat = 7 devolve 4", remove_todos(li, 7), 4);
    int e1[] = {3, 5};
    confere_lista("resultado: 3 5", li, e1, 2);
    confere("remover de novo devolve 0", remove_todos(li, 7), 0);
    libera_lista(li);

    li = cria_lista();
    int t[] = {7, 7, 7};
    preenche(li, t, 3);
    confere("todos iguais: devolve 3", remove_todos(li, 7), 3);
    confere("lista fica vazia", lista_vazia(li), 1);
    confere("lista continua valida: insere 1", insere_lista_final(li, novo(1)), 1);
    int e2[] = {1};
    confere_lista("lista com 1", li, e2, 1);
    libera_lista(li);

    li = cria_lista();
    int n[] = {1, 2, 3};
    preenche(li, n, 3);
    confere("nenhuma ocorrencia: devolve 0", remove_todos(li, 9), 0);
    confere_lista("lista inalterada", li, n, 3);
    libera_lista(li);

    li = cria_lista();
    int u[] = {5};
    preenche(li, u, 1);
    confere("um elemento igual: devolve 1", remove_todos(li, 5), 1);
    confere("lista fica vazia", lista_vazia(li), 1);
    libera_lista(li);

    li = cria_lista();
    int f[] = {1, 2, 9, 9};
    preenche(li, f, 4);
    confere("ocorrencias no final: devolve 2", remove_todos(li, 9), 2);
    int e3[] = {1, 2};
    confere_lista("resultado: 1 2", li, e3, 2);
    libera_lista(li);
}
#endif

/* ---------------- Questao 7: inverte_lista ---------------- */
#if TESTA_Q7
static void testa_q7(void) {
    printf("\n=== Questao 7: inverte_lista ===\n");

    inverte_lista(NULL);
    confere("lista NULL nao trava", 1, 1);

    Lista *vazia = cria_lista();
    inverte_lista(vazia);
    confere("lista vazia continua vazia", lista_vazia(vazia), 1);
    libera_lista(vazia);

    Lista *um = cria_lista();
    int m1[] = {9};
    preenche(um, m1, 1);
    inverte_lista(um);
    confere_lista("um elemento continua igual", um, m1, 1);
    libera_lista(um);

    Lista *li = cria_lista();
    int m5[] = {1, 2, 3, 4, 5};
    preenche(li, m5, 5);
    inverte_lista(li);
    int e5[] = {5, 4, 3, 2, 1};
    confere_lista("1..5 -> 5 4 3 2 1", li, e5, 5);
    inverte_lista(li);
    confere_lista("inverter de novo volta ao original", li, m5, 5);
    libera_lista(li);

    li = cria_lista();
    int m4[] = {1, 2, 3, 4};
    preenche(li, m4, 4);
    inverte_lista(li);
    int e4[] = {4, 3, 2, 1};
    confere_lista("1..4 (tamanho par) -> 4 3 2 1", li, e4, 4);

    /* o inicio e os dois sentidos tem de estar certos para novas operacoes */
    insere_lista_inicio(li, novo(0));
    insere_lista_final(li, novo(9));
    int e6[] = {0, 4, 3, 2, 1, 9};
    confere_lista("inserir no inicio e no final depois de inverter", li, e6, 6);
    remove_lista_final(li);
    remove_lista_inicio(li);
    confere_lista("remover inicio e final depois de inverter", li, e4, 4);
    libera_lista(li);
}
#endif

/* ---------------- Questao 8: eh_palindromo ---------------- */
#if TESTA_Q8
static int pal(const int mats[], int n) {
    Lista *li = cria_lista();
    preenche(li, mats, n);
    int r = eh_palindromo(li);
    /* a lista nao pode ser alterada */
    confere_lista("  (a lista nao foi alterada)", li, mats, n);
    libera_lista(li);
    return r;
}

static void testa_q8(void) {
    printf("\n=== Questao 8: eh_palindromo ===\n");

    confere("lista NULL devolve 0", eh_palindromo(NULL), 0);
    Lista *vazia = cria_lista();
    confere("lista vazia devolve 1", eh_palindromo(vazia), 1);
    libera_lista(vazia);

    int a[] = {5};
    confere("um elemento devolve 1", pal(a, 1), 1);
    int b[] = {1, 2, 3, 2, 1};
    confere("1 2 3 2 1 (impar) devolve 1", pal(b, 5), 1);
    int c[] = {4, 8, 8, 4};
    confere("4 8 8 4 (par) devolve 1", pal(c, 4), 1);
    int d[] = {1, 2, 2, 3};
    confere("1 2 2 3 devolve 0", pal(d, 4), 0);
    int e[] = {5, 5};
    confere("5 5 devolve 1", pal(e, 2), 1);
    int f[] = {5, 6};
    confere("5 6 devolve 0", pal(f, 2), 0);
    int g[] = {1, 2, 1};
    confere("1 2 1 devolve 1", pal(g, 3), 1);
    int h[] = {1, 2, 3};
    confere("1 2 3 devolve 0", pal(h, 3), 0);
    int i[] = {1, 2, 3, 4, 3, 2, 9};
    confere("diferenca so nas pontas (1 ... 9) devolve 0", pal(i, 7), 0);
}
#endif

int main(void) {
#if TESTA_Q1
    testa_q1();
#endif
#if TESTA_Q2
    testa_q2();
#endif
#if TESTA_Q3
    testa_q3();
#endif
#if TESTA_Q4
    testa_q4();
#endif
#if TESTA_Q5
    testa_q5();
#endif
#if TESTA_Q6
    testa_q6();
#endif
#if TESTA_Q7
    testa_q7();
#endif
#if TESTA_Q8
    testa_q8();
#endif

    printf("\n=== Resumo: %d teste(s) automatico(s), %d falha(s) ===\n",
           total, falhas);
    return falhas == 0 ? 0 : 1;
}