/*
Com v = realloc(v...), se o realloc falhar, o bloco de memória antigo se perde, assim como os dados 
que ali estavam armazenados, gerando um vazamento de memória

Com 1000 elementos, são necessários 9 chamadas de realloc, com 1022 elementos copiados. Se o realloc 
crescesse de 1 em 1, seriam necessárias 998 operações, com 499499 elementos copiados.
*/


#include <stdio.h>
#include <stdlib.h>

int fun(int *vetor){
    int elementos_lidos = 0;
    int capacidade = 2;
    int qtd_reallocs = 0;
    int soma = 0;
    int n = 0;
    
    if(vetor == NULL){
        printf("Não há memória disponível\n");
        return 1;
    }

    while(n != -1){
        scanf("%d", &n);

        if(n == -1){
            break;
        }
        

        if(elementos_lidos == capacidade){
            capacidade *= 2;
            int *vetorAux;
            vetorAux = realloc(vetor, capacidade * sizeof(int));
            if(vetorAux == NULL){
                printf("Não há memória disponível\n");
                free(vetor);
                return 1;
            }
            vetor = vetorAux;
            qtd_reallocs++;
        }

        vetor[elementos_lidos] = n;

        soma += n;
        elementos_lidos++;
    }

    

    printf("tam %d cap %d reallocs %d soma %d\n", elementos_lidos, capacidade, qtd_reallocs, soma);
    free(vetor);
    vetor = NULL;
    return 0;

}

int main(void){
    int *vetor; 
    vetor = malloc(sizeof(int)*2);

    fun(vetor);
}