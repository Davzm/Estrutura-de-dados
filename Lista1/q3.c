/*Pula 4 bytes. Se o vetor fosse de double, pularia 8 bytes*/

#include <stdio.h>

int somaVetor(const int *v, int n){
    int resultado = 0;
    for(int i = 0; i < n; i++){
        resultado += *v;
        v++;
    }
    return resultado;
}

int main(){
    int v[] = {12, 7, 30, 4, 18};
    int n;

    n = sizeof(v) / sizeof(v[0]);

    int resultado = somaVetor(v, n); 
    printf("%d\n", resultado);

    printf("Tamanho em bytes do tipo int: %lu\n", sizeof(int));
    return 0;
}