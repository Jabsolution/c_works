#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[] = "Jay Desai";
    int len = sizeof(buf) / sizeof(char);
    char *storage = malloc(sizeof(char) * len);
    char *tmp = NULL;
    int i = 0;

    tmp = storage;
    while (len) {
        printf("Now copying at: %p\n", storage);
        memcpy(storage++, &buf[i], 1);
        i++;
        len--;
    }
    storage = tmp;
    printf("Storage: %s\n", storage);
}

