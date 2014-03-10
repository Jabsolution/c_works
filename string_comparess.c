#include <stdio.h>
#include <stdlib.h>

void string_compress(char *, int);

int main() {
    char str[] = "aabccccaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    int len = sizeof(str) / sizeof(char);
    string_compress(str, len - 1);
    printf("\n");
    printf("%s \n", str);
}

void string_compress(char *str, int n) {
    char c = 0;
    int count = 0;
    int i = 0;
    int idx = 0;
    char tmp[10] = {};
    int uniq_char = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (!tmp[str[i] - 'a'])
            uniq_char++;
        tmp[str[i] - 'a']++;   
    }

    if ((uniq_char * 2) >= n) {
        printf("String compression not possible\n");
        exit(1);
    }
 
    for(i = 0; str[i] != '\0'; ) {
        idx = i;
        c   = str[i]; 
        count = 0;
        while (str[idx++] == c) {
            count++;
        }
        i = idx - 1;
        if (count > 1 && tmp[str[i - 1] - 'a'] != count) {
            tmp[str[i - 1] - 'a'] -= count;
            printf("%c%d", str[i - 1], count);
        } else { 
            printf("%c%d", str[i - 1], tmp[str[i - 1] - 'a']);
        }
    }
}
