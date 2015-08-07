#include <stdio.h>
#include <stdlib.h>

void reverse_string(char *, char *);

int main() {
    char str[] = "string";
    char *head = NULL;
    char *tail = NULL;
    int len = sizeof(str) - 1;

    head = &str[0];
    tail = &str[len - 1];

    printf("Before: %s", str);
    reverse_string(head, tail);
    printf("\nAfter: %s", str);

    printf("\n");
}

void reverse_string(char *head, char *tail) {
    char tmp;
    while (head != tail && head < tail) {
        tmp = *tail;
        *tail = *head;
        *head = tmp;
        tail--;
        head++;
    }
}

