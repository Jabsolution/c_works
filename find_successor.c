#include <stdio.h>
#include <stdlib.h>

int main() {

}

tree *find_successor(tree *node) {
    if (!node)
        return NULL;

    if (node->right)
        return find_minimum(node->right);

    while (node->parent && node->parent->right == node) {
        node = node->parent;
    }
    return node->parent;
}

tree *find_minimum(tree *node) {
    while (node->left) 
        node = node->left;
    return node;
}

