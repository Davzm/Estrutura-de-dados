#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaTarefas.h"

/* Nó da lista encadeada */
struct elemento {
    struct tarefa dados;     
    struct elemento *prox;
};
typedef struct elemento Elem;

/* --- Implementação das Funções Base --- */

ListaTarefas* cria_lista(void) {
    ListaTarefas* li = (ListaTarefas*) malloc(sizeof(ListaTarefas));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(ListaTarefas* li) {
    if (li != NULL) {
        Elem* no;
        while ((*li) != NULL) {
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int tamanho_lista(ListaTarefas* li) {
    if (li == NULL) return -1;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL) {
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(ListaTarefas* li) {
    if (li == NULL){ 
        return -1;
    }
    return 0;
}

int lista_vazia(ListaTarefas* li) {
    if (li == NULL){ 
        return -1;
    }
    if (*li == NULL){ 
        return 1;
    }
    return 0;
}

int insere_tarefa_inicio(ListaTarefas* li, struct tarefa t) {
    if (li == NULL){ 
        return 0;
    }
    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL){ 
        return 0;
    }    
    no->dados = t;
    no->prox = (*li);
    *li = no;
    return 1;
}

int insere_tarefa_final(ListaTarefas* li, struct tarefa t) {
    if (li == NULL){ 
        return 0;
    }

    Elem* no = (Elem*) malloc(sizeof(Elem));
    
    if (no == NULL){ 
        return 0;
    }
    no->dados = t;
    no->prox = NULL;

    if ((*li) == NULL) {
        *li = no;
    } else {
        Elem* aux = *li;
        while (aux->prox != NULL)
            aux = aux->prox;
        aux->prox = no;
    }
    return 1;
}

int insere_tarefa_ordenada(ListaTarefas* li, struct tarefa t) {
    if (li == NULL){ 
        return 0;
    
    }
    Elem* no = (Elem*) malloc(sizeof(Elem));
    
    if (no == NULL){ 
        return 0;
    }
    
    no->dados = t;
    
    if ((*li) == NULL) {
        no->prox = NULL;
        *li = no;
        return 1;
    } else {
        Elem *ant = NULL, *atual = *li;
        /* Ordena por prioridade: menor prioridade (1 = mais urgente) vem antes */
        while (atual != NULL && atual->dados.prioridade <= t.prioridade) {
            ant = atual;
            atual = atual->prox;
        }
        if (atual == *li) {
            no->prox = (*li);
            *li = no;
        } else {
            no->prox = atual;
            ant->prox = no;
        }
        return 1;
    }
}

int remove_tarefa_inicio(ListaTarefas* li) {
    if (li == NULL || (*li) == NULL) return 0;
    Elem *no = *li;
    *li = no->prox;
    free(no);
    return 1;
}

int remove_tarefa_final(ListaTarefas* li) {
    if (li == NULL || (*li) == NULL){
        return 0;
    }

    Elem *ant = NULL, *no = *li;
    
    while (no->prox != NULL) {
        ant = no;
        no = no->prox;
    }

    if (no == (*li)){
        *li = no->prox;
    }else{
        ant->prox = no->prox;
    }
    free(no);
    return 1;
}

int remove_tarefa(ListaTarefas* li, int codigo) {
    if (li == NULL || (*li) == NULL){ 
        return 0;
    }

    Elem *ant = NULL, *no = *li;
    
    while (no != NULL && no->dados.codigo != codigo) {
        ant = no;
        no = no->prox;
    }
    
    if (no == NULL){ 
        return 0;
    }
    
    if (no == *li){
        *li = no->prox;
    }else{
        ant->prox = no->prox;
    }

    free(no);
    return 1;
}

int busca_tarefa_pos(ListaTarefas* li, int pos, struct tarefa *t) {
    if (li == NULL || pos <= 0){ 
        return 0;
    }
        
    Elem *no = *li;
    int i = 1;
    while (no != NULL && i < pos) {
        no = no->prox;
        i++;
    }
    if (no == NULL) return 0;
    *t = no->dados;
    return 1;
}

int busca_tarefa_cod(ListaTarefas* li, int codigo, struct tarefa *t) {
    if (li == NULL){ 
        return 0;
    }    

    Elem *no = *li;
    while (no != NULL && no->dados.codigo != codigo){
        no = no->prox;
    }

    if (no == NULL){ 
        return 0;
    }

    *t = no->dados;
    return 1;
}

/* ============================================================
   Abaixo você implementará as 8 funções solicitadas
   ============================================================ */

int conta_tarefas_prioridade(ListaTarefas* li, int prioridade) {
    if(li == NULL){
        return -1;
    }

    Elem *no = *li;
    int contador = 0;
    while(no != NULL){
        if(no-> dados.prioridade == prioridade){
            contador++;
        }
        no = no -> prox;
    }

    return contador;
}

int tarefa_mais_urgente(ListaTarefas* li, struct tarefa *t) {
    if(li == NULL || *li == NULL || t == NULL){
        return 0;
    }

    Elem *no = *li;
    Elem *mais_urgente = *li;

    while(no != NULL){
        if(no->dados.prioridade == 0){
            mais_urgente = no;
            break;
        }
        if(no -> dados.prioridade < mais_urgente->dados.prioridade){
            mais_urgente = no; 
        }
        no = no->prox;
    }


    *t = mais_urgente->dados;
    return 1;
}

int busca_tarefa_desc(ListaTarefas* li, char *texto, struct tarefa *t) {
    if(li == NULL || *li == NULL || t == NULL){
        return 0;
    }

    Elem *no = *li;
    
    
    while(no != NULL){
        if(strstr(no->dados.descricao, texto)){
            *t = no->dados;
            return 1;
        }
        no = no->prox;
    }

    return 0;
}

int insere_tarefa_final_prioridade(ListaTarefas* li, struct tarefa t) {
    if(li == NULL){
        return 0;
    }

    Elem* novo = (Elem*) malloc(sizeof(Elem));
    if(novo == NULL){
        return 0;
    }

    novo->dados = t;

    //↓ caso a lista seja vazia ↓
    if (*li == NULL) {
        novo->prox = NULL;
        *li = novo;
        return 1; 
    }    

    Elem *aux = *li;
    Elem *ultimo_prioridade = NULL;
    Elem *ultimo_no = NULL;


    while(aux != NULL){
        if (aux->dados.prioridade == t.prioridade){
            ultimo_prioridade = aux; // Guarda o último nó com a mesma prioridade 
        }
        if (aux->prox == NULL){
            ultimo_no = aux; //Guarda o último nó da lista
        }
        aux = aux->prox;
    }

    if (ultimo_prioridade != NULL) {
        novo->prox = ultimo_prioridade->prox;
        ultimo_prioridade->prox = novo;
    } else {
        /* Se não encontrou nenhuma tarefa com essa prioridade, insere no final */
        ultimo_no->prox = novo;
        novo->prox = NULL;
    }

    return 1;
}

int remove_tarefas_prioridade(ListaTarefas* li, int prioridade) {
    if(li == NULL){
        return -1;
    }

    int contador = 0;
    Elem *ant = NULL;
    Elem *no = *li;

    while(no != NULL){
        if(prioridade == no->dados.prioridade){
            Elem *aux = no;

            if(no == *li){
                *li = no->prox;
                no = *li;
            }else{
                ant->prox = no->prox;
                no = no->prox;
            }         
            free(aux);
            contador++;          

            ant->prox = no->prox;
            free(no);
            no = ant;
            contador++;
        }else{
            ant = no;
            no = no->prox;
        }
        
    }

    return contador;
}
/*

A,B,C,D
a -> b -> c -> d -> NULL
  <-   
D,C,B,A
d -> c -> b -> a -> NULL
*/

int inverte_lista(ListaTarefas* li) {
    if(li == NULL){
        return 0;
    }

    Elem *atual = *li;
    Elem *anterior = NULL;
    Elem *proximo = NULL;

    while(atual != NULL){
        proximo = atual->prox;
        atual->prox = anterior;
        anterior = atual;
        atual = proximo;
    }
    *li = anterior;

    return 1;
}

int remove_tarefa_pos(ListaTarefas* li, int pos) {
    if(li == NULL || *li == NULL || pos <= 0){
        return 0;
    }

    Elem *no = *li;
    Elem *anterior = NULL;
    int posicao = 1;

    while(no != NULL && posicao != pos){
        anterior = no;
        no = no->prox;
        posicao++;
    }

    if(no == NULL){
        return 0;
    }

    if(no == *li){
        *li = no->prox;
    }else{
        anterior->prox = no->prox;
    }

    free(no);
    return 1;
}

int mescla_tarefas(ListaTarefas* dst, ListaTarefas* src) {
    if(dst == NULL || src == NULL){
        return -1;
    }

    if (*src == NULL) {
        return 0; // Se src estiver vazia, 0 tarefas foram transferidas
    }

    Elem *no_dst = *dst;
    Elem *no_src = *src;

    int contador = 0;
    
    

    if(*dst == NULL){   //se dst for vazia, recebe src logo de cara
        *dst = *src;
    }else{
        while(no_dst->prox != NULL){ 
            no_dst = no_dst->prox;
        }
        no_dst->prox = *src;
    }//econtra a última posição de dst e faz apontar para o início de src

    while (no_src != NULL) {
        contador++;
        no_src = no_src->prox;
    }//contando o número de elementos transferidos

    *src = NULL;

    return contador;
}

