/*
void destruirAluno(Aluno *a) não conseguiria zerar o ponteiro do chamador, pois Aluno já é um ponteiro,
então nós precisamos de um ponteiro de ponteiro para conseguir acessar o endereço real e zerar essa varíavel de fato.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int   matricula;
    char  nome[32];
    float media;
} Aluno;

Aluno *criarAluno(int matricula, const char *nome, float media){
    Aluno *a;
    a = malloc(sizeof(Aluno));

    if(a == NULL){
        return NULL;
    }

    a -> matricula = matricula;
   strcpy(a -> nome, nome);
    a -> media = media;
    return a;
}

void imprimirAluno(const Aluno *a){
    printf("Detalhes do aluno:\nMatrícula: %d\nNome: %s\nMédia: %.2f\n", a->matricula, a->nome, a->media);
}

void destruirAluno(Aluno **pa){
    if(*pa == NULL){
        return;
    }else{
        free(*pa); //liberando espaço
        *pa = NULL; //garantindo que não ocorra pointer tangling
    }

}


int main(void){
    Aluno *a;
    
    a = criarAluno(1234, "Davi", 7.5);
    imprimirAluno(a);
    destruirAluno(&a);
    printf("%p\n", a);
    return 0;
}