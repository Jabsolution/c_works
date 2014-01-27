#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tree_node {
    int ele;
    struct tree_node *right;
    struct tree_node *left;
} tree_node;

void inorder_print(tree_node *);
tree_node *insert_node(int *, int, int); 
tree_node *create_node(int);

int main() {
    int ele[] = {1, 2, 3, 4, 5, 6, 7, 8};
    tree_node *head;
    head = insert_node(ele, 0, 7);
    inorder_print(head);
}

void inorder_print(tree_node *node) {
    if (!node) 
        return;
    inorder_print(node->left);
    printf("%d",  node->ele);
    inorder_print(node->right);
}

tree_node *insert_node(int *arr, int idx_lo, int idx_hi) {
    int len = idx_lo + idx_hi + 1;
    int mid = floor(len/2);
    tree_node *node;
    if (idx_lo > idx_hi)
        return NULL;
    if (idx_lo == idx_hi) {
        node = create_node(arr[idx_lo]);
        node->left = NULL;
        node->right = NULL;
        return node;
    }
    node = create_node(arr[mid]);
    node->left  = insert_node(arr, idx_lo, mid-1);
    node->right = insert_node(arr, mid+1, idx_hi);
    return node;
}

tree_node *create_node(int ele) {
    tree_node *node = NULL;
    node = (tree_node *)malloc(sizeof(tree_node));
    node->ele = ele;
    node->right = NULL;
    node->left = NULL;
    return node;
}
