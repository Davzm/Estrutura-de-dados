/* ============================================================
   ListaDinEncadCirc.c
   Estrutura de Dados I - UFPB - Aula 07
   Lista dinamica encadeada circular

   Implementacao identica a apresentada nos slides da Aula 07.
   A definicao de struct elemento esta aqui, e nao no .h: e isso
   que torna Lista um tipo opaco. Quem usa a biblioteca enxerga
   apenas Lista* e os prototipos declarados no cabecalho.

   Qualquer funcao nova que precise percorrer a lista no a no
   tem de ser escrita NESTE arquivo, porque e aqui que os campos
   dados e prox sao visiveis.
   ============================================================ */

#include <stdio.h>
#include <stdlib.h>
#include "listaCircular.h"

/* Definicao do tipo lista: oculta de quem usa a biblioteca. */
struct elemento {
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

/* --- informacoes de estado --------------------------------- */

int tamanho_lista(Lista* li) {
    if (li == NULL || (*li) == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    do {                    /* do-while: o primeiro elemento tem de ser contado */
        cont++;
        no = no->prox;
    } while (no != (*li));
    return cont;
}

int lista_cheia(Lista* li) {
    (void) li;              /* parametro mantido por simetria com as demais */
    return 0;
}

int lista_vazia(Lista* li) {
    if (li == NULL)
        return 1;           /* lista invalida */
    if (*li == NULL)
        return 1;           /* nenhum elemento alocado */
    return 0;
}

/* --- insercao ---------------------------------------------- */

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;           /* sem memoria: a lista esta cheia */
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;
        *li = no;           /* unica linha que difere da insercao no final */
    }
    return 1;
}

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia: o no aponta para si mesmo */
        *li = no;
        no->prox = no;
    } else {
        Elem *aux = *li;
        while (aux->prox != (*li)) {   /* procura o ultimo */
            aux = aux->prox;
        }
        aux->prox = no;
        no->prox = *li;     /* o inicio nao muda */
    }
    return 1;
}

int insere_lista_ordenada(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;
    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;
    no->dados = al;
    if ((*li) == NULL) {    /* lista vazia */
        *li = no;
        no->prox = no;
        return 1;
    }
    if ((*li)->dados.matricula > al.matricula) {   /* insercao no inicio */
        Elem *atual = *li;
        while (atual->prox != (*li))               /* procura o ultimo */
            atual = atual->prox;
        no->prox = *li;
        atual->prox = no;
        *li = no;
        return 1;
    }
    /* insercao no meio ou no final: ant acompanha atual uma posicao atras */
    Elem *ant = *li, *atual = (*li)->prox;
    while (atual != (*li) && atual->dados.matricula < al.matricula) {
        ant = atual;
        atual = atual->prox;
    }
    ant->prox = no;
    no->prox = atual;
    return 1;
}

/* --- remocao ----------------------------------------------- */

int remove_lista_inicio(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *atual = *li;
    while (atual->prox != (*li))  /* procura o ultimo */
        atual = atual->prox;
    Elem *no = *li;
    atual->prox = no->prox;       /* o ultimo passa a apontar para o segundo */
    *li = no->prox;               /* o segundo passa a ser o inicio */
    free(no);
    return 1;
}

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    if ((*li) == (*li)->prox) {   /* elemento unico: a lista fica vazia */
        free(*li);
        *li = NULL;
        return 1;
    }
    Elem *ant = NULL, *no = *li;
    while (no->prox != (*li)) {   /* procura o ultimo, guardando o anterior */
        ant = no;
        no = no->prox;
    }
    ant->prox = no->prox;         /* o penultimo passa a apontar para o inicio */
    free(no);
    return 1;
}

int remove_lista(Lista* li, int mat) {
    if (li == NULL)
        return 0;
    if ((*li) == NULL)
        return 0;           /* lista vazia */
    Elem *no = *li;
    if (no->dados.matricula == mat) {      /* remocao do inicio */
        if (no == no->prox) {              /* a lista fica vazia */
            free(no);
            *li = NULL;
            return 1;
        } else {
            Elem *ult = *li;
            while (ult->prox != (*li))     /* procura o ultimo */
                ult = ult->prox;
            ult->prox = (*li)->prox;
            *li = (*li)->prox;
            free(no);
            return 1;
        }
    }
    Elem *ant = no;
    no = no->prox;
    /* para ao encontrar a matricula ou ao completar uma volta */
    while (no != (*li) && no->dados.matricula != mat) {
        ant = no;
        no = no->prox;
    }
    if (no == (*li))
        return 0;           /* chave ausente */
    ant->prox = no->prox;
    free(no);
    return 1;
}

/* --- busca ------------------------------------------------- */

int busca_lista_pos(Lista* li, int pos, struct aluno *al) {
    if (li == NULL || (*li) == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    /* para no ultimo elemento ou ao alcancar a posicao desejada */
    while (no->prox != (*li) && i < pos) {
        no = no->prox;
        i++;
    }
    if (i != pos)
        return 0;           /* posicao inexistente */
    else {
        *al = no->dados;
        return 1;
    }
}

int busca_lista_mat(Lista* li, int mat, struct aluno *al) {
    if (li == NULL || (*li) == NULL)
        return 0;
    Elem *no = *li;
    /* para no ultimo elemento ou ao encontrar a matricula */
    while (no->prox != (*li) && no->dados.matricula != mat)
        no = no->prox;
    if (no->dados.matricula != mat)
        return 0;           /* chave ausente */
    else {
        *al = no->dados;
        return 1;
    }
}   

    /*=============================================================================*/

void imprime_lista(Lista* li){
    if(li == NULL || *li == NULL){
        return;
    }    
    Elem *no = *li;

    do{
        printf("%d ",no->dados.matricula);
        no = no->prox;
    }while(no != *li);
    printf("\n");
}

int maior_matricula(Lista* li, int *mat){
    if(li == NULL || *li == NULL){
        return 0;
    }

    Elem *no = *li;
    int maior = no->dados.matricula;
    do{
        if(maior < no->dados.matricula){
            maior = no->dados.matricula;
        }
        no = no->prox;
    }while(no != *li);
    
    *mat = maior;
    return 1;
}

/*
Não testa se a lista é válida. Se li == NULL, vai gerar segmentation fault

o laço while vai entrar em loop infinito, pois no nunca vai ser NULL, visto que
o último no aponta para o primeiro. (considerando uma lista não vazia)
*/
int conta_aprovados(Lista* li){
    if(li == NULL || *li == NULL) return 0;

    int cont = 0;
    Elem *no = *li;
    
    do{
        float media = (no->dados.n1 + no->dados.n2 + no->dados.n3) / 3;
        if(media >= 7.0){
            cont++;
        }
        no = no->prox;
    }while(no != *li);
    
    return cont;
}

int busca_ciclica(Lista* li, int k, struct aluno *al){
    if(li == NULL || *li == NULL || k <= 0) return 0;

    Elem *no = *li;
    int condicao_parada = (k-1) % tamanho_lista(li);

    for(int i = 0; i < condicao_parada; i++){
        no = no->prox;
    }

    *al = no->dados;

    return 1;
}

int remove_lista_pos(Lista* li, int pos){
    if(li == NULL || *li == NULL || pos > tamanho_lista(li) || pos <= 0){
        return 0;
    }

    if(pos == 1){
        return remove_lista_inicio(li);
    }

    Elem *no = *li;
    Elem *ant = NULL;

    for(int i = 1; i < pos; i++){
        ant = no;
        no = no->prox;
    }

    ant->prox = no->prox;
    free(no);
    return 1;
}

/*
1) O custo geral é O(k mod n), no pior caso, n-1 avanços, ou seja, O(n). Como a função pode parar antes de chegar no último elemento, um k pequeno vai gerar 
menos interações necessárias

2) Seria necessário achar o último no e o no na posição k, fazer o último apontar para o antigo primeiro, fazer o no da posição k apontar para NULL e fazer 
*li apontar para k+1. O custo seria sempre O(n), visto que sempre é necessário percorrer a lista inteira.
*/

int rotaciona_lista(Lista* li, int k){
    if(li == NULL || *li == NULL || k < 0) return 0;

    Elem *no = *li;
    int condicao_parada = k % tamanho_lista(li);

    for(int i = 0; i < condicao_parada; i++){
        no = no->prox;
    }

    *li = no; 

    return 1;
}
/*
O custo passaria a ser O(1), pois não seria necessário percorrer a lista até chegar no último elemento, e só então religar os ponteiros. 
*/

int concatena_listas(Lista* li1, Lista* li2){
    if(li1 == NULL || li2 == NULL || li1 == li2) return 0;
    if(*li2 == NULL)return 1;

    if(*li1 == NULL){
        *li1 = *li2;
        *li2 = NULL;
        return 1;
    }

    Elem *no1 = *li1;
    

    while(no1->prox != *li1){
        no1 = no1->prox;
    }
    
    Elem *no2 = *li2;
    
    while(no2->prox != *li2){
        no2 = no2->prox;
    }

    no1->prox = *li2;
    no2->prox = *li1;
    *li2 = NULL;
    return 1;
}

int josephus(Lista* li, int k, int *sobrevivente){
    if(li == NULL || *li == NULL || k < 1) return 0;

    /*if(tamanho_lista(li) == 1){
        Elem *no = *li;
        *sobrevivente = no->dados.matricula;
        free(no);
        *li = NULL;
        return 1;
    }
    */
    
    Elem *ant = *li;
    while(ant->prox != *li) ant = ant->prox;


    while(ant->prox != ant){
        Elem *no = ant->prox;

        for(int i = 1; i < k; i++){
            ant = no;
            no = no->prox;
        }
        
        ant->prox = no->prox;
        free(no);
    }

    *sobrevivente = ant->dados.matricula;
    free(ant);
    *li = NULL;

    return 1;
}



/*

{1,2,3,4,5} k = 10

pos = 3
{1,2,4,5}
2 -> 4

{1,2,3,4,5,6,7}
k = 3

{1,2,4,5,6,7}
{1,2,4,5,7}
{1,4,5,7}
{1,4,5}
{1,4}
{1}
*/



