#include <stdio.h>
#include <stdlib.h>

void print_permute_str(char *, int, int, int);
void swap(char *, char *);

void swap(char *p1, char *p2) {
    char tmp;
    tmp = *p1;
    *p1 = *p2;
    *p2 = tmp;
}

int main() {
    char str[] = "abcde";
    int n = 5;
    int k = 3;

    print_permute_str(str, 0, n, k);
}

void print_permute_str(char *str, int i, int n, int k) {
    int j = 0;
    int l = 0;

    if (i == k) {
        for (l = 0; l < k; l++) { 
            printf("%c", str[l]);
        }
        printf("\n");
        return;
    }

    for (j = i; j < n; j++) {
        swap(&str[i], &str[j]);  
        print_permute_str(str, i + 1, n, k);
        swap(&str[i], &str[j]);
    }

}

