#include "../lista_duplamente_encadeada.h"
#include <stdio.h>
#include <stdlib.h>

struct elemento {
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;


/* --- criacao e destruicao ---------------------------------- */

Lista* cria_lista(void) {
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li) {
    if (li == NULL)
        return;
    if ((*li) != NULL) {
        Elem *aux, *no = *li;
        /* para quando o seguinte ao atual e o inicio: uma volta completa */
        while ((*li) != no->prox) {
            aux = no;
            no = no->prox;   /* avanca antes de liberar */
            free(aux);
        }
        free(no);
    }
    free(li);               /* libera o bloco do inicio */
}
// ===========================================================================================================//


int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL) return 0;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL) return 0;

    no->dados = al;

    if(*li != NULL){
        no->ant = (*li)->ant;
        no->ant->prox = no;
        no->prox = *li;
        (*li)->ant = no;
    }else{
        no->ant = no;
        no->prox = no;
    }

    *li = no;
    return 1;

}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)return 0;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)return 0;

    no->dados = al;

    if(*li != NULL){
        no->ant = (*li)->ant;
        no->prox = (*li);
        (*li)->ant->prox = no;
        (*li)->ant = no;
    }else{
        no->ant = no;
        no->prox = no;
        *li = no;
    }

    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL || *li == NULL) return 0;

    Elem *no = *li;

    if(no == no->prox){
        no->prox = NULL;
        no->ant = NULL;
        (*li) = NULL;
    }else{
        (*li)->ant->prox = no->prox;
        (*li)->prox->ant = no->ant;
        (*li) = no->prox;
    }

    free(no);

    return 1;
}

int remove_lista_final(Lista *li){
    if(li == NULL || *li == NULL) return 0;

    Elem *no = *li;

    if(no == no->ant){
        no->ant = NULL;
        no->prox = NULL;
        *li = NULL;
    }else{
        no = no->ant; //acessa o último elemento
        no->ant->prox = *li; //faz o penúltimo apontar para o primeiro
        no->prox->ant = no->ant; //faz o primeiro apontar para o penúltimo
    }

    free(no);
    return 1;
}

/*
{1}
*/

/* ============================================================
   AUXILIARES DE TESTE
   Ficam neste arquivo porque so aqui os campos ant e prox sao
   visiveis (Lista e um tipo opaco). O main.c so enxerga os
   prototipos, declarados la.

   Copiam as matriculas para um vetor v (de tamanho max) e devolvem
   quantos elementos foram percorridos. Se a lista estiver quebrada
   (um ponteiro NULL ou um ciclo que nao fecha) elas NAO travam:
   devolvem -1 ou um valor maior que max, e o teste acusa a falha.
   ============================================================ */

/* Ida: do primeiro ao ultimo, seguindo prox. */
int matriculas_ida(Lista* li, int v[], int max) {
    if (li == NULL || *li == NULL) return 0;
    int n = 0;
    Elem *no = *li;
    do {
        if (n < max) v[n] = no->dados.matricula;
        n++;
        no = no->prox;
    } while (no != NULL && no != *li && n <= max);
    if (no == NULL) return -1;          /* prox NULL: circularidade quebrada */
    return n;
}

/* Volta: do ultimo, que e (*li)->ant, ao primeiro, seguindo ant. */
int matriculas_volta(Lista* li, int v[], int max) {
    if (li == NULL || *li == NULL) return 0;
    Elem *ult = (*li)->ant;
    if (ult == NULL) return -1;
    int n = 0;
    Elem *no = ult;
    do {
        if (n < max) v[n] = no->dados.matricula;
        n++;
        no = no->ant;
    } while (no != NULL && no != ult && n <= max);
    if (no == NULL) return -1;          /* ant NULL: circularidade quebrada */
    return n;
}