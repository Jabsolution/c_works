#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int ele; // Generic tree
    struct _tree *left;
    struct _tree *right;
} tree;

void insert_tree(tree **, int);
void print_tree_inorder(tree *);
void mirror_tree(tree **);
int check_if_mirror_trees(tree *, tree *);
int check_if_bin_search_tree(tree *);
void print_successor(tree *, int);

int main() {
    int items[]={45, 23, 98, 38, 2, 12, 98, 101, 36};
    int items1[]={45, 23, 98, 38, 2, 12, 98, 101, 36};
    int idx = 0;
    tree *A = NULL;
    tree *B = NULL;

    for(idx = 0; idx < 8; idx++) {
        insert_tree(&A, items[idx]);
        insert_tree(&B, items1[idx]);
    }

    print_tree_inorder(A);
    mirror_tree(&B);
    print_tree_inorder(B);
    if (check_if_mirror_trees(A, B))
        printf("True\n");
    else
        printf("False\n");

    if (check_if_bin_search_tree(A))
        printf("Bin tree\n");
    else
        printf("Not a bin tree\n");
    print_successor(A, 23);
}

void print_successor(tree *node, int ele) {
    tree *temp;
    tree *prev_node;
    if (node->right) {
        temp = node->right;
        while (temp) {
            prev_node = temp;
            temp = temp->left;
        }
        printf("Successor: %d", prev_node->ele);
    }
}

int check_if_bin_search_tree(tree *A) {
    if (!A)
        return 1;

    if (!check_if_bin_search_tree(A->left))
        return 0;
    if (!check_if_bin_search_tree(A->right))
        return 0;

    if (!A->left && !A->right)
        return 1;
    if (!A->left && (A->ele > A->right->ele))
        return 0;
    else if (!A->right && (A->ele < A->left->ele))
        return 0;
    else if (((A->left) && (A->ele < A->left->ele)) 
            || ((A->right) && (A->ele > A->right->ele)))
        return 0;

    return 1;
}

int check_if_mirror_trees(tree *A, tree *B) {
    if (!A && !B) 
        return 1;
    else if (!A && B)
        return 0;
    else if (A && !B)
        return 0;

    if (!check_if_mirror_trees(A->left, B->right)) 
        return 0;
    printf("A:B [%d]:[%d]\n", A->ele, B->ele);
    if (A->ele != B->ele) 
        return 0;
    if (!check_if_mirror_trees(A->right, B->left)) 
        return 0;
    return 1;
}

void mirror_tree(tree **head) {
    tree *temp;

    if (!*head)
        return;
    mirror_tree(&(*head)->left);
    mirror_tree(&(*head)->right);

    if ((*head)->left || (*head)->right) {
        temp = (*head)->left;
        (*head)->left = (*head)->right;
        (*head)->right = temp;
    }

}

void print_tree_inorder(tree *head) {
    if (!head)
        return;
    print_tree_inorder(head->left);
    printf("%d ", head->ele);
    print_tree_inorder(head->right);
}

void insert_tree(tree **head, int ele) {
    tree *node = *head;
    tree *prevNode;
    tree *temp;

    while (node) {
        prevNode = node;
        if (ele < node->ele)
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

