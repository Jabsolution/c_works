#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max(a,b) a>b?a:b

int getLength(char *);
int main() {
    char *str1 = malloc(sizeof(char) * 5000);
    char *str2 = malloc(sizeof(char) * 5000);
    int len = 0;
    int **matrix = NULL;
    int i = 0;
    int j = 0;
    int l = 0;
    int m = 0;

    memset(str1, '\0', sizeof(char) * 5000);
    memset(str2, '\0', sizeof(char) * 5000);

    scanf("%s", str1);
    scanf("%s", str2);

    len = getLength(str1) + 1;

    matrix = malloc(sizeof(int *) * len);

    for(i = 0; i < len; i++) {
        matrix[i] = malloc(sizeof(int) * len);
    }

    for (i = 0; i < len; i++) {
        for (j = 0; j < len; j++) {
            matrix[i][j] = 0;
        }
    }

    for(i = 1; i < len; i++) {
        l = i - 1;
        for (j = 1; j < len; j++) {
            m = j - 1;
            
            if (str1[l] == str2[m]) {
                matrix[i][j] = matrix[i - 1][j - 1] + 1;
            } else {
                matrix[i][j] = max(matrix[i - 1][j], matrix[i][j - 1]);
            }
        }
    }

    printf("%d", matrix[len - 1][len - 1]);
}

int getLength(char *str) {
    int c = 0;

    while (*str) {
        c += 1;
        str++;
    }

    return c;
}


