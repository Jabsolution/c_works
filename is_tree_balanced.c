#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define GET_MAX(a, b) (a > b) ? a : b

typedef struct _tree {
    int val;
    struct _tree *right;
    struct _tree *left;
} tree;

int check_if_tree_is_balanced(tree *);
int measure_height(tree *);
void insert_tree(tree **, int);
void create_node(tree **, int *);
void print_inorder(tree *);

int main() {
    int items[]= {45, 23, 98, 38, 2, 12, 98, 101, 36, 100};
    tree *head = NULL;
    int len = 0;
    int i = 0;

    len = (sizeof(items)/sizeof(int));
    printf("Size is: %d\n", len);

    for (i = 0; i <= len - 1; i++) {
        insert_tree(&head, items[i]);
    }
    print_inorder(head);
    if (check_if_tree_is_balanced(head))
        printf("\nYes\n");
    else 
        printf("No\n");
}

int check_if_tree_is_balanced(tree *head) {
    int left_h = 0;
    int right_h = 0;
    int height = 0;

    if (!head)
        return 1;

    left_h += measure_height(head->left);
    right_h += measure_height(head->right);

    printf("left_h: %d right_h: %d\n", left_h, right_h);
    height = abs(left_h - right_h);
    printf("height: %d", height);
    return ((height > 1) ? 0 : 1);

}

int measure_height(tree *node) {
    int left_h = 0;
    int right_h = 0;

    if (!node)
        return 0;

    if (node->left) 
        left_h = 1;
    if (node->right) 
        right_h = 1;

    left_h += measure_height(node->left);
    right_h += measure_height(node->right);

    return(GET_MAX(left_h, right_h));
}

void print_inorder(tree *node) {
    if (!node)
        return;
    print_inorder(node->left);
    printf("%d ", node->val);
    print_inorder(node->right);
}

void insert_tree(tree **head, int item) {
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

void create_node(tree **node, int *item) {
    if (!item) 
        return; 
    *node = malloc(sizeof(tree));
    (*node)->val = *item;
    (*node)->right = NULL;
    (*node)->left  = NULL;
}

