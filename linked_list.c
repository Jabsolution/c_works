#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct _list {
    int a;
    struct _list *next;
} list;

typedef struct _tree {
    int data;
    struct _tree *right;
    struct _tree *left;
    list *cur_head;
} tree;

void insert_list(list **, list **, int);
void print_list(list *);
list *recursive_reverse(list *, list **);
void iterative_reverse(list **);
void reverse_k_nodes(list **, int);
void create_loop(list *);
int hasLoop(list *);
tree *create_bst(list *, int, int);
void print_inorder(tree *);
void swap_alternate_nodes(list *, list *, list **);
void move_last_to_front(list **head);
list * swap_every_second_node(list *);
void iterative_swap(list **head);
void delete_alternate_node(list *head);
void rotate_by_k_node(list **, list **, int);
void delete_node(list *);
list *get_intersection_point(list *, list *);
list *return_nth_node_from_end(list *, int);

int main() {
    int a[] = {10, 45, 27, 1, 9, 80, 10, 70};
    int sorted[] = {1, 9, 10, 10, 27, 45, 70, 80};
    int sorted_len = sizeof(sorted) / sizeof(int);
    int l1[] = {1, 5, 12, 10, 87, 34, 3, 8};
    int l2[] = {6, 10};
    int len1 = sizeof(l1) / sizeof(int);
    int len2 = sizeof(l2) / sizeof(int);
    int len = sizeof(a) / sizeof(int);
    int i = 0;
    list *head = NULL;
    list *sorted_head = NULL;
    list *sorted_tail = NULL;
    list *tail = NULL;
    list *node = NULL;
    list *int_node = NULL;
    list *l1_head = NULL;
    list *l2_head = NULL;
    list *l1_tail = NULL;
    list *l2_tail = NULL;
    list *long_head = NULL;
    list *new_l2_head = NULL;
    list *intsec_node = NULL;

    // Tree
    tree *root = NULL;

    for(i = 0; i < len; i++) {
        insert_list(&head, &tail, a[i]);
    }

    for(i = 0; i < sorted_len; i++) {
        insert_list(&sorted_head, &sorted_tail, 
                    sorted[i]);
    }

    for (i = 0; i < len1; i++) {
        insert_list(&l1_head, &l1_tail, l1[i]);
    }

    for (i = 0; i < len2; i++) {
        insert_list(&l2_head, &l2_tail, l2[i]);
    }

    // Simple list print
    print_list(head);

    // Iterative reverse 
    iterative_reverse(&head);
    printf("\n");
    print_list(head);

    // Recursive reverse
    int_node = head;
    node = recursive_reverse(int_node, &head);
    node->next = NULL;
    tail = node;
    printf("\n");
    print_list(head);

    // Reverse k nodes of list
    reverse_k_nodes(&head, 4);
    printf("\n");
    print_list(head);


    //Create, detect and remove loop in the list
    // make loop in the list
    create_loop(head);
    //print_list(head);
    if (hasLoop(head)) {
       printf("The list contains loop");
    }
    print_list(head);


    printf("\nCreating BST from a sorted linked list\n");
    printf("Sorted Link List:");
    print_list(sorted_head);
    root = create_bst(sorted_head, 0, sorted_len - 1);
    printf("\nBST:");
    print_inorder(root);

    printf("\n");
    printf("List 1: ");
    print_list(l1_head);
    printf("\n");
    printf("List 2: ");
    print_list(l2_head);
    swap_alternate_nodes(l1_head, l2_head, &new_l2_head);
    printf("\n");
    printf("Merged list: ");
    print_list(l1_head);
    l2_head = new_l2_head;
    printf("\n");
    printf("New list2: ");
    print_list(l2_head);


    printf("Moved to front\n");
    print_list(sorted_head);
    move_last_to_front(&sorted_head);
    printf("After\n");
    print_list(sorted_head);


    printf("\n");
    sorted_head = swap_every_second_node(sorted_head);
    print_list(sorted_head);

    printf("\n");
    iterative_swap(&sorted_head);
    print_list(sorted_head);


    printf("\n");
    delete_alternate_node(sorted_head);
    print_list(sorted_head);


    printf("\nRotation by K node");
    printf("List 1 before rotation");
    print_list(l1_head);
    printf("\nList 1 after rotation");
    rotate_by_k_node(&l1_head, &l1_tail, 3);
    print_list(l1_head);


    printf("\nDelete a node");
    printf("\nList before deletion: ");
    print_list(l1_head);
    printf("\nList after deletion: ");
    delete_node(l1_head);
    print_list(l1_head);


    printf("\nGet Intersection point of two list");
    printf("\nList 1: ");
    print_list(l1_head);
    printf("\nList 2: ");
    print_list(l2_head);
    printf("\nIntersection point is: ");
    intsec_node = get_intersection_point(l1_head, l2_head);
    printf("%d \n", intsec_node->a);
}

list *get_intersection_point(list *l1_head, list *l2_head) {

}

void rotate_by_k_node(list **head, list **tail, int k) {
    int i = 0;
    list *new_head = NULL;
    list *node = *head;

    while (node) {
        if (i == k) {
            if (node->next) {
                new_head = node->next;
                node->next = NULL;
                (*tail)->next = *head;
                *tail = node;
                *head = new_head;
            }
            return;
        } else {
            i++;
            node = node->next;
        }
    }
}

void delete_alternate_node(list *head) {
    list *node = head;
    list *delete_node = NULL;

    if (!node)
        return;

    while (node && node->next) {
        delete_node = node->next;
        node->next = delete_node->next;
        node = node->next;
        free(delete_node);
    }
}


void iterative_swap(list **head) {
    list *prev_pair = NULL;
    list *next_pair = NULL;

    list *tmp = NULL;
    list *node = *head;
    
    while (node) {

        if (!node->next) {
            prev_pair->next = node;
            break;
        }


        tmp = node->next;
        next_pair = node->next->next;

        if (prev_pair)
            prev_pair->next = tmp;
        else
            *head = tmp;

        prev_pair = node;
        tmp->next = node;

        node->next = NULL;
        node = next_pair;

    }
}

list *swap_every_second_node(list *node) {
    list *tmp = NULL;

    if (!node)
        return NULL;

    if (!node->next)
        return node;

    tmp = node->next;
    node->next = swap_every_second_node(node->next->next);
    tmp->next = node;

    return tmp;
}

void move_last_to_front(list **head) {
    list *front_node = NULL;
    list *second_last = *head;

    if (!(*head)->next)
        return;

    while (second_last->next->next) {
        second_last = second_last->next;

    }

    // Last node becomes the first node
    front_node = second_last->next;
    // Second last node becomes the last node
    second_last->next = NULL;

    front_node->next = *head;
    *head = front_node;
}

void swap_alternate_nodes(list *l1_head, list *l2_head, list **new_l2_head) {
    list *tmp1;
    list *tmp2;
    

    while (l1_head && l2_head) {
        tmp1 = l1_head->next;
        tmp2 = l2_head->next;

        l1_head->next = l2_head;
        l2_head->next = tmp1;

        l1_head = tmp1;
        l2_head = tmp2;
    }


}

void print_inorder(tree *root) {
    if (!root)
        return;

    print_inorder(root->left);
    printf("%d ", root->data);
    print_inorder(root->right);

}

tree *create_bst(list *head, int lo, int hi) {
    tree *node = malloc(sizeof(tree));
    list *lnode;
    int mid = (lo + hi) / 2;

    if (lo > hi)
        return NULL;

    node->left = create_bst(head, lo, mid - 1);
    if (node->left && node->left->cur_head) {
        // Interior nodes comes here
        node->data = node->left->cur_head->a;
        head = node->left->cur_head->next;
    } else {
        // Only leaves will execute this part
        node->data = head->a;
        head = head->next;
    }
    node->cur_head = head;
    node->right = create_bst(head, mid + 1, hi);

    // Here update the current root with the new cur_head
    if (node->right && node->right->cur_head)
        node->cur_head = node->right->cur_head;

    return node;
}

void create_loop(list *head) {
    list *node1 = NULL;
    list *node = head;

    while (node) {
        if (node->a == 27) {
            node1 = node;
        }

        if (node1 && node->a == 10) {
            node->next = node1;
            return;
        }
        node = node->next;
    }
}

int hasLoop(list *head) {
    list *fp = NULL;
    list *cp = head;
    list *tmp_node = NULL;

    if (!head)
        return 0;

    if (cp && cp->next) 
        fp = cp->next->next;
    else
        return 0;

    while (fp != cp) {
        // If the fast pointer has reached the end means
        // we dont have a loop
        if (!fp)
            return 0;

        if (fp && fp->next) {
            tmp_node = fp;
            fp = fp->next->next;
        } else {
            return 0;
        }

        printf("Looping :(\n");
        cp = cp->next;
    }

    if (fp == cp) {
        tmp_node->next->next = NULL;
        printf("Loop detection at %d", fp->a);
    }

    return 1;
}

void reverse_k_nodes(list **head, int node_idx) {
    int i = 0;
    list *node = *head;
    list *rem_node = NULL;
    list *init_head = *head;
    while (node->next && i != node_idx - 1) {
        node = node->next;
        i++;
    }

    rem_node = node->next;
    node->next = NULL;
    iterative_reverse(head);
    init_head->next = rem_node;
}

list *recursive_reverse(list *node, list **head) {
    list *tmp_node = NULL;
    if (node->next) {
        tmp_node = recursive_reverse(node->next, head);
        tmp_node->next = node;
    } else {
        *head = node;
    }
    return node;
}

void iterative_reverse(list **head) {
    list *prev = NULL;
    list *cur  = *head;
    list *next = NULL;

    if (!(*head) || !(*head)->next) 
        return;

    next = cur->next;

    while (cur->next) {
        cur->next = prev;
        prev = cur;
        cur = next;
        next = cur->next;
    }
    cur->next = prev;
    *head = cur;
}

void print_list(list *head) {
    if (!head)
        return;

    while (head) {
        printf("%d ", head->a);
        head = head->next;
    }

}

void insert_list(list **head, list **tail, int a) {
    list *node = malloc(sizeof(list));
    if (!*head) {
        node->a = a;
        node->next = NULL;
        (*head) = node;
        (*tail) = node;
        return;
    }

    node->a = a;
    node->next = NULL;
    (*tail)->next = node;
    (*tail) = node;
    return;
}

void delete_node(list *node) {
    list *delete_node = NULL;
    if (!node->next)
        return;

    delete_node = node->next;
    memcpy(node, delete_node, sizeof(list));
    node->next = delete_node->next;
    free(delete_node);
}
