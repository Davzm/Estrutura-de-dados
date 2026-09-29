#include <stdio.h>

int *primeiraOcorrencia(int *v, int n, int alvo)
{
    for (int i = 0; i < n; i++)
    {
        if (*v == alvo)
        {
            *v = 0;
            return v;
        }

        v++;
    }

    return NULL;
}

int main()
{
    int v[] = {12, 7, 30, 4, 18, 30};
    int n = sizeof(v) / sizeof(v[0]);
    int alvo = 30;

    if (primeiraOcorrencia(v, n, alvo) == NULL)
    {
        puts("nao encontrado");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            printf("%d ", v[i]);
        }
    }

    return 0;
}