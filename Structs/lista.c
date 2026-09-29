#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include <string.h>
#include <stdbool.h>

struct lista {
    int qtd;
    struct produto dados[MAX];
};

Lista *cria_lista(){
    Lista *li;
    li = (Lista *) malloc(sizeof(struct lista));
    if (li != NULL){
        li->qtd = 0;
    }
    return li;
}

void libera_lista(Lista *li){
    free(li);
}

int busca_lista_pos(Lista *li, int pos, struct produto *p){
    if (li == NULL || pos <= 0 || pos > li->qtd){
        return 0;
    }
    *p = li->dados[pos - 1];
    return 1;
}

int busca_lista_cod(Lista *li, int cod, struct produto *p){
    if (li == NULL)
        return 0;
    int i = 0;
    while (i < li->qtd && li->dados[i].codigo != cod){
        i++;
    }
    if (i == li->qtd){
        return 0;
    }
    *p = li->dados[i];
    return 1;
}

int insere_lista_final(Lista *li, struct produto p){
    if (li == NULL){
        return 0;
    }
    if (li->qtd == MAX){
        return 0;
    }
    li->dados[li->qtd] = p;
    li->qtd++;
    return 1;
}

int insere_lista_inicio(Lista *li, struct produto p){
    if (li == NULL){
        return 0;
    }
    if (li->qtd == MAX){
        return 0;
    }
    for (int i = li->qtd - 1; i >= 0; i--){
        li->dados[i + 1] = li->dados[i];
    }
    li->dados[0] = p;
    li->qtd++;
    return 1;
}

int insere_lista_ordenada(Lista *li, struct produto p){
    if (li == NULL)
        return 0;
    if (li->qtd == MAX) // lista cheia
        return 0;
    int k, i = 0;
    while (i < li->qtd && li->dados[i].codigo < p.codigo)
        i++;
    for (k = li->qtd - 1; k >= i; k--)
        li->dados[k + 1] = li->dados[k];
    li->dados[i] = p;
    li->qtd++;
    return 1;
}

int remove_lista(Lista *li, int cod){
    if (li == NULL)
        return 0;
    if (li->qtd == 0) // lista vazia
        return 0;
    int k, i = 0;
    while (i < li->qtd && li->dados[i].codigo != cod){
        i++;
    }
    if (i == li->qtd){
        return 0;
    }
    for (k = i; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_otimizado(Lista *li, int cod){
    if (li == NULL)
        return 0;
    if (li->qtd == 0)
        return 0;
    int i = 0;
    while (i < li->qtd && li->dados[i].codigo != cod)
        i++;
    if (i == li->qtd) // não encontrado
        return 0;
    li->qtd--;
    li->dados[i] = li->dados[li->qtd];
    return 1;
}

int remove_lista_inicio(Lista *li){
    if (li == NULL)
        return 0;
    if (li->qtd == 0) // lista vazia
        return 0;
    int k = 0;
    for (k = 0; k < li->qtd - 1; k++)
        li->dados[k] = li->dados[k + 1];
    li->qtd--;
    return 1;
}

int remove_lista_final(Lista *li){
    if (li == NULL)
        return 0;
    if (li->qtd == 0) // lista vazia
        return 0;
    li->qtd--;
    return 1;
}

int tamanho_lista(Lista *li){
    if (li == NULL)
        return -1;
    return li->qtd;
}

int lista_cheia(Lista *li){
    if (li == NULL)
        return -1;
    return (li->qtd == MAX);
}

int lista_vazia(Lista *li){
    if (li == NULL)
        return -1;
    return (li->qtd == 0);
}

/* ---------------------------------------------------------- */
/* Novas funções a implementar (Questões desta atividade)     */
/* ---------------------------------------------------------- */

int lista_tem_espaco(Lista *li, int n){
    if(li == NULL){
        return 0;
    }else if(li -> qtd + n <= MAX){
        return 1;
    }else{
        return 0;
    }
}

float soma_precos(Lista *li){
    if(li == NULL){
        return 0;
    }

    float soma = 0;
    for(int i = 0; i < li -> qtd; i++){
        soma += li -> dados[i].preco;
    }
    return soma;
}

int busca_por_nome(Lista *li, char *nome, struct produto *p){
    if(li == NULL){
        return 0;
    }

    for(int i = 0; i < li -> qtd; i++){

        if(strcmp(li -> dados[i].nome, nome) == 0){
            *p = li -> dados[i];
            return 1;
        }
    }
    return 0;
}

int insere_lista_decrescente(Lista *li, struct produto p){
    if(li == NULL){
        return 0;
    }

    if(li -> qtd == MAX){
        return 0;
    }

    int k,i = 0;

    while(i< li -> qtd && li->dados[i].preco > p.preco){
        i++;
    }

    for (k = li->qtd - 1; k >= i; k--){
        li->dados[k + 1] = li->dados[k];
    }

    li->dados[i] = p;
    li->qtd++;
    return 1;

}

int remove_mais_caro(Lista *li, struct produto *removido){
    if(li == NULL){
        return 0;
    }

    if(li -> qtd == 0){
        return 0;
    }

    int i;
    int posicao = 0;
    float mais_caro = li -> dados[0].preco;

    for(i = 1; i < li -> qtd; i++){
        if(li -> dados[i].preco > mais_caro){
            mais_caro = li -> dados[i].preco;
            posicao = i;
        }
    }
    *removido = li-> dados[posicao];
    li -> qtd--;
    li -> dados[posicao] = li -> dados[li->qtd];
    return 1;

}

int conta_faixa_preco(Lista *li, float min, float max){
    if(li == NULL){
        return 0;
    }

    int contador = 0;
    int i = 0;
    while(i < li->qtd){
        if(li->dados[i].preco >= min && li->dados[i].preco <= max){
            contador++;
        }
        i++;
    }
    return contador;
}

int remove_abaixo_de(Lista *li, float precoMinimo){
    if(li == NULL){
        return 0;
    }
    if(li -> qtd == 0){
        return 0;
    }

    int i;
    int contador = 0;
    for(i = 0; i < li->qtd; i++){
        if(li->dados[i].preco < precoMinimo){
            li -> qtd--;
            li->dados[i] = li->dados[li->qtd];
            i--;
            contador++;
        }
    }
    return contador;
}

int mescla_listas(Lista *destino, Lista *origem){
    if(destino == NULL || origem == NULL){
        return 0;
    }
    int contador = 0;
    
    for(int i = 0; i < origem->qtd; i++){
        if(destino -> qtd == MAX){
            break;
        }

        struct produto temp;
        if (busca_lista_cod(destino, origem->dados[i].codigo, &temp) == 0) {
            contador++;
            destino -> qtd++;
            destino -> dados[destino -> qtd-1] = origem -> dados[i];
        }
        
    }
    return contador;
}
