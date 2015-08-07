#include <stdio.h>
#include <stdlib.h>

void insert_tree(tree **head, void *item) {
    tree *node = NULL;
    tree *prevNode = NULL;

    if (!*head) {
        create_node(&node, &item);
        *head = node;
        return;
    }

    node = *head;
    while (node) {
        prevNode = node;
        if (node->val >= item) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    create_node(&node, &item);
    if (prevNode->val >= item) {
        prevNode->left = node;
    } else {
        prevNode->right = node;
    }
    return;
}
void create_node(tree **node, void *item) {
    if (!item)
        return;
    *node = malloc(sizeof(tree));
    (*node)->ptr = item;
    (*node)->right = NULL;
    (*node)->left  = NULL;
}
