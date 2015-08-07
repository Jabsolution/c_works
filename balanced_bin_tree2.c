#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct _tree {
    int data;
    struct _tree *left;
    struct _tree *right;
} tree;

tree *create_balanced_bintree(int *, int, int);
void print_tree(tree *);

int main() {
    int items[] = {2, 14, 32, 54, 64, 72, 84, 98};
    tree *head = NULL;
    int lo = 0;
    int high = 7;

    head = create_balanced_bintree(items, lo, high);
    print_tree(head);
}

void print_tree(tree *head) {
    if (!head)
        return;
    print_tree(head->left);
    printf("%d ", head->data);
    print_tree(head->right);
}

tree *create_balanced_bintree(int *items, int lo, int hi) {
    tree *node;
    int mid = 0;

    if (lo > hi) {
        return NULL;
    }

    if (lo == hi) {
        node = (tree *)malloc(sizeof(tree));
        node->data = items[lo];
        node->left = NULL;
        node->right = NULL;
        return node;
    }

    mid = floor((lo + hi) / 2);
    node = (tree *)malloc(sizeof(tree));
    node->data = items[mid];
    node->left = create_balanced_bintree(items, lo, mid - 1);
    node->right = create_balanced_bintree(items, mid + 1, hi);
    return node;
}
