#include <stdio.h>
#include <stdlib.h>
#include "PilhaDupla.h"

struct pilha_dupla{
    int topo1;
    int topo2;
    int capacidade;
    struct aluno *dados;
};

PilhaDupla* cria_PilhaDupla(int capacidade){
    PilhaDupla *pd;
    if (capacidade <= 0)
        return NULL;

    pd = (PilhaDupla*) malloc(sizeof(struct pilha_dupla));          /* 1a alocacao */
    if (pd == NULL)
        return NULL;
    
    pd->dados = (struct aluno*) malloc(capacidade * sizeof(struct aluno));
    if (pd->dados == NULL) {                             /* 2a alocacao falhou */
        free(pd);       /* sem este free, a struct ficaria perdida */
        return NULL;
    }
    pd->capacidade = capacidade;
    pd->topo1 = 0;
    pd->topo2 = capacidade -1;
    return pd;
}

void libera_PilhaDupla(PilhaDupla* pd){
    if (pd == NULL)
        return;
    free(pd->dados);   
    free(pd); 
}

int tamanho_PilhaDupla(PilhaDupla* pd, int p){
    if (pd == NULL)
        return -1;

    if(p == 1){
        return pd->topo1;
    }else if(p == 2){
        return pd->capacidade - 1 - pd->topo2;
    }else{
        return -1;
    }
    
}
int  PilhaDupla_cheia(PilhaDupla* pd){
    if (pd == NULL)
        return -1;

    return (pd->topo1 > pd->topo2);
}

int PilhaDupla_vazia(PilhaDupla* pd, int p ){
    if (pd == NULL)
        return -1;
    if(p == 1){
        return (pd->topo1 == 0);
    }else if(p == 2){
        return (pd->topo2 == pd->capacidade - 1);
    }else{
        return -1;
    }
}

int insere_PilhaDupla(PilhaDupla* pd, int p, struct aluno al){
    if (pd == NULL)
        return 0;
    if (PilhaDupla_cheia(pd))                
        return 0;
    
    if(p == 1){
        pd->dados[pd->topo1] = al;
        pd->topo1++;
    }else if(p == 2){
        pd->dados[pd->topo2] = al;
        pd->topo2--;
    }
    
    return 1;
}
int remove_PilhaDupla(PilhaDupla* pd, int p){
    if (pd == NULL || PilhaDupla_vazia(pd, p))
        return 0;

    if(p == 1){
        pd->topo1--;
    }else if(p == 2){
        pd->topo2++;
    }else{
        return 0;
    }

    return 1;
}
int consulta_topo_PilhaDupla(PilhaDupla* pd, int p, struct aluno *al){
    if (pd == NULL || al == NULL || PilhaDupla_vazia(pd,p))
        return 0;
    if(p == 1){
        *al = pd->dados[pd->topo1 - 1];
    }else if(p == 2){
        *al = pd->dados[pd->topo2 + 1];
    }else{
        return 0;
    }
       
    return 1;
}
