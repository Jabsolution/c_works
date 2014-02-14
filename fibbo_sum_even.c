#include <stdio.h>
#include <stdlib.h>

int fibbo(int, int *);

int main() {
    int sum = 0;
    int a[34] = {0};
    int i = 0;
    fibbo(34, a);
    printf("\n");
    for(i = 0; i < 34; i++) {
        if (!(a[i] % 2)) {
            printf("%d ", a[i]);
            sum += a[i];
        }
    } 
    printf("\nEven sum: %d", sum);
    
}

int fibbo(int n, int *a) {
    if (n == 1) 
        return 1;
    if (!n) 
        return 0;
    if (a[n])
        return a[n];
    a[n] = fibbo(n-1, a) + fibbo(n - 2, a);
    printf("%d ", a[n]);
    return a[n];
}
