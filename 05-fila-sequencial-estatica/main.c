/* Programa de teste da biblioteca: reproduz os traces da Aula 09
   (fila com capacidade 5, incluindo a volta circular de final). */
#include <stdio.h>
#include <string.h>
#include "FilaEstatica.h"
#include <stdbool.h>

static struct aluno mk(int matricula, const char *nome) {
    struct aluno al;
    al.matricula = matricula;
    strncpy(al.nome, nome, sizeof(al.nome) - 1);
    al.nome[sizeof(al.nome) - 1] = '\0';
    al.n1 = al.n2 = al.n3 = 0.0f;
    return al;
}

/* Imprime a fila do inicio para o final usando apenas a interface:
   consulta, remove e reinsere cada elemento (qtd voltas completas).
   A fila termina no mesmo estado logico em que comecou. */
static void imprime(const char *rotulo, Fila *fi) {
    int i, n = tamanho_Fila(fi);
    struct aluno al;
    printf("%-24s qtd=%d:", rotulo, n);
    for (i = 0; i < n; i++) {
        consulta_Fila(fi, &al);
        remove_Fila(fi);
        insere_Fila(fi, al);
        printf(" %d", al.matricula);
    }
    printf("\n");
}

//{1,2,3,4,5,6,7}
//{1,2,4,5,6,7}
//{1,2,4,5,7}
//{1,4,5,7}
//{1,4,5}
//{1,4}
//{4}

//{7}

int josefo(int n, int k){
    if(n < 1 || k < 1) return -1;
    Fila *fi; 
    fi = cria_Fila(n);
    if(fi == NULL) return -1; 
    struct aluno al;
    for(int i = 1; i <= n; i++){
        al.matricula = i;
        insere_Fila(fi, al);
    }

    while(tamanho_Fila(fi) > 1){
        for(int i = 0; i < k-1; i++){
            consulta_Fila(fi, &al);
            remove_Fila(fi);
            insere_Fila(fi, al);
        }
        consulta_Fila(fi, &al);
        printf("Aluno de matricula %d removido\n", al.matricula);
        remove_Fila(fi);

    }
    consulta_Fila(fi, &al);
    int matricula = al.matricula;
    remove_Fila(fi);
    libera_Fila(fi);
    return matricula;
}

int main(void) {
    Fila *fi;
    struct aluno al;

    printf("cria_Fila(0) == NULL: %d\n", cria_Fila(0) == NULL);

    fi = cria_Fila(5);
    if (fi == NULL) {
        printf("falha na alocacao\n");
        return 1;
    }
    printf("vazia=%d cheia=%d tamanho=%d\n", Fila_vazia(fi), Fila_cheia(fi), tamanho_Fila(fi));

    insere_Fila(fi, mk(10, "Ana"));
    insere_Fila(fi, mk(20, "Bruno"));
    insere_Fila(fi, mk(30, "Carla"));
    insere_Fila(fi, mk(40, "Diego"));
    imprime("apos 4 insercoes", fi);

    consulta_Fila(fi, &al);
    printf("consulta -> %d (%s)\n", al.matricula, al.nome);

    remove_Fila(fi);
    remove_Fila(fi);
    imprime("apos 2 remocoes", fi);

    insere_Fila(fi, mk(50, "Elisa"));
    insere_Fila(fi, mk(60, "Fabio"));     /* final volta para a posicao 0 */
    insere_Fila(fi, mk(70, "Gabriela"));
    imprime("volta circular", fi);
    printf("vazia=%d cheia=%d tamanho=%d\n", Fila_vazia(fi), Fila_cheia(fi), tamanho_Fila(fi));
    printf("insere em fila cheia = %d\n", insere_Fila(fi, mk(80, "Hugo")));

    while (!Fila_vazia(fi)) {
        consulta_Fila(fi, &al);
        printf("atende %d\n", al.matricula);
        remove_Fila(fi);
    }
    printf("remove em fila vazia = %d\n", remove_Fila(fi));
    printf("consulta em fila vazia = %d\n", consulta_Fila(fi, &al));

    libera_Fila(fi);

    fi = cria_Fila(5);
    printf("Teste de fura fila com fila vazia: %d (esperado 1)\n", fura_Fila(fi, mk(40, "Sophia")));
    imprime("fura fila vazia || mat = 40", fi);

    libera_Fila(fi);

    fi = cria_Fila(3);
    insere_Fila(fi, mk(20, "Matheus"));
    printf("Teste de fura fila como inicio = 0: %d (esperado 1)\n", fura_Fila(fi, mk(30, "Rafael")));

    imprime("fura fila inicio = 0 || mat = 30", fi);
    insere_Fila(fi, mk(50, "Patricia"));

    printf("Teste fura fila com fila cheia: %d (esperado 0) \n", fura_Fila(fi, mk(60, "Otavio")));
    imprime("fura fila cheia || mat = 60", fi);
    libera_Fila(fi);

    //Problema de Josefo
    printf("Josefo(7,3): Sobrevivente é o aluno %d\n", josefo(7,3));
    printf("Josefo(5,2): Sobrevivente é o aluno %d\n", josefo(5,2));
    printf("Josefo(1,4): Sobrevivente é o aluno %d\n", josefo(1,4));
    printf("Josefo(6,1): Sobrevivente é o aluno %d\n", josefo(6,1));
    printf("Josefo(0,-1): Sobrevivente é o aluno %d (esperado -1)\n", josefo(0,-1));
    return 0;
}