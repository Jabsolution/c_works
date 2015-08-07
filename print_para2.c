#include <stdio.h>
#include <stdlib.h>

void swap(char *, char *);
void print_permutations(char *, int);

int main() {
    int para = 5;
    char *str = malloc(sizeof(int) * para);
    int i = 0;

    for (i = 0; i < (para * 2); i++) {
        if (i < para) {
            str[i] = '(';
        } else {
            str[i] = ')';
        }
    }
    printf("%s\n", str);
    print_permutations(str, para);
}

void swap(char *src, char *dest) {
    char tmp;
    tmp = *src;
    *src = *dest;
    *dest  = tmp;
}

void print_permutations(char *str, int para) {
    int i = 0;
    int j = 0;
    int k = 0;

    for (j = 1, k = para; j < para; j++) {
        for (k = para; k < (para * 2) - 1; k++) {
            swap(&str[j], &str[k]);
            printf("%s\n", str);
            swap(&str[j], &str[k]);
        }
    }
}

