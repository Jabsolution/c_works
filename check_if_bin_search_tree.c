/*
 * Print tree in BFS style.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct _tree {
    int val;
    struct _tree *left;
    struct _tree *right;
} tree;

void insert_tree(tree **, int);
void inorder_print(tree *);
int is_bin_search_tree(tree *);

int main() {
    int items[]= {45, 23, 98, 38, 2, 12, 98, 101, 36, 36};
    int idx = 0;
    tree *head1 = NULL;
    tree *tree_node = NULL;

    /*
     * The master tree
     */
    for(idx = 0; idx <= 9; idx++) {
        insert_tree(&head1, items[idx]);
    }

    inorder_print(head1);
    if (is_bin_search_tree(head1)) 
        printf("Yes");
    else
        printf("No");
}

int is_bin_search_tree(tree *head) {
    if (!head)
        return 1;
    if (!head->left && !head->right)
        return 1;
    if (!head->left)
        return ((head->val < head->right->val)
                && (is_bin_search_tree(head->left)) 
                && (is_bin_search_tree(head->right)));
    if (!head->right)
         return ((head->val >= head->left->val)
                 && (is_bin_search_tree(head->left))
                 && (is_bin_search_tree(head->right)));

     return ((head->val < head->right->val)
             && (head->val >= head->left->val)
             && (is_bin_search_tree(head->left))
             && (is_bin_search_tree(head->right)));
}

void inorder_print(tree *head) {
    if (!head)
        return;
    inorder_print(head->left);
    printf("%d ", head->val);
    inorder_print(head->right);
}

void insert_tree(tree **head, int val) {
    tree *node = *head;
    tree *prevNode;

    while (node) {
        prevNode = node;
        if (val <= (node->val)) 
            node = node->left; 
        else 
            node = node->right;
    }

    if (!*head) {
        node = malloc(sizeof(tree));
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        *head = node;
    } else if (val <= prevNode->val) {
        node = malloc(sizeof(tree));
        node->val = val;
        node->left = NULL;
        node->right = NULL;
        prevNode->left = node;
    } else {
        node = malloc(sizeof(tree));
        node->val = val;
        node->right = NULL;
        node->left = NULL;
        if (val == 12) 
            prevNode->left = node;
        else
            prevNode->right = node;
    }
}
