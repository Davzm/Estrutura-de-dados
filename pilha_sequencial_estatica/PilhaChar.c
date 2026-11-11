#include "PilhaChar.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct pilha {
    int qtd;
    int capacidade;
    char *dados;
};


Pilha* cria_Pilha(int capacidade){
    Pilha *pi;
    if (capacidade <= 0)
        return NULL;
    pi = (Pilha*) malloc(sizeof(struct pilha));          /* 1a alocacao */

    if (pi == NULL)
        return NULL;
    pi->dados = (char*) malloc(capacidade * sizeof(char));

    if (pi->dados == NULL) {                             /* 2a alocacao falhou */
        free(pi);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    pi->capacidade = capacidade;
    pi->qtd = 0;
    return pi;
}

void libera_Pilha(Pilha* pi) {
    if (pi == NULL)
        return;
    free(pi->dados);    /* primeiro o vetor: pi ainda e valido aqui */
    free(pi);           /* depois a estrutura que guardava o vetor */
}

/* ------------------------------------------------------------
   Informacoes de estado
   ------------------------------------------------------------ */

int tamanho_Pilha(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return pi->qtd;
}

int Pilha_cheia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == pi->capacidade);  /* no livro: qtd == MAX */
}

int Pilha_vazia(Pilha* pi) {
    if (pi == NULL)
        return -1;
    return (pi->qtd == 0);
}

/* ------------------------------------------------------------
   Operacoes da pilha (sempre no topo)
   ------------------------------------------------------------ */

int insere_Pilha(Pilha* pi, char c) {
    if (pi == NULL)
        return 0;
    if (Pilha_cheia(pi))                  /* teste de estouro */
        return 0;
    pi->dados[pi->qtd] = c;              /* qtd e a primeira posicao livre */
    pi->qtd++;                            /* o novo elemento passa a ser o topo */
    return 1;
}

int remove_Pilha(Pilha* pi) {
    if (pi == NULL || Pilha_vazia(pi))
        return 0;
    pi->qtd--;          /* o topo desce uma posicao; nada e apagado */
    return 1;
}

int consulta_topo_Pilha(Pilha* pi, char *c) {
    if (pi == NULL || c == NULL || Pilha_vazia(pi))
        return 0;
    *c = pi->dados[pi->qtd - 1];         /* topo: ultima posicao ocupada */
    return 1;
}


//=========================================================================================//

int verifica_delimitadores(const char *expr){
    if(expr == NULL)return 0;
    int capacidade = strlen(expr);
    Pilha *pi;
    pi = cria_Pilha(capacidade);
    if(pi == NULL) return 0;
    
    char x;
    int i = 0, qtd_elem = 0;
    x = expr[i];
    int caract_delimita = 0;
    char topo_p;

    for(int i = 0; expr[i] != '\0'; i++){
        x = expr[i];

        if(x == '(' || x == '[' || x == '{'){
            insere_Pilha(pi, x);
        }

        else if (x == ')' || x == ']' || x == '}'){
            char topo_p;
            
            // Se a pilha estiver vazia ao tentar fechar, a expressao e invalida
            if(!consulta_topo_Pilha(pi, &topo_p)){
                libera_Pilha(pi);
                return 0;
            }

            if((x == ')' && topo_p == '(') ||
                (x == ']' && topo_p == '[') ||
                (x == '}' && topo_p == '{')){
                remove_Pilha(pi);
            }else{
                libera_Pilha(pi);
                return 0;
            }
        }
    }

    int retorno = Pilha_vazia(pi);
    libera_Pilha(pi);
    return retorno;
    
}


/*
        {[(      ||     )]}
        {[(


*/