#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MOD 1000000009

void matrix_chain(int);

int main() {
    int n = 0;
    scanf("%d", &n);
    matrix_chain(n);
}

void matrix_chain(int n) {
    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;
    int c[151] = {0};
    int m[152][152] = {{0}};
    c[0] = 1;
    c[1] = 1;

    for (i = 2; i < n; i++) {
        for (k = 0; k < i; k++) {
            c[i] = (c[i] + ((c[k] * c[i - k - 1]) % (MOD)) % MOD);
        }
    }

    for (i = 1; i < n + 1; i++) {
        m[i][i] = i;
    }

    for (l = 2; l < n + 1; l++) {
        for (i = 1; i <= n - l + 1; i++) {
            j = i + l - 1;
            for (k = i; k < j + 1; k++) {
                m[i][j] = m[i][j] + ((c[k - i] * c[j - k] % MOD) * m[k][k]) % MOD;
                m[i][j] = m[i][j] - (m[i][k - 1] * c[j - k] + m[k + 1][j] * c[k - i] % MOD) % MOD;
                printf("%d %d %d\n", i, j, m[i][j]); 
            }
        }
    }

    printf("%d ", m[1][n]);
}
