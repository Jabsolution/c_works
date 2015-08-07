#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int data;
    struct _tree *right;
    struct _tree *left;
    struct _tree *parent;
} tree;

void insert_into_tree(tree **, int);
void inorder_print(tree *, int);
void tree_rotate(tree **);
void rotate_left(tree **, tree *);
void rotate_right(tree **, tree *);

int odd_sum = 0;
int even_sum = 0;
tree **master_root = NULL;

int main() {
    int tests = 0;
    int size = 0;
    int alphas_betas[2];
    int *numbers = NULL;
    int i = 0;
    tree *root = NULL;

    scanf("%d", &tests);


    scanf("%d", &size); 

    numbers = malloc(sizeof(int) * size);

    scanf("%d", &alphas_betas[0]);
    scanf("%d", &alphas_betas[1]);

    for (i = 0; i < size; i++) {
        scanf("%d", &numbers[i]);
    }

    for (i = 0; i < size; i++) {
        insert_into_tree(&root, numbers[i]);
    }

    master_root = &root;

    inorder_print(root, 0);
    printf("%d %d\n", even_sum, odd_sum);
    tree_rotate(&root);
    printf("%d %d\n", even_sum, odd_sum);
}

void tree_rotate(tree **root) {
    tree *node = *root;

    if (!*root)
        return;

    while (node->left) {
        rotate_right(root, node);
        tree_rotate(&(node->left));
        inorder_print(*master_root, 0);
        printf("%d %d\n", even_sum, odd_sum);
    }

    while (node->right) {
        tree_rotate(&(node->right));
        rotate_left(root, node);
        inorder_print(*master_root, 0);
        printf("%d %d\n", even_sum, odd_sum);
    }
}

void inorder_print(tree *root, int index) {
    if (!root)
        return;

    inorder_print(root->left, index + 1);
    if (index % 2) {
        printf("Odd %d\n", root->data);
        odd_sum += root->data;
    } else {
        printf("Even %d\n", root->data);
        even_sum += root->data;
    }
    inorder_print(root->right, index + 1);
}

void insert_into_tree(tree **root, int a) {
    tree *node = NULL;
    tree *prevNode = NULL;

    if (!*root) {
        node = malloc(sizeof(tree));
        node->data = a;
        node->left = NULL;
        node->right = NULL;
        node->parent = NULL;
        *root = node;
        return;
    }

    node = *root;
    while (node) {
        prevNode = node;
        if (node->data > a) {
            node = node->left;
        } else {
            node = node->right;
        }
    }

    node = malloc(sizeof(tree));
    node->data = a;
    node->left = NULL;
    node->right = NULL;
    node->parent = prevNode;
    if (prevNode->data > a) {
        prevNode->left = node;
    } else {
        prevNode->right = node;
    }
}

void rotate_left(tree **root, tree *node) {
    tree *rnode = NULL;
    if (!*root || !node)
        return;

    rnode = node->right;

    if (!rnode)
        return;

    node->right = rnode->left;
    
    if (rnode->left) {
        rnode->left->parent = node;
    }

    rnode->parent = node->parent;

    if (!node->parent) {
        *root = rnode;
    } else if (node == node->parent->left) {
        node->parent->left = rnode;
    } else {
        node->parent->right = rnode;
    }

    rnode->left = node;
    node->parent = rnode;
} 

void rotate_right(tree **root, tree *node) {
    tree *lnode = NULL;
    if (!*root || !node)
        return;

    lnode = node->left;

    if (!lnode)
        return;

    node->left = lnode->right;

    if (!lnode->right) {
        lnode->parent = node;
    }

    lnode->parent = node->parent;

    if (!node->parent) {
        printf("Changing root with %d", lnode->data);
        *root = lnode;
    } else if (node == node->parent->left) {
        node->parent->left = lnode;
    } else {
        node->parent->right = lnode;
    }

    lnode->right = node;
    node->parent = lnode;
}
