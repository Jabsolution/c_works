#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int val;
    struct _tree *right;
    struct _tree *left;
    struct _tree *parent;
} tree;

void print_inorder(tree *);
tree *get_common_ancestor(tree *, int, int);
tree *get_ancestor(tree *, tree *, tree *);
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
    node = get_common_ancestor(head, 36, 45);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 2, 38);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 2, 12);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 12, 100);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 23, 38);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 45, 98);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 98, 98);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
    node = get_common_ancestor(head, 36, 38);
    if (node) {
        printf("\nCommon ancestor: %d\n", node->val);
    } else { 
        printf("\nCouldn't find common ancestor\n");
    }
}

void insert_tree(tree **head, int item) {
    tree *node = NULL;
    tree *prevNode = NULL;

    if (!*head) {
        create_node(&node, &item);
        *head = node;
        node->parent = NULL;
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
        node->parent = prevNode;
    } else {
        prevNode->right = node;
        node->parent = prevNode;
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
    tree *nodeA;
    tree *nodeB;

    if (!root)
        return NULL;
    if (!a && !b) 
        return NULL;

    nodeA = find(root, a);
    nodeB = find(root, b);

    printf("\nnodeA: %d nodeB: %d", nodeA->val, nodeB->val);
    
    if (!nodeA && !nodeB)
        return NULL;

    return get_ancestor(root, nodeA, nodeB);
}

tree *get_ancestor(root, nodeA, nodeB) {
    while (nodeA) {
        if (!nodeA->parent)
            return nodeA;
        if (nodeA->parent->val == nodeB->val)
            return nodeA->parent;
        if (nodeA->parent->val > nodeB->val) {
            return nodeA;
        } 

        nodeA = nodeA->parent;
    }

    return NULL;
}

tree* find(tree *root, int val) {
    if (!root)
        return NULL;
    if (root->val == val)
        return root;
    return ((root->val >= val) ? find(root->left, val) : find(root->right, val));
}
