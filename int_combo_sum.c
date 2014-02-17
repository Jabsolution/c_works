#include <stdio.h>
#include <stdlib.h>

void print_combo_sum(char *, int, int);

int main() {
    int no = 7;
    char str[7] = {};

    print_combo_sum(str, no, 0);
}

void print_combo_sum(char *str, int no, int idx) {
    int rem = 0;
    int i = 1;

    if (no == 1) {
        str[idx] = '0' + no;
        str[idx + 1] = '\0';
        printf("Str: %s\n", str);
        return;
    }

    /*
     * Exclude N+0 = N
     */
    if (idx) {
        str[idx++] = '0' + no;
        str[idx] = '\0';
        printf("Str: %s\n", str);
        idx = idx - 1;
    }

    str[idx++] = '0' + i;
    print_combo_sum(str, no - i, idx);
    i++;
    idx = idx - 1;
    while (i <= no/2) {
        str[idx++] = '0' + i;
        str[idx++] = '0' + (no - i);
        i++;
        str[idx] = '\0';
        printf("Str: %s\n", str);
        idx = idx - 2;

    }
}
