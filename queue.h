#include <stdio.h>
#include <stdlib.h>

typedef struct _queue {
    void *items;         //a pointer to the queue element
    struct _queue *next; //a pointer to the next item in the queue
} queue;

typedef struct _qinfo {
    unsigned long count;
    queue *head;
    queue *tail;
} qinfo;

extern void enqueue(qinfo **, void *);
extern queue *dequeue(qinfo **);
extern void qinit(qinfo **);
