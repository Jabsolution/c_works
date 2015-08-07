/*
 * A simple binary search tree
 *
 * This program first builds a tree and print it in-order
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    void *ele; // Generic tree
    struct _tree *left;
    struct _tree *right;
    struct _tree *parent;
} tree;

void insert_tree(tree **, void *);
void print_tree_inorder(tree *);
void transplant(tree **, tree *, tree *);
tree *tree_minimum(tree *);
tree *tree_maximum(tree *);
void delete(tree **, tree *);
tree *parent(tree *, tree *);
tree *successor(tree *);
tree *predecessor(tree *);
tree *search(tree *, int);

int main() {
    int items[]={45, 23, 98, 38, 2, 12, 98, 101, 36};
    int array_len = sizeof(items) / sizeof(int);
    int idx = 0;
    tree *head = NULL;
    tree *srch_node = NULL;

    for(idx = 0; idx < array_len; idx++) {
        insert_tree(&head, (void *)&items[idx]);
    }

    print_tree_inorder(head);
    srch_node = search(head, 12);
    if (srch_node) {
        printf("Found node: %d", *((int *)srch_node->ele));
    }

    delete(&head, srch_node);
    print_tree_inorder(head);
}

void print_tree_inorder(tree *head) {
    if (!head)
        return;
    print_tree_inorder(head->left);
    printf("%d ", *((int *)head->ele));
    print_tree_inorder(head->right);
}

void insert_tree(tree **head, void *ele) {
    tree *node = *head;
    tree *prevNode = *head;

    while (node) {
        prevNode = node;
        if (*((int *)ele) < *((int *)node->ele)) 
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
    } else if (*((int *)ele) < *((int *)prevNode->ele)) {
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
    node->parent = prevNode;
}

tree *search(tree *head, int val) {
    while (head) {
        if (val == *((int *)head->ele)) {
            return head;
        } else if (val > *((int *)head->ele)) {
            head = head->right;
        } else {
            head = head->left;
        }
    }
    return NULL;
}

tree *tree_minimum(tree *node) {
    tree *temp = NULL;

    if (!node) 
        return NULL;

    while (node) {
        temp = node;
        node = node->left;
    }

    return temp;
}

tree *tree_maximum(tree *node) {
    tree *temp = NULL;

    if (!node)
        return NULL;

    while(node) {
        temp = node;
        node = node->right;
    }

    return temp;
}

void delete(tree **head, tree *node) {
    tree *z = NULL;
    if (!node)
        return;

    if (!node->left) {
        transplant(head, node, node->right);
    } else if (!node->right) {
        transplant(head, node, node->left);
    } else {
        z = tree_minimum(node);
        if (z->parent != node) {
            transplant(head, z, z->right);
            node->right->parent = z;
            z->right = node->right;
        }
        transplant(head, node, z);
        node->left->parent = z;
        z->left = node->left;
    }
}

tree *parent(tree *head, tree *node) {
    int val = *(int *)node->val;
    tree *parent = NULL;

    while (head != node) {
        parent = head;
        if (*(int *)head->val > val) {
            head = head->left;
        } else {
            head = head->right;
        }
    }
    return parent;
}

tree *successor(tree *node) {
    tree *temp = NULL;
    if (node->right) {
        return tree_minimum(node->right);
    }

    temp = node->parent;
    while (!temp && node = temp->left) {
        node = temp;
        temp = temp->parent;
    }
    return temp;
}

tree *predecessor(tree *node) {
    tree *temp = NULL;
    if (node->left) {
        return tree_maximum(node->left);
    }

    temp = node->parent;
    while (!temp && node = temp->right) {
        node = temp;
        temp = temp->parent;
    }
    return temp;
}

void transplant(tree **head, tree *u, tree *v) {
    // Edge E(u, v)
    if (!u->parent) {
        *head = v;
    } else if (u->parent->right == u) {
        u->parent->right = v;
    } else {
        u->parent->left = v;
    }

    if (v) {
        v->parent = u->parent;
    }
}
