#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct _tree {
    int ele;
    struct _tree *left;
    struct _tree *right;
} tree;

typedef struct _bfs_node {
    void *tree_node;
    struct _bfs_node *parent;
    int color; // Not yet visited
} bfs_node;

void insert_tree(tree **, int);
void init_bfs_node(bfs_node **, void *);
void *process_bfs_node_get_tree_node(bfs_node *);
bfs_node *create_bfs_node(tree *);
void inorder_print(tree *);

int main() {
    int items[]={45, 23, 98, 38, 2, 12, 98, 101, 36};
    int idx = 0;
    tree *head = NULL;
    bfs_node *b_node = NULL;
    qinfo *q = NULL;
    tree *tree_node = NULL;

    /*
     * Initialize qinfo
     */
    qinit(&q);

    for(idx = 0; idx < 8; idx++) {
        insert_tree(&head, items[idx]);
    }

    inorder_print(head);

    // Print tree in BFS stlye
    b_node = create_bfs_node(head);
    enqueue(&q, (void *)b_node);

    while ((b_node = (bfs_node *)dequeue(&q))) {
        tree_node = (tree *)process_bfs_node_get_tree_node(b_node);
        printf("%d ", tree_node->ele);
        if (tree_node->left) {
            printf("%d ", tree_node->left->ele);
            b_node = create_bfs_node(tree_node->left);
            enqueue(&q, (void *)b_node);
        } 
        if (tree_node->right) {
            printf("%d ", tree_node->right->ele);
            b_node = create_bfs_node(tree_node->right);
            enqueue(&q, (void *)b_node);
        }
        printf("Head is %p\n", q->head);
        printf("Tail is %p\n", q->tail);
    }
}

void inorder_print(tree *head) {
    if (!head)
        return;
    inorder_print(head->left);
    printf("%d ", head->ele);
    inorder_print(head->right);
}

void *process_bfs_node_get_tree_node(bfs_node *b_node) {
    if (!b_node)
        return NULL;
    return (b_node->tree_node);
}

bfs_node * create_bfs_node(tree *tree_node) {
    bfs_node *node;
    if (!tree_node) 
        return NULL;
    init_bfs_node(&node, (void *)tree_node);
    return node;
}

void init_bfs_node(bfs_node **q, void *node) {
    if (!*q)
        return;

    *q = (bfs_node *)malloc(sizeof(bfs_node));
    (*q)->tree_node = node;
    (*q)->color = 0;
    (*q)->parent = NULL;
}

void insert_tree(tree **head, int ele) {
    tree *node = *head;
    tree *prevNode;

    while (node) {
        prevNode = node;
        if (ele < (node->ele)) 
            node = node->left; 
        else 
            node = node->right;
    }

    if (!*head) {
        node = malloc(sizeof(tree));
        node->ele = ele;
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
