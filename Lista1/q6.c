/*
Se o tamanho estiver errado, o programa vai alocar os dados em outros espaços de memória que não pertencem 
ao vetor destino, o que pode passar despercebido em um código pequeno como este. Que, mesmo com o tamanho 
errado, o compilador printou a palavra corretamente.
O programa não avisa
*/

#include <stdio.h>

int meuStrlen(const char *s){
    int contador = 0;
    while(*s != '\0'){
        contador++;
        s++;
    }
    return contador;
}

void meuStrcpy(char *destino, const char *origem){
    while(*origem != '\0'){
        *destino = *origem;
        destino++;
        origem++;
    }
    *destino = '\0';
    
}

int main(void){
    const char origem[] = "Estrutura de Dados";
    char destino[19];

    meuStrcpy(destino, origem);

    printf("%s | ", destino);
    printf("%d\n", meuStrlen(origem));

    return 0;
}
