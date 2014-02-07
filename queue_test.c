#include <stdio.h>
#include <stdlib.h>

typedef struct _ele {
    int i;
    char *str;
} ele;

typedef struct _queue {
    void *items;
    struct _queue *next;
} queue;

void enqueue(queue **, queue **, void *);
queue *dequeue(queue **);

int main() {
    ele items;
    queue *head = NULL;
    queue *tail = NULL;
    queue *node;
    ele *r_node;

    items.i = 10;
    items.str = "jaykdesa";

    enqueue(&head, &tail, (void *)&items);
    node = dequeue(&head);
    if (!node) 
        printf("The queue is empty\n");

    r_node = (ele *)node->items;
    printf("%d %s", r_node->i, r_node->str);
    
    node = dequeue(&head);
    if (!node) 
        printf("THe queue is empty\n");
    
}

void enqueue(queue **head, queue **tail, void *ele) {
    queue *node;
    if (!*head) {
        node = (queue *)malloc(sizeof(queue));
        node->items = ele;
        node->next = NULL;
        *head = node;
        *tail = node; 
        return;
    }
    node = (queue *)malloc(sizeof(queue));
    node->items = ele;
    (*tail)->next = node;
    (*tail) = node;
}

queue *dequeue(queue **head) {
    queue *node;
    if (!*head) {
        return NULL;
    }
    node = *head;
    *head = (*head)->next;
    return node;
}
