/*
1 - linha 11 -> função maiorValor retornando o endereço da variável local 'maior'
2 - linha 16 -> ponteiro *p não aponta para nada
3 - linha 4 -> sizeof(v) retorna o tamanho do ponteiro, não do array
4 - linha 6 -> loop tenta acessar elemento inexistente

*/

#include <stdio.h>
 
int maiorValor(int v[], int n) {
    int maior = v[0];
    for (int i = 1; i < n; i++) {
        //puts("for");
        if (v[i] > maior) {
            //puts("if");
            maior = v[i];
        }
    }
    return maior;
}
 
int main(void) {
    int v[5] = {12, 7, 30, 4, 18};
    int n = sizeof(v) / sizeof(int);
    //int *p;
    //printf("%d\n", *p);
    printf("%d\n", maiorValor(v, n));
    return 0;
}
