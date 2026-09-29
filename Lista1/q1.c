/*A função não pode ser void, pois a estrutura do código exige que a função 'dobrar' retorne um valor 
inteiro, que será printado pela main, no entanto uma função do tipo void não retorna nehum valor*/
#include <stdio.h>

int dobrar(int n){
    return n*2;
}
 
int main(void) {
    int n = 21;
    n = dobrar(n);
    printf("%d\n", n);   /* precisa imprimir 42 */
    return 0;
}
