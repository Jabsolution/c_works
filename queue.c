/*
 *
 * A generic Queue 
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

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
