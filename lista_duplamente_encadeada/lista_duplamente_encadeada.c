/* ============================================================
   ListaDinEncadDupla.c
   Estrutura de Dados I - UFPB - Aula 08
   Lista dinamica duplamente encadeada

   Implementacao identica a apresentada nos slides da Aula 08.
   A definicao de struct elemento esta aqui, e nao no .h: e isso
   que torna Lista um tipo opaco. Quem usa a biblioteca enxerga
   apenas Lista* e os prototipos declarados no cabecalho.

   Qualquer funcao nova que precise percorrer a lista no a no
   tem de ser escrita NESTE arquivo, porque e aqui que os campos
   ant, dados e prox sao visiveis.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "lista_duplamente_encadeada.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca.
   Com struct aluno de 48 bytes, sizeof(Elem) = 64 bytes em uma
   plataforma de 64 bits, contra 56 na lista encadeada simples. */
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
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;   /* avanca antes de liberar */
            free(no);
        }
        free(li);                /* libera o bloco do inicio */
    }
}

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;               /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;            /* lista invalida */
    if (*li == NULL)
        return 1;            /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;    /* sem memoria: a lista esta cheia */
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if (*li != NULL)             /* lista nao vazia */
        (*li)->ant = no;         /* o antigo primeiro ganha antecessor */
    *li = no;
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    no->prox = NULL;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->ant = NULL;
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL) return 0;
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL) return 0;
    no->dados = al;
    if ((*li) == NULL) {         /* lista vazia: insere inicio */
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }
    else {
        /* O livro declara ante sem valor inicial. A inicializacao com
           NULL nao altera o comportamento e elimina o aviso
           "may be used uninitialized" do gcc com -O2. */
        Elem *ante = NULL, *atual = *li;
        while (atual != NULL &&
               atual->dados.matricula < al.matricula) {
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li) {      /* insere inicio */
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else {                 /* insere no meio ou no final */
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)   /* nao e o ultimo */
                atual->ant = no;
        }
        return 1;
    }
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    *li = no->prox;
    if (no->prox != NULL)          /* existe um seguinte */
        no->prox->ant = NULL;      /* ele passa a ser o primeiro */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no->prox != NULL)
        no = no->prox;
    if (no->ant == NULL)           /* primeiro e unico */
        *li = no->prox;
    else
        no->ant->prox = NULL;      /* penultimo obtido pelo proprio no */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL) return 0;
    if ((*li) == NULL) return 0;   /* lista vazia */
    Elem* no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)                /* chave ausente */
        return 0;
    if (no->ant == NULL)           /* remove o primeiro */
        *li = no->prox;
    else
        no->ant->prox = no->prox;
    if (no->prox != NULL)          /* nao e o ultimo */
        no->prox->ant = no->ant;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL)
        return 0;
    Elem *no = *li;
    while (no != NULL && no->dados.matricula != mat)
        no = no->prox;
    if (no == NULL)
        return 0;
    else {
        *al = no->dados;
        return 1;
    }
}
// ========================================================================================== //

/*
O custo é O(n), visto que é sempre preciso percorrer a lista duas vezes (2n), indo e voltado.
*/
void imprime_lista_inversa(Lista* li){
    if(li == NULL || *li == NULL){
        puts("(lista vazia)");
        return;
    }

    Elem *no = *li;
    while(no->prox != NULL){ 
        no = no->prox;
    }

    printf("%d", no->dados.matricula); //evita o espaço extra ao final da lista
    no = no->ant;

    while(no != NULL){
        printf("%d ", no->dados.matricula);
        no = no->ant;
    }

    printf("\n");
}

int lista_consistente(Lista* li){
    if(li == NULL) return 0;
    if(*li == NULL) return 1;
    if((*li)->ant != NULL) return 0;

    Elem *no = *li;
    while(no->prox != NULL){
        if(no->prox->ant != no) return 0;
        no = no->prox;
    }

    return 1;
}

/*
A) o código não vai remover o 33, pois vai tentar fazer NULL apontar para o novo primeiro elemento, gerando segmentation fault

B) 33 ⇄ 23 ⇄ 16
    33 ant = NULL; 33 prox = 16; 16 ant = (endereço já liberado de 23); 16 prox = NULL

    Como tamanho_lista percorre a lista do primeiro ao último elemento, ela devolve o tamanho correto (2), visto que 33 aponta corretamente para 16.
    No entanto, lista_consistente retorna 0, pois no->prox->ant != no, visto que 16 não aponta de volta da 33
*/


int remove_lista_corrigida(Lista* li, int mat){
    if(li == NULL) return 0;
    if((*li) == NULL) return 0;
    Elem* no = *li;

    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL) return 0;
    
    if(no->ant == NULL){
        *li = no->prox;
    }else{
        no->ant->prox = no->prox;
    }

    if(no->prox != NULL){
        no->prox->ant = no->ant;
    }
    free(no);
    return 1;
}

//posição 1 = primeiro elemento
//testar remoção da primeira posição, posição intermediária e última
int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || *li == NULL) return 0;
    if(pos > tamanho_lista(li) || pos <= 0) return 0;
    if(lista_consistente(li) == 0) return 0;

    Elem *no = *li;
    for(int i = 1; i < pos; i++){
        no = no->prox;
    }

    if(no->ant == NULL){
        *li = no->prox;
    }else{
        no->ant->prox = no->prox;
    }

    if(no->prox != NULL){
        no->prox->ant = no->ant;
    }

    free(no);
    return 1;
}

int move_para_inicio(Lista* li, int mat){
    if(li == NULL || *li == NULL) return 0;
    if(lista_consistente(li) == 0) return 0;

    Elem *no = *li;
    Elem *aux = *li;

    if(no->dados.matricula == mat) return 1;

    while(no->dados.matricula != mat && no->prox != NULL){
        no = no->prox;
    }
    if(no->dados.matricula != mat) return 0;

    no->ant->prox = no->prox;
    if(no->prox != NULL){
        no->prox->ant = no->ant;
    }

    no->prox = aux;
    no->ant = NULL;
    aux->ant = no;
    *li = no;
    return 1;
}


/*

{1,2,3,4,5}
mat = 3

1 ⇆ 2 ⇆ '3' ⇆ 4 ⇆ 5 
1 -> 2 -> 4 -> 5 
1 <- 2 <- 3 <- 4 <- 5

1 ⇆ 2 ⇆ 3 ⇆ '4' ⇆ 5 
4 -> 1 ⇆ 2 ⇆ 3 ⇆ 5 



3 ⇆ 1 ⇆ 2 ⇆ 4 ⇆ 5 

*/

