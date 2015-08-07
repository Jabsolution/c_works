#include <stdio.h>
#include <stdlib.h>

int *merge_list(int *, int *, int, int, int);

int main() {
    int list2[] = {2, 3, 4, 9, 10, 12, 21, 25};
    int list1[] = {10, 14, 15, 17, 20, 21, 35, 40, 41};
    int *new_list = NULL;
    int len = (sizeof(list1) + sizeof(list2)) / sizeof(int);
    int len1 = sizeof(list1) / sizeof(int);
    int len2 = sizeof(list2) / sizeof(int);
    int i = 0;

    if (!len1 && !len2) {
        printf("NULL");
    } else if (!len1) {
        new_list = list2;
    } else if (!len2) {
        new_list = list1;
    } else {
        new_list = merge_list(list1, list2, len, len1, len2);
    }

    if (new_list) {
        for (i = 0; i < len; i++) {
            printf("%d ", new_list[i]);
        }
    }
}

int *merge_list(int *list1, int *list2, int len, int len1, int len2) {
    int *new_list = NULL;
    int i = 0;
    int j = 0;
    int new_list_index = 0;

    new_list = (int *)malloc(len * sizeof(int));

    while (i < len1 && j < len2) {
        if (list1[i] <= list2[j]) {
            new_list[new_list_index++] = list1[i++];
        } else {
            new_list[new_list_index++] = list2[j++];
        }
    }

    while (j < len2) {
        new_list[new_list_index++] = list2[j++];
    }

    while (i < len1) {
        new_list[new_list_index++] = list1[i++];
    }

    return new_list;

}


