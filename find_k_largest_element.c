#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int a;
    struct _tree *left;
    struct _tree *right;
    struct _tree *parent;
} tree;
void build_BST(tree **, int);
void print_BST(tree *);
tree *return_kth_element(tree *, int);

int main() {
    int a[] = {1, 3, 12, 19, 13, 2, 15};
    int len = sizeof(a) / sizeof(int);
    int i = 0;
    tree *root = NULL;
    tree *node = NULL;

    for (i = 0; i < len; i++) {
        build_BST(&root, a[i]);
    }

    print_BST(root);
    node = return_kth_element(root, 3);

    printf("Element: %d", node->a);
}

void print_BST(tree *root) {
    if (!root)
        return;
    print_BST(root->left);
    printf("%d ", root->a);
    print_BST(root->right);
}

void build_BST(tree **root, int ele) {
    tree *node = malloc(sizeof(tree));
    tree *prevNode = NULL;
    tree *tnode = *root;
    
    if (!*root) {
        *root = node;
        node->a = ele;
        node->right = NULL;
        node->left = NULL;
        node->parent = NULL;
        return;
    }

    while (tnode) {
        prevNode = tnode;
        if (tnode->a < ele) {
            tnode = tnode->right;
        } else {
            tnode = tnode->left;
        }
    }

    if (prevNode->a > ele) {
        prevNode->left = node;
    } else {
        prevNode->right = node;
    }

    node->a = ele;
    node->parent = prevNode;
    node->left = NULL;
    node->right = NULL;

}

tree *return_kth_element(tree *root, int k) {
    tree *node = root;
    tree *prevNode = NULL;

    while (k >= 0) {
        /* We first locate the MAX node by traversing to the right */
        while(node) {
            prevNode = node;
            node = node->right;
        }

        k -= 1;
        if (k) {
            if (prevNode->left) {
                node = prevNode->left;
            } else {
                node = prevNode->parent;
            }
        }
    }

    return prevNode;
}
