/*
Realiza 3 trocas, tanto para para n = 6 quanto para n = 7
Quando n é ímpar, o elemento central não muda de posição
*/
#include <stdio.h>

void inverter(int *v, int n){
    int *aux = v + (n - 1);
    int temp;

    for (int i = 0; i < n; i++){
        if (v == aux){
            break;
        }else if(v + 1 == aux){
            temp = *v;
            *v = *aux;
            *aux = temp;
            break;
        }else{
            temp = *v;
            *v = *aux;
            *aux = temp;

            v++;
            aux--;
        }
    }
}

int main(void){
    //int v[] = {1,2,3,4,5,6,7};
    int v[] = {12, 7, 30, 4, 18, 9};
    int n = sizeof(v) / sizeof(v[0]);

    inverter(v, n);

    for (int i = 0; i < n; i++){
        printf("%d ", v[i]);
    }

    return 0;
}