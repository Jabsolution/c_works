#include <stdio.h>
#include <stdlib.h>

void permute_str(char *str, int, int);
void swap(char *, char *);

void swap(char *x, char *y) {
    char temp_str;
    temp_str = *y;
    *y = *x;
    *x = temp_str;
}

int main() {
    char str[4] = "abc";
    permute_str(str, 0, 2);
}

void permute_str(char *str, int i, int n) {
    int j;

    if (i == n) {
        printf("%s\n", str);
    } else {
        for (j = i; j <= n; j++) {
            swap((str + i), (str + j));
            permute_str(str, i + 1, n);
            swap((str + i), (str + j));
        }

    }

}

