#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int a;
    struct _tree *left;
    struct _tree *right;
} tree;

tree *form_balanced_bin_tree(int *, int, int);
void print_tree(tree *);

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int len = sizeof(a) / sizeof(int);
    tree *root;

    root = form_balanced_bin_tree(a, 0, len - 1); 
    print_tree(root);
}

void print_tree(tree *root) {
    if (!root)
        return;
    print_tree(root->left);
    printf("%d ", root->a);
    print_tree(root->right);
}

tree *form_balanced_bin_tree(int *a, int lo, int hi) {
    int mid = (lo + hi) / 2;
    tree *node;

    if (lo > hi)
        return NULL;

    node = malloc(sizeof(tree));
    node->a = a[mid];
    node->left = form_balanced_bin_tree(a, lo, mid - 1);
    node->right = form_balanced_bin_tree(a, mid + 1, hi);

    return node;
}

