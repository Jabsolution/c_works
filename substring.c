/*
 *
 * Print substrings
 *
 */
#include <stdio.h>
#include <stdlib.h>

void substring(char *);

int main() {
    char *str = "banana";
    substring(str);
}

void substring(char *str) {
    int i = 0;
    int j = 0;
    int k = 0;
    char buf_str[6] = "";

    for(i = 0, k = 0; str[i] != '\0'; i++, k = 0) {
       buf_str[k++] = str[i];
       for(j = i + 1; str[j] != '\0'; j++) {
           buf_str[k++] = str[j];
           buf_str[k] = '\0';
           printf("\n%s", buf_str);
       }
    }
}
