#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct _tree {
    int val;
    struct _tree *left;
    struct _tree *right;
} tree;

typedef struct _queue {
    void *items;         //a pointer to the queue element
    struct _queue *next; //a pointer to the next item in the queue
} queue;

typedef struct _qinfo {
    unsigned long count;
    queue *head;
    queue *tail;
} qinfo;

int depth = 0;
void insert_to(tree **, qinfo *, int, int);
void inorder_print(tree *); 
void swap_nodes(tree *, int, int);
void enqueue(qinfo **, void *); 
void *dequeue(qinfo **);
void qinit(qinfo **);
void determine_depth(tree *root, int);

int main() {
    int N = 0;
    int *K = NULL;
    int i = 0;
    int j = 1;
    int left = 0;
    int right = 0;
    int sizeof_k = 0;
    double level = 0;
    tree *root = NULL;
    qinfo *q = NULL;

    scanf("%d", &N);
    level = ceil(log2(N)) + 1;
    //printf("Level: %f", level);

    // Init queue
    qinit(&q);

    for (i = 0; i < N; i++) {
        scanf("%d %d", &left, &right);
        insert_to(&root, q, left, right);
    }   

    determine_depth(root, 0);
    scanf("%d", &sizeof_k);
    K = malloc(sizeof_k * sizeof(int));

    for (i = 0; i < sizeof_k; i++) {
        scanf("%d", &K[i]);
    }

    for (i = 0; i < sizeof_k; i++) {
        j = 1;
        while (K[i] * j < depth) {
            swap_nodes(root, 0, K[i] * j);
            j += 1;
        }
        inorder_print(root);
        printf("\n");
    }
}

void determine_depth(tree *root, int local_depth) {
    if (!root) {
        if (depth < local_depth)
            depth = local_depth;
        return;
    }
    local_depth++;
    determine_depth(root->left, local_depth);
    determine_depth(root->right, local_depth);
}

void swap_nodes(tree *root, int cur_level, int levels) {
    tree *tmp = NULL;

    if (!root) {
        return;
    }

    if (cur_level >= levels)
        return;

    swap_nodes(root->left, cur_level + 1, levels);
    if (cur_level + 1 == levels) {
        tmp = root->left;
        root->left = root->right;
        root->right = tmp;
    } 
    swap_nodes(root->right, cur_level + 1, levels);
}

void inorder_print(tree *root) {
    if (!root)
        return;
    inorder_print(root->left);
    printf("%d ", root->val);
    inorder_print(root->right);
}

void insert_to(tree **root, qinfo *q, int left, int right) {
    tree *node = NULL;
    tree *left_node = NULL;
    tree *right_node = NULL;

    if (left == -1 && right == -1) {
        dequeue(&q);
        return;
    }

    if (!*root) {
        node = malloc(sizeof(tree));
        node->val = 1;
        node->left = NULL;
        node->right = NULL;
        *root = node;

        // Enqueue our first Node
        enqueue(&q, (void *)node);
    }

    node = (tree *)dequeue(&q);
    if (left != -1) {
        left_node = malloc(sizeof(tree));
        left_node->val = left;
        left_node->left = NULL;
        left_node->right = NULL;
        node->left = left_node;
        enqueue(&q, (void *)left_node);
    }

    if (right != -1) {
        right_node = malloc(sizeof(tree));
        right_node->val = right;
        right_node->left = NULL;
        right_node->right = NULL;
        node->right = right_node;
        enqueue(&q, (void *)right_node);
    }
}

void qinit(qinfo **q) {
    *q = malloc(sizeof(qinfo));
    (*q)->count = 0;
    (*q)->head = NULL;
    (*q)->tail = NULL;
}

void enqueue(qinfo **q, void *ele) {
    queue *node;
    if (!(*q)->head) {
        node = (queue *)malloc(sizeof(queue));
        node->items = ele;
        node->next = NULL;
        (*q)->head = node;
        (*q)->tail = node;
        (*q)->count++;
        return;
    }
    node = (queue *)malloc(sizeof(queue));
    node->items = ele;
    node->next = NULL;
    (*q)->tail->next = node;
    (*q)->tail = node;
    (*q)->count++;
}

void *dequeue(qinfo **q) {
    queue *node;
    if (!(*q)->head) {
        return NULL;
    }
    node = (*q)->head;
    (*q)->head = node->next;
    return (node->items);
}


