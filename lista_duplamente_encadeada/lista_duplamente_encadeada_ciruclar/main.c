/* ============================================================
   main.c - Testes da lista duplamente encadeada CIRCULAR
   (Questao extra da Aula 08)

   Funcoes testadas: insere_lista_inicio, insere_lista_final,
   remove_lista_inicio, remove_lista_final, cria_lista, libera_lista.

   Como Lista e um tipo opaco, o main nao enxerga ant nem prox.
   Por isso a conferencia usa duas funcoes auxiliares escritas no
   .c (matriculas_ida e matriculas_volta): uma percorre por prox,
   a outra por ant. A lista so esta certa se as DUAS saidas
   baterem com o esperado. Ligacao esquecida = falha aqui.

   Compilar (dentro desta pasta):
     gcc -Wall -Wextra -std=c11 lista_duplamente_encadeada_circular.c main.c -o prog
   Memoria:
     valgrind --leak-check=full ./prog
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "lista_duplamente_encadeada.h"

/* Definidas em lista_duplamente_encadeada_circular.c */
int matriculas_ida(Lista* li, int v[], int max);
int matriculas_volta(Lista* li, int v[], int max);

#define MAX 64

static int total = 0, falhas = 0;

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

static struct aluno novo(int mat) {
    struct aluno al = {0};
    al.matricula = mat;
    return al;
}

/* Devolve 1 se a lista tem exatamente as matriculas esperadas, na ordem,
   lidas por prox (ida) E por ant (volta, que deve dar a ordem inversa). */
static int lista_igual(Lista *li, const int esp[], int n) {
    int ida[MAX], volta[MAX];
    int ni = matriculas_ida(li, ida, MAX);
    int nv = matriculas_volta(li, volta, MAX);
    if (ni != n || nv != n) return 0;
    for (int i = 0; i < n; i++) {
        if (ida[i] != esp[i]) return 0;
        if (volta[i] != esp[n - 1 - i]) return 0;
    }
    return 1;
}

static void mostra(const char *rotulo, const int v[], int n) {
    printf("          %s", rotulo);
    if (n < 0) { printf(" (circularidade quebrada: ponteiro NULL)\n"); return; }
    if (n > MAX) { printf(" (nao fecha o ciclo)\n"); return; }
    for (int i = 0; i < n; i++) printf(" %d", v[i]);
    printf("\n");
}

static void confere_lista(const char *descricao, Lista *li,
                          const int esp[], int n) {
    total++;
    if (lista_igual(li, esp, n)) {
        printf("  [OK]    %s\n", descricao);
        return;
    }
    falhas++;
    int ida[MAX], volta[MAX];
    int ni = matriculas_ida(li, ida, MAX);
    int nv = matriculas_volta(li, volta, MAX);
    printf("  [FALHA] %s\n", descricao);
    mostra("esperado (ida):  ", esp, n);
    mostra("obtido por prox: ", ida, ni);
    printf("          obtido por ant (do ultimo ao primeiro):");
    if (nv < 0) printf(" (circularidade quebrada)\n");
    else if (nv > MAX) printf(" (nao fecha o ciclo)\n");
    else { for (int i = 0; i < nv; i++) printf(" %d", volta[i]); printf("\n"); }
}

/* ---------------- listas invalidas e vazias ---------------- */
static void testa_invalidas_e_vazias(void) {
    printf("\n=== Lista invalida (NULL) e lista vazia ===\n");

    libera_lista(NULL);
    confere("libera_lista(NULL) nao trava", 1, 1);
    confere("insere_lista_inicio(NULL) devolve 0",
            insere_lista_inicio(NULL, novo(1)), 0);
    confere("insere_lista_final(NULL) devolve 0",
            insere_lista_final(NULL, novo(1)), 0);
    confere("remove_lista_inicio(NULL) devolve 0", remove_lista_inicio(NULL), 0);
    confere("remove_lista_final(NULL) devolve 0", remove_lista_final(NULL), 0);

    Lista *li = cria_lista();
    confere("remove_lista_inicio em lista vazia devolve 0",
            remove_lista_inicio(li), 0);
    confere("remove_lista_final em lista vazia devolve 0",
            remove_lista_final(li), 0);
    confere_lista("lista continua vazia", li, NULL, 0);
    libera_lista(li);
}

/* ---------------- insercoes ---------------- */
static void testa_insercoes(void) {
    printf("\n=== Insercoes ===\n");

    Lista *li = cria_lista();
    confere("insere_lista_inicio em lista vazia devolve 1",
            insere_lista_inicio(li, novo(1)), 1);
    int e1[] = {1};
    confere_lista("um elemento, inserido no inicio: aponta para si mesmo "
                  "nos dois sentidos", li, e1, 1);
    libera_lista(li);

    li = cria_lista();
    confere("insere_lista_final em lista vazia devolve 1",
            insere_lista_final(li, novo(1)), 1);
    confere_lista("um elemento, inserido no final: aponta para si mesmo "
                  "nos dois sentidos", li, e1, 1);
    libera_lista(li);

    li = cria_lista();
    insere_lista_inicio(li, novo(3));
    insere_lista_inicio(li, novo(2));
    insere_lista_inicio(li, novo(1));
    int e2[] = {1, 2, 3};
    confere_lista("tres no inicio (3, 2, 1) -> 1 2 3", li, e2, 3);
    libera_lista(li);

    li = cria_lista();
    insere_lista_final(li, novo(1));
    insere_lista_final(li, novo(2));
    insere_lista_final(li, novo(3));
    confere_lista("tres no final (1, 2, 3) -> 1 2 3", li, e2, 3);
    libera_lista(li);

    li = cria_lista();
    insere_lista_final(li, novo(2));
    insere_lista_inicio(li, novo(1));
    insere_lista_final(li, novo(3));
    insere_lista_inicio(li, novo(0));
    int e3[] = {0, 1, 2, 3};
    confere_lista("misto: final 2, inicio 1, final 3, inicio 0 -> 0 1 2 3",
                  li, e3, 4);
    libera_lista(li);
}

/* ---------------- remocoes ---------------- */
static void testa_remove_inicio(void) {
    printf("\n=== remove_lista_inicio ===\n");
    Lista *li = cria_lista();
    int m[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) insere_lista_final(li, novo(m[i]));

    confere("remove o 1 devolve 1", remove_lista_inicio(li), 1);
    int e1[] = {2, 3};
    confere_lista("resultado: 2 3", li, e1, 2);

    confere("remove o 2 devolve 1", remove_lista_inicio(li), 1);
    int e2[] = {3};
    confere_lista("resultado: 3 (aponta para si mesmo)", li, e2, 1);

    confere("remove o ultimo elemento devolve 1", remove_lista_inicio(li), 1);
    confere_lista("lista fica vazia", li, NULL, 0);
    confere("remover de lista vazia devolve 0", remove_lista_inicio(li), 0);

    confere("lista continua valida: insere 9", insere_lista_inicio(li, novo(9)), 1);
    int e3[] = {9};
    confere_lista("lista com 9", li, e3, 1);
    libera_lista(li);
}

static void testa_remove_final(void) {
    printf("\n=== remove_lista_final ===\n");
    Lista *li = cria_lista();
    int m[] = {1, 2, 3};
    for (int i = 0; i < 3; i++) insere_lista_final(li, novo(m[i]));

    confere("remove o 3 devolve 1", remove_lista_final(li), 1);
    int e1[] = {1, 2};
    confere_lista("resultado: 1 2", li, e1, 2);

    confere("remove o 2 devolve 1", remove_lista_final(li), 1);
    int e2[] = {1};
    confere_lista("resultado: 1 (aponta para si mesmo)", li, e2, 1);

    confere("remove o ultimo elemento devolve 1", remove_lista_final(li), 1);
    confere_lista("lista fica vazia", li, NULL, 0);
    confere("remover de lista vazia devolve 0", remove_lista_final(li), 0);

    confere("lista continua valida: insere 9", insere_lista_final(li, novo(9)), 1);
    int e3[] = {9};
    confere_lista("lista com 9", li, e3, 1);
    libera_lista(li);
}

static void testa_alternando(void) {
    printf("\n=== Remocoes alternadas nas duas pontas ===\n");
    Lista *li = cria_lista();
    for (int i = 1; i <= 5; i++) insere_lista_final(li, novo(i));

    remove_lista_final(li);
    int e1[] = {1, 2, 3, 4};
    confere_lista("1..5, remove final -> 1 2 3 4", li, e1, 4);
    remove_lista_inicio(li);
    int e2[] = {2, 3, 4};
    confere_lista("remove inicio -> 2 3 4", li, e2, 3);
    remove_lista_final(li);
    int e3[] = {2, 3};
    confere_lista("remove final -> 2 3", li, e3, 2);
    remove_lista_inicio(li);
    int e4[] = {3};
    confere_lista("remove inicio -> 3", li, e4, 1);
    libera_lista(li);
}

/* ---------------- teste com modelo (sequencia pseudoaleatoria) ----------------
   Aplica as mesmas operacoes a lista e a um vetor simples (o "modelo") e
   compara os dois depois de cada passo. Pega erros que aparecem so em
   certas combinacoes de operacoes. A sequencia e fixa (sempre igual). */
static unsigned int semente = 2463534242u;
static unsigned int proximo(void) {
    semente ^= semente << 13;
    semente ^= semente >> 17;
    semente ^= semente << 5;
    return semente;
}

static void testa_modelo(void) {
    printf("\n=== Teste com modelo: 500 operacoes aleatorias ===\n");
    Lista *li = cria_lista();
    int modelo[MAX], nm = 0, prox_mat = 1, erros = 0;

    for (int passo = 1; passo <= 500; passo++) {
        int op = (int)(proximo() % 4);
        if (op < 2 && nm >= 40) op += 2;        /* limita o tamanho */
        int esperado_ret = 1, ret;

        if (op == 0) {                          /* insere no inicio */
            ret = insere_lista_inicio(li, novo(prox_mat));
            for (int i = nm; i > 0; i--) modelo[i] = modelo[i - 1];
            modelo[0] = prox_mat++; nm++;
        } else if (op == 1) {                   /* insere no final */
            ret = insere_lista_final(li, novo(prox_mat));
            modelo[nm++] = prox_mat++;
        } else if (op == 2) {                   /* remove do inicio */
            ret = remove_lista_inicio(li);
            if (nm == 0) esperado_ret = 0;
            else { for (int i = 1; i < nm; i++) modelo[i - 1] = modelo[i]; nm--; }
        } else {                                /* remove do final */
            ret = remove_lista_final(li);
            if (nm == 0) esperado_ret = 0;
            else nm--;
        }

        if (ret != esperado_ret || !lista_igual(li, modelo, nm)) {
            erros++;
            printf("  [FALHA] passo %d (operacao %d, tamanho esperado %d)\n",
                   passo, op, nm);
            break;      /* depois do primeiro erro o resto nao faz sentido */
        }
    }
    confere("500 operacoes iguais ao modelo (erros)", erros, 0);
    libera_lista(li);
}

int main(void) {
    testa_invalidas_e_vazias();
    testa_insercoes();
    testa_remove_inicio();
    testa_remove_final();
    testa_alternando();
    testa_modelo();

    printf("\n=== Resumo: %d teste(s) automatico(s), %d falha(s) ===\n",
           total, falhas);
    return falhas == 0 ? 0 : 1;
}