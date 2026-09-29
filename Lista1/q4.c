#include <stdio.h>

void minMax(const int *v, int n, int *min, int *max){
    for(int i = 0; i < n; i++){
        if(*min > *v){ //compara o valor de 'min' com o atual valor do vetor
            *min = *v; //atualiza o valor de 'min', caso passe peli if
        }

        if(*max < *v){ //compara o valor de 'max' com o atual valor do vetor
            *max = *v; //atualiza o valor de 'max', caso passe peli if
        }

        v++; //avança uma posição do vetor
    }
}

int main(){
    int v[] = {12, 7, 30, 4, 18, 9};
    int n = sizeof(v) / sizeof(v[0]);
    int min = v[0]; //iguala 'min' ao primeiro valor do vetor para evitar qualquer erro em caso de assumir um valor arbitrário
    int max = v[0]; //mesma coisa de ^

    minMax(v, n, &min, &max);

    printf("%d %d", min, max);
    

    return 0;
}
