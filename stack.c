#include <stdio.h>
#include <stdlib.h>

typedef struct _list {
    void *data;
    struct _list *next;
} list;

typedef struct _stack {
    void *stack_element;
    void *top;
    int stack_size;
    int current_size;
} stack;

typedef struct _test_data {
    int data;
} test_data;

int main() {
    stack *st = malloc(sizeof(stack));
    test_data *st_ele = malloc(sizeof(test_data));

    st_ele->data = 10;
    stack_init(st, 256);
    push(st, (void *)st_ele);
}

void stack_init(stack *st, int size) {
    if (!st)
        return NULL;

    st->size = size;
    st->top = NULL;
    st->stack_element = NULL;

}

void push(stack *st, void *element) {
    list *head;
    list *tail;

    if (!st->top) {
        add_node((void *)element, &tail);
        head = tail;
    } else {
        if (st->size <= st->current_size) {
            add_node((void *)element, &tail);
            st->top = (void *)tail;
        } else {
            printf("Stack is full\n");
        }
    }
}

void add_node(void *element, list **tail) {
    list *node = malloc(sizeof(list));
    if (!*tail) {
        node->data = element;
        node->next = NULL;
        *tail = node;
        return;
    }

    node->data = element;
    node->next = NULL;
    (*tail)->next = node;
    (*tail) = node;
}





