#include <stdio.h>
#include <stdlib.h>

void print_combo_sum(char *, int, int);

int main() {
    int no = 4;
    char str[4] = {};

    print_combo_sum(str, no, 0);
}

void print_combo_sum(char *str, int no, int idx) {
    int rem = 0;
    int i = 0;

    if (no == 1) {
        str[idx] = '0' + no;
        str[idx + 1] = '\0';
        printf("Str: %s\n", str);
        return;
    }
    /*
     * When no is not a result of a subtraction
     * and
     * index is non-zero
     */
    if (!no && idx) {
        str[idx + 1] = '\0';
        printf("Str: %s\n", str);
        return;
    }

    for (i = 0; i < no; i++) {
        if (!i && !idx) 
            continue;
        rem = no - i;
        str[idx++] = '0' + rem;
        print_combo_sum(str, i, idx);
        idx = idx - 1;;
    }
}
