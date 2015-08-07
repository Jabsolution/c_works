#include <stdio.h>
#include <stdlib.h>

typedef struct _list {
    int val;
    struct _list *next;
} list;

void insert_list(list **, list **, int);
void create_cycle(list *, list *, int);
list *get_node(int);
void print_list(list *);
int is_cycle(list *);

int main() {
    int items[] = {1, 2, 3, 4, 5, 6, 7};
    int i = 0;
    list *head = NULL;
    list *tail = NULL;

    for (i = 0; i <= 6; i++) {
        insert_list(&head, &tail, items[i]);
    }
    create_cycle(head, tail, 3);
    if (is_cycle(head))
        printf("Found cycle in the list");
}

void create_cycle(list *head, list *tail, int val) {
    list *node = NULL;

    if (!head || !tail) 
        return;

    node = head;
    while (node) {
        if (node->val == val) {
            tail->next = node;
            return;
        }
        node = node->next;
    }
}

void insert_list(list **head, list **tail, int val) {
    list *node;

    node = get_node(val);

    /*
     * Empty list
     */
    if (!*head) {
        *head = node;
    } else {
        (*tail)->next = node;
    }
    *tail = node;   
}

void print_list(list *node) {
    while (node) {
        printf("%d ", node->val);
        node = node->next;
    }
}

list *get_node(int val) {
    list *node = NULL;
    node = (list *)malloc(sizeof(list));
    node->val = val;
    node->next = NULL;
    return node;
}

int is_cycle(list *node) {
    list *s_ptr = NULL;
    list *f_ptr = NULL;

    if (!node)
        return 0;

    s_ptr = node;
    while (s_ptr->next) {
        if (!f_ptr) {
            f_ptr = s_ptr->next->next;
        } else if (f_ptr->next) {
            f_ptr = f_ptr->next->next;
        }

        if (f_ptr == s_ptr) {
            return 1;
        }

        s_ptr = s_ptr->next;
    }
    return 0;
}

