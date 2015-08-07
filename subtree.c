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
int is_subtree_present(tree *, tree *);
int is_equal(tree *, tree *);

int main() {
    int items[]= {45, 23, 98, 38, 2, 12, 98, 101, 36};
    int items2[] = {23, 2, 12, 38, 36}; 
    int idx = 0;
    tree *head1 = NULL;
    tree *head2 = NULL;
    tree *tree_node = NULL;

    /*
     * The master tree
     */
    for(idx = 0; idx <= 8; idx++) {
        insert_tree(&head1, items[idx]);
    }

    /*
     * Subtree
     */
    for(idx = 0; idx <= 4; idx++) {
        insert_tree(&head2, items2[idx]);
    }

    inorder_print(head1);
    inorder_print(head2);
   
    if (is_subtree_present(head1, head2))
        printf("Yes");
    else
        printf("No");
}

int is_equal(tree *t1, tree *t2) {
    if (!t1 && !t2) 
        return 1;
    if (!t1 || !t2)
        return 0;

    return ((t1->val == t2->val) && is_equal(t1->left, t2->left)
            && is_equal(t1->right, t2->right));
}

int is_subtree_present(tree *t1, tree *t2) {
    if (!t1)
        return 0;
    if (!t2)
        return 1;

    while (t1) {
        if (t1->val == t2->val && is_equal(t1, t2))
            return 1;

        if (t1->val >= t2->val) {
            t1 = t1->left;
        } else {
            t1 = t1->right;
        }
    }

    return 0;
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
        prevNode->right = node;
    }
}
