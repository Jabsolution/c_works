#include <stdio.h>
#include <stdlib.h>


int count = 0;
void print_permutations(char *, int, int);
void swap(char *src, char *dst, int);

int main() {
    char letters[] = "0123456789";
    int len = sizeof(letters) / sizeof(char);
    len -= 1;
    printf("%s %d\n", letters, len);
    print_permutations(letters, 0, len - 1);
}

void swap(char *src, char *dst, int m) {
    char tmp;
    char *lmt = NULL;
    
    /*
     * src = 0, dst = 3
     *
     * lmt = src,
     *
     * src = dst - 1 (2)
     *
     *
     *  0, 1, 2, 3
     *  0, 1, 3, 2
     *  0, 3, 1, 2
     *  3, 0, 1, 2
     */
    if (m == 'r') {
        lmt = src;
        src = dst - 1;
        while (src >= lmt) {
            tmp = *src;
            *src = *dst;
            *dst = tmp;
            dst--;
            src--;
        }
    } else {
        lmt = dst;
        dst = src;
        src = src + 1;
        while (src <= lmt) {
            tmp = *src;
            *src = *dst;
            *dst = tmp;
            dst++;
            src++;
        }
    }
}
/*
 * abc, acb, bac, bca, cba, cab
 *
 */
void print_permutations(char *str, int j, int n) {
    int i = 0;

    if (j == n) {
        ++count;
        printf("%s\n", str);
        if (count == 1000000) {
            exit(1);
        }
        return;
    }

    for (i = j; i <= n; i++) {
        swap((str + j), (str + i), 'r');
        print_permutations(str, j + 1, n);
        swap((str + j), (str + i), 'l');
    }
}

