#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int val;
    struct _tree *right;
    struct _tree *left;
} tree;

void print_inorder(tree *);
tree *get_common_ancestor(tree *, int, int);
int find(tree *, int);
void insert_tree(tree **, int);
void create_node(tree **, int *);

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
    printf("\nCommon ancestor: %d\n", (get_common_ancestor(head, 36, 12))->val);
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
    int is_a_at_left = 0;
    int is_a_at_right = 0;
    int is_b_at_right = 0;
    int is_b_at_left = 0;
    
    if (!root)
        return NULL;
    if (!a && !b) 
        return NULL;

    if ((root->val == a) || (root->val == b)) 
        return root;

    if (a <= root->val) 
        is_a_at_left = find(root->left, a);
    else 
        is_a_at_right = find(root->right, a);

    if (b > root->val)
        is_b_at_right = find(root->right, b);
    else
        is_b_at_left = find(root->left, b);


    if ((is_a_at_left != is_b_at_left) || (is_a_at_right != is_b_at_right))
        return root;

    root = is_a_at_left ? root->left : root->right;
    return (get_common_ancestor(root, a, b));
}

int find(tree *root, int val) {
    if (!root)
        return 0;
    if (root->val == val)
        return 1;
    return ((root->val >= val) ? find(root->left, val) : find(root->right, val));
}
