#include <stdio.h>
#include <stdlib.h>

tree *find_min(tree *);
tree *find_max(tree *);

int main() {

}

tree *find_min(tree *head) {
    if (!head)
        return NULL;

    if (head->left)
        return find_min(head->left);
    else
        return head;
}

tree *find_max(tree *head) {
    if (!head)
        return NULL;

    if (head->right) 
        return find_max(head->right);
    else
        return head;
}

