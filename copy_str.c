#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "Mr John Smith    ";
    char tmp[17] = {};
    int len = 16;
    int i = 0;
    int j = 0;
    strncpy(tmp, str, len);

    printf("%s\n", tmp);
    for (i = 0; (j <= len && tmp[i] != '\0'); i++) {
        if (tmp[i] == ' ') {
            strncpy(&str[j], "%20", 3);
            j = j + 3;
        } else {
            str[j++] = tmp[i];
        }
    }
    printf("%s\n", str);
}




