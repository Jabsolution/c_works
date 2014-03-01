/*
 *
 * Stack boxes based on their b(breadth) x h(heigh) x d(depth).
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _box {
    int h;
    int w;
    int d;
} box;

int stack_boxes( box *, box *);
int main() {
    box boxes[] = {
        {12, 16, 9},
        {9, 15, 7},
        {27, 17, 10},
        {7, 14, 6}
    };
    box *b = NULL;
    printf("height is: %d", stack_boxes(boxes, b));
}

int stack_boxes(box *b_array, box *b ) {
    int i = 0;
    int max_h = 0;
    int max = 0;
    for(i = 0; i < 4; i++) {
        if (!b) {
            max = b_array[i].h + stack_boxes(b_array, &b_array[i]);
            if (max > max_h) {
                max_h = max;
            }
        } else if ((b_array[i].h < b->h)
                   && (b_array[i].w < b->w)
                   && (b_array[i].d < b->d)) {
            max = b_array[i].h + stack_boxes(b_array, &b_array[i]);
            if (max > max_h) {
                max_h = max;
            }
        }
    }
    return max_h;
}

