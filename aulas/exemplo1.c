#include <stdio.h>



int maior(int A[], int n) {
       int i;
       int M = A[0];
       for (i = 1; i < n; i++) {
            printf("Iteração: %d\n", i);
           if (A[i] >= M)
               M = A[i];
       }
    return M;
   }

int main(){
    int v[] = {4,2,3,1};
    printf("%d\n",maior(v, 4));
    return 0;
}
