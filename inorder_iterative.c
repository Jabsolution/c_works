/*
 * A simple binary search tree
 *
 * This program first builds a tree and print it in-order iteratively
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _tree {
    int ele; // Generic tree
    struct _tree *prev;
    struct _tree *left;
    struct _tree *right;
} tree;

typedef struct _list {
    int ele;
    struct _list *next;
    struct _list *prev;
} list;

typedef struct _queue {
    void *ele;
    struct _queue *next;
} queue;



void insert_tree(tree **, int);
void print_tree_inorder(list **, list **, tree *);
void print_tree_inorder1(tree *);
void print_tree_postorder(tree *);
void print_tree_preorder(tree *);
void print_tree_lvlorder(tree *);
void enqueue(queue **, queue **, void *);
void *dequeue(queue **, queue **);
void create_doubly_ll(list **, list **, tree *);
void print_doubly_ll(list *, list *);

int main() {
    int items[]={45, 23, 98, 38, 2, 12, 98, 101, 36};
    int idx = 0;
    tree *head = NULL;
    list *l_head = NULL;
    list *l_tail = NULL;

    for(idx = 0; idx <= 8; idx++) {
        insert_tree(&head, items[idx]);
    }

    //print_tree_inorder1(head);
    print_tree_inorder(&l_head, &l_tail, head);
    printf("\n");
    print_tree_postorder(head);
    print_tree_preorder(head);
    print_tree_lvlorder(head);
    //create_doubly_ll(&l_head, &l_tail, head);
    print_doubly_ll(l_head, l_tail);
    printf("\n");
}

void print_doubly_ll(list *head, list *tail) {
    if (!head || !tail) 
        return;

    printf("\nDoubly Link list: ");
    while (tail) {
        printf("%d ", tail->ele);
        tail = tail->prev;
    }
}

void create_doubly_ll(list **l_head, list **l_tail, tree *head) {
    list *node = NULL;
    if (!head) {
        return;
    }

    if (!*l_head) {
        node = malloc(sizeof(list));
        node->ele = head->ele;
        node->next = node;
        node->prev = NULL;
        *l_head = node;
        *l_tail = node;
        return;
    }

    node = malloc(sizeof(list));
    node->ele = head->ele;
    node->next = *l_head;
    node->prev = *l_tail;
    (*l_tail)->next = node;
    *l_tail = node;
    return;
}

void enqueue(queue **head, queue **tail, void *ele) {
    queue *node = NULL;
    tree *tmp_node = NULL;

    tmp_node = (tree *)ele;
    if (!*head) {
        node = malloc(sizeof(queue));
        node->ele = ele;
        node->next = NULL;
        *head = node;
        *tail = node;
        return;
    }

    node = malloc(sizeof(queue));
    node->ele = ele;
    node->next = NULL;
    (*tail)->next = node;
    *tail = node;
    return;
}

void *dequeue(queue **head, queue **tail) {
    queue *tmp = NULL;
    if (*head) {
        tmp = (*head);

        if (*head == *tail) {
            *head = NULL;
            *tail = NULL;
        } else {
            (*head) = (*head)->next;
        }
        return (tmp->ele);
    } else {
        return NULL;
    }
}

void print_tree_lvlorder(tree *head) {
    queue *q_head = NULL;
    queue *tail = NULL;
    void *node = (void *)head;
    tree *tmp_node = NULL;

    printf("\nLEVEL-ORDER: \n");
    enqueue(&q_head, &tail, node);
    while ((node = dequeue(&q_head, &tail))) {
        tmp_node = (tree *)node;
        if (tmp_node->left) {
            enqueue(&q_head, &tail, (void *)tmp_node->left);
        }
        if (tmp_node->right) {
            enqueue(&q_head, &tail, (void *)tmp_node->right);
        }
        printf("%d ", tmp_node->ele);
    }
}

void print_tree_preorder(tree *head) {
    tree *node = head;
    tree *prevNode = NULL;


    printf("\nPRE-ORDER: \n");
    while (node) {
        if (!node->left || prevNode == node->left) {
            if (!node->left)
                printf("%d ", node->ele);

            if (node->right) {
                node = node->right;
            } else {
                while (node->prev && node == node->prev->right) {
                    node = node->prev;
                }
                prevNode = node;
                node = node->prev;
            }
        } else {
            printf("%d ", node->ele);
            node = node->left;
        }

    }

}
void print_tree_inorder1(tree *head) {
    if (!head)
        return;
    print_tree_inorder1(head->left);
    printf("%d ", head->ele);
    print_tree_inorder1(head->right);
}

/*
 * Go left recursivly, go right tree recursivly then print root.
 *
 * left, right, root
 *
 */
void print_tree_postorder(tree *head) {
    tree *node = NULL;
    tree *prevNode = NULL;

    printf("POST-ORDER: \n");
    node = head;
    while (node) {
        if (!node->left || prevNode == node->left) {
            if (node->right) {
                node = node->right;
            } else {
                while (node->prev && node == node->prev->right) {
                    printf("%d ", node->ele);
                    node = node->prev;
                }
                printf("%d ", node->ele);
                prevNode = node;
                node = node->prev;
            }
        } else {
            node = node->left;
        }
    }

}

/*
 * Left, root, right
 *
 */
void print_tree_inorder(list **l_head, list **l_tail, tree *head) {
    tree *node = NULL;
    tree *prevNode = NULL;
    node = head;

    printf("INORDER: \n");
    while (node) {
        /* We print root if 
         * 1) left node is NULL
         * 2) prevNode is the left node of it's parent
         */
        if (!node->left || (prevNode == node->left)) {
            /* Print Root */
            printf("%d ", node->ele);
            create_doubly_ll(l_head, l_tail, node);

            /* Go to right if it exists */
            if (node->right) {
                node = node->right;
            } else {
                /* This part means that we have visited left, root and right and need to 
                 * climb(follow) the right node chain 
                 */
                while (node->prev && node == node->prev->right) {
                    node = node->prev;
                }
                prevNode = node;
                node = node->prev;
            }
        } else {
            /* Go left untill you find NULL */
            node = node->left;
        }
    }
}

void insert_tree(tree **head, int ele) {
    tree *node = *head;
    tree *prevNode;

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
        node->prev = NULL;
        *head = node;
    } else if (ele < prevNode->ele) {
        node = malloc(sizeof(tree));
        node->ele = ele;
        node->left = NULL;
        node->right = NULL;
        node->prev = prevNode;
        prevNode->left = node;
    } else {
        node = malloc(sizeof(tree));
        node->ele = ele;
        node->right = NULL;
        node->left = NULL;
        node->prev = prevNode;
        prevNode->right = node;
    }
}
