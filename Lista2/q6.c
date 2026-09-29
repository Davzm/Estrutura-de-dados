/*
1) Pede 19 bytes. Não é a soma dos dois strlen, pois o strlen desconsidera o '\0', então ficaria faltando 
1 byte na alocação. Esquecer esse byte extra gera um comportamento indefinido; no meu caso o código imprimiu 
a string corretamente (por causa do buffer?), mas poderia ter corrompido outros dados do heap.

2) devolve 8, pois esse é o tamanho em bytes de um ponteiro
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenar(const char *a, const char *b){
    char *c;
    c = malloc(strlen(a) + strlen(b) + 1);
    if(c == NULL){
        return NULL;
    }

    strcpy(c, a);
    strcat(c, b);

    return c;
}



int main(void){
    char *t = concatenar("Estrutura de ", "Dados");

    printf("%s\n%lu\n", t, strlen(t));
    free(t);
    t = NULL;

    return 0;
}