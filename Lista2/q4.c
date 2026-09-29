/*
1) Para n = 100, nós teríamos 101 chamadas para malloc e para free, considerando que todos os mallocs
funcionariam corretamente.

2) somaDiagonal precisa rececber n, pois m é apenas um endereço e não carrega nenhum informação sobre a
quantidade de dados armazenada ali.
*/

#include <stdio.h>
#include <stdlib.h>

int **criarMatriz(int lin, int col){
    int **m;
    m = malloc(lin * sizeof(int *));

    if(m == NULL){
        puts("Não há memória disponível");
        return NULL;
    }

    for(int i = 0; i < lin; i++){
        m[i] = malloc(col * sizeof(int));
        if(m[i] == NULL){
            puts("Não há memória disponível");
            for(int j = 0; j < i; j++){
                free(m[j]);
            }
            free(m);
            return NULL;
        }
    }

    for(int i = 0; i < lin; i++){
        for(int j = 0; j < col; j++){                       
            m[i][j] = (i*lin)+j;
            //printf("%d ", m[i][j]);
        }
        //puts("");
    }
    return m;
}

void destruirMatriz(int **m, int lin){
    for(int i = 0; i < lin; i++){
        free(m[i]);
    }
    free(m);
}

long somaDiagonal(int **m, int n){
    long soma = 0;
    for(int i = 0; i < n; i++){
        soma += m[i][i];
    }
    return soma;
}


int main(void){
    int n;
    int ** matriz;
    printf("Digite o número de linhas e colunas da matriz: ");
    scanf("%d", &n);

    matriz = criarMatriz(n, n);
    printf("Soma da diagonal = %ld\n",somaDiagonal(matriz, n));

    destruirMatriz(matriz,n);
    return 0;
}



                /*  
    0   1   2
    3   4   5
    6   7   8        
*/