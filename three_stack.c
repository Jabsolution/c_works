#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

typedef struct _stack {
    void **toStacks;
    int sizeOfStack;
} stack;

typedef struct _items {
    int ele;
    char *str;
} items;

/*
 * Initialize stack
 */
void init_stack(stack **s) {
    *s = malloc(sizeof(stack));
    (*s)->toStacks = malloc(MAX_SIZE*sizeof(void *));
    (*s)->sizeOfStack = 0;
}

void push(stack *s, void *items) {
    if (s->sizeOfStack >= MAX_SIZE) {
        printf("Stack is full. Stack Size: %d", s->sizeOfStack);
    }
    s->toStacks[s->sizeOfStack++] = items;
}

void *pop(stack *s) {
    if (s->sizeOfStack < 0) {
        printf("Stack is empty. Stack Size: %d", s->sizeOfStack);
        return 0;
    }
    return(s->toStacks[--(s->sizeOfStack)]);
}

int main() {
    stack *s;
    items i[2];
    items *list_of_items = NULL;

    i[0].ele = 10;
    i[0].str = "jay";

    i[1].ele = 20;
    i[1].str = "desai";

    init_stack(&s);
    push(s, (void *)&i[0]);
    push(s, (void *)&i[1]);
    while ((list_of_items = (items *) pop(s))) {
        printf("Items1: %d %s", list_of_items->ele, list_of_items->str);
    }
}
