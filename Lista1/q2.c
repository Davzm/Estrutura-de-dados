#include <stdio.h>

void ordenarPar(int *x, int *y){
    if(*x < *y){
        printf("%d %d\n", *x, *y);
    }else{
        printf("%d %d\n", *y, *x);
    }
}

int main(){
    int a, b;
    int c, d;
    a = 9;
    b = 5;

    c = 2;
    d = 7;

    ordenarPar(&a, &b);
    puts("--------------");
    ordenarPar(&c, &d);

    return 0;
}