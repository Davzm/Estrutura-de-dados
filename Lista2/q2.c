/*
Pois é impossível saber previamente quantos valores serão digitados, então a memória precisa ser alocada 
dinamicamente.
*/

#include <stdio.h>
#include <stdlib.h>

float calculaMedia(int n){
    float *notas;
    notas = malloc(n * sizeof(float));
    float media = 0;
    //float nota;
    float maior = 0;

    for (int i = 0; i < n; i++){
        printf("Nota %d: ", i + 1);
        scanf("%f", notas);
        //*notas = nota;
        media += *notas;

        if (*notas > maior){
            maior = *notas;
        }

        notas++;
    }


    printf("Maior = %.2f\n", maior);
    return media / n;

    free(notas); //liberando espaço
    notas = NULL; //garantindo que não ocorra pointer tangling
}

int main(void){
    int n;
    printf("Digite quantas notas serão analisadas: ");
    scanf("%d", &n);

    printf("Média = %.2f\n", calculaMedia(n));

    return 0;
}