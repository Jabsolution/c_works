#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_mat(int *, int);
void test(unsigned int *, int, int, int, unsigned int);
void populate_array(unsigned int **t, int);

int main(int argc, char *argv[]) {
    int total = 0;
    int rows  = strtol(argv[1], NULL, 10);
    printf("ROWS: %d\n", rows);
    unsigned int *t = NULL;
    populate_array(&t, rows);
    total += t[0];
    test(t, 0, 0, rows, total);
}

void populate_array(unsigned int **ret_array, int rows) {
    FILE *fp;
    int size = 0;
    int total_int = (rows * (rows + 1)) / 2;
    int i = 0;
    char *t = NULL;
    char *byte = malloc(sizeof(char) * 3);
    unsigned int *t_i = malloc(sizeof(unsigned int) * total_int);
    int idx = 0;

    fp = fopen("p067_triangle.txt", "r");
    fseek(fp, 0, SEEK_END);
    size = ftell(fp);
    t = malloc(sizeof(char) * size);

    printf("size: %d and total_int: %d", size, total_int);
    rewind(fp);

    fread(t, 1, size, fp);

    while(i <= size) {
        if (t[i] < '0' || t[i] > '9') {
            i++;
            continue;
        }
        // Copy two bytes to byte string
        strncpy(byte, &t[i], 2);
        byte[2] = '\0';
        t_i[idx] = strtol(byte, NULL, 10);
        idx++;
        i += 2;
    }

    idx = 0;
    while (idx <= total_int) {
        printf("%d ", t_i[idx]);
        idx++;
    }


    *ret_array = t_i;
}

void test(unsigned int *t, int s_idx, int c_row, int row, unsigned int total) {
    int left = 0;
    int right = 0;
    int left_sum = 0;
    int right_sum = 0;
    int middle = 0;
    int adj_idx = 0;

    printf("New element: %d\n", t[s_idx]);
    s_idx = s_idx + c_row + 1;
    if (c_row == row - 2) {
        if (t[s_idx] > t[s_idx + 1])
            total += t[s_idx];
        else
            total += t[s_idx + 1];
        printf("Total: %d\n", total);
        return;
    }

    printf("Considering %d and %d\n", t[s_idx], t[s_idx + 1]);
    
    // Adjacent children
    adj_idx = s_idx + c_row + 2; 

    // Here adj_idx is a left child and adj_idx + 1 is the right
    left = adj_idx;
    middle = adj_idx + 1;

    printf("LEFT %d and %d\n", t[left], t[middle]);
    if (t[s_idx] + t[left] > t[s_idx] + t[middle])
        left_sum = t[s_idx] + t[left];
    else
        left_sum = t[s_idx] + t[middle];

    right = middle + 1;
    printf("RIGHT %d and %d\n", t[middle], t[right]);
    if (t[s_idx + 1] + t[middle] > t[s_idx + 1] + t[right])
        right_sum = t[s_idx + 1] + t[middle];
    else
        right_sum = t[s_idx + 1] + t[right];

    if (left_sum > right_sum) {
        total += t[s_idx];
        printf("Now total: %d\n", total);
        test(t, s_idx, c_row + 1, row, total);
    } else {
        total += t[s_idx + 1];
        printf("Now total: %d\n", total);
        test(t, s_idx + 1, c_row + 1, row, total);
    }
}

void print_mat(int *t, int len) {
    int row = 0;
    int ele = 0;
    int s_idx = 0;

    while (row < len) {
        while (ele >= 0) {
            printf("%d ", t[s_idx]);
            s_idx++;
            ele--;
        }
        printf("\n");
        ele = row + 1;
        row++;
    }

}

