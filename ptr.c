#include <stdio.h>
#include <stdlib.h>

typedef struct _box {
    int a;
    int b;
} box;

void print_val(box *);
int main() {
    box boxes[] = {
        {5, 4},
        {6, 7}
    };

    print_val(boxes);
}

void print_val(box *b) {
    b++;
    printf("%d %d", b->a, b->b);
}
