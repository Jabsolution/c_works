#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int val;
    struct _tree *right;
    struct _tree *left;
} tree;

void print_inorder(tree *);
tree *get_common_ancestor(tree *, int, int);
tree * find(tree *, int);
void insert_tree(tree **, int);
void create_node(tree **, int *);

int main() {
    int items[]= {45, 23, 98, 38, 2, 12, 98, 101, 36, 100};
    tree *head = NULL;
    tree *node = NULL;
    int len = 0;
    int i = 0;

    len = (sizeof(items)/sizeof(int));
    printf("Size is: %d\n", len);

    for (i = 0; i <= len - 1; i++) {
        insert_tree(&head, items[i]);
    }
    print_inorder(head);
    node = get_common_ancestor(head, 36, 38);
    if (node) {
        printf("Common Ancestor: %d", node->val);
    }
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


void print_inorder(tree *node) {
    if (!node)
        return;
    print_inorder(node->left);
    printf("%d ", node->val);
    print_inorder(node->right);
}

tree *get_common_ancestor(tree *root, int a, int b) {
    tree *is_b_at_left = NULL;
    tree * is_a_at_left = NULL;
    tree *is_a_at_right = NULL;
    tree *is_b_at_right = NULL;

    printf("\nGetting ancestor of: %d %d\n", a, b);
    
    if (!root)
        return NULL;
    if (!a && !b) 
        return NULL;

    if ((root->val == a) || (root->val == b)) 
        return root;

    is_a_at_left = find(root->left, a);
    is_b_at_left = find(root->left, b);

    is_a_at_right = find(root->right, a);
    is_b_at_right = find(root->right, b);

    if ((is_a_at_left && is_b_at_left) && is_a_at_left == is_b_at_left) {
        return is_a_at_left;
    } 
    if ((is_a_at_right && is_b_at_right) && is_a_at_right == is_b_at_right) {
        return is_a_at_right;
    } 
    return root;
}

tree * find(tree *root, int val) {
    if (!root)
        return NULL;
    if ((root->left && root->left->val == val) 
        || (root->right && root->right->val == val)
        || root->val == val
        || find(root->left, val) || find(root->right, val)) {
        printf("\nReturning :%d", root->val);
        return root;

    }
    return NULL;
}
