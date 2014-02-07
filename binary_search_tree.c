#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    void *ele;
    struct _tree *left;
    struct _tree *right;
} tree;

void insert_tree(tree **, int);
void print_tree_inorder(tree *);

int main() {
    int items[]={45, 23, 98, 38, 2, 12, 98, 101, 36};
    int idx = 0;
    tree *head = NULL;

    for(idx = 0; idx < 8; idx++) {
        insert_tree(&head, (void *)&items[idx]);
    }

    print_tree_inorder(head);
}

void print_tree_inorder(tree *head) {
    if (!head)
        return;
    print_tree_inorder(head->left);
    printf("%d ", head->ele);
    print_tree_inorder(head->right);
}

void insert_tree(tree **head, void *ele) {
    tree *node = *head;
    tree *prevNode;

    while (node) {
        prevNode = node;
        if (ele < node->ele) 
            node = node->left; 
        else 
            node = node->right;
    }

    if (!*head) {
        node = malloc(sizeof(tree));
        node->ele = (void *)ele;
        node->left = NULL;
        node->right = NULL;
        *head = node;
    } else if (ele < prevNode->ele) {
        node = malloc(sizeof(tree));
        node->ele = ele;
        node->left = NULL;
        node->right = NULL;
        prevNode->left = node;
    } else {
        node = malloc(sizeof(tree));
        node->ele = ele;
        node->right = NULL;
        node->left = NULL;
        prevNode->right = node;
    }
}
