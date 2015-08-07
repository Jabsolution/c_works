/*
 *
 * Stack boxes based on their b(breadth) x h(heigh) x d(depth).
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

int stack_boxes(int (*)[3], int n);
void swap(int *, int *);
int main() {
    int boxes[3][3] = {
        {5, 2, 4},
        {1, 4, 2},
        {4, 4, 2},
    };
    printf("height is: %d\n", stack_boxes(boxes, 2));
}

void swap(int *src, int *dst) {
    int tmp = *src;
    *src = *dst;
    *dst = tmp;
}

int stack_boxes(int (*b)[3], int n) {
    int i = 0;
    int j = 0;
    int h_max = 0;
    int h = 0;
    int l = 0;
    int w = 0;
    int k = 0;
    int h_global = 0;
    int l_local  = 0;
    int w_local  = 0;
    int h_global_so_far = 0;
    int buffer[3][3] = {{}};
    int tmp = 0;

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            swap(&b[i][0], &b[i][j]);
            if (h_max < b[i][0]) {
                h_max = b[i][0];
                if ((l <= b[i][1] && w <= b[i][2]) ||         
                    (w <= b[i][1] && l <= b[i][2])) {
                    h_global = h + b[i][0]; 
                    l_local = b[i][1];
                    w_local = b[i][2];
                 } else if (l >= b[i][1] && w >= b[i][2]) {
                     h_global = h + b[i][0];
                     l_local = l;
                     w_local = w;
                 } else {
                     h_global_so_far = h_global;
                     for (k = i; k <= 0; k--) {
                         h_global_so_far -= b[i][0];
                         

                     }

                 }
            }
            printf("h_global: %d\n", h_global);
            printf("height: %d l_local: %d w_local: %d\n", b[i][0], l_local, w_local);
            buffer[tmp][0] = b[i][0];
            buffer[tmp][1] = l_local;
            buffer[tmp][2] = w_local;
            tmp++;

            swap(&b[i][0], &b[i][j]);
        }
        h = h_global;
        l = l_local;
        w = w_local;
        printf("h: %d l:%d w:%d\n", h, l, w);
        h_max = 0;
    }
    /*
     * Print the final array
     */
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", buffer[i][j]);
        }
        printf("\n");
    }
    return h;
}

