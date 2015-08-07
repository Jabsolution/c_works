#include <stdio.h>
#include <stdlib.h>

int main() {

}

tree *find_predecessor(tree *node) {
    if (!node)
        return NULL;

    if (node->left)
        return find_maximum(node->left);

    while (node->parent && node->parent->left == node) {
        node = node->parent;
    }
    return node->parent;
}

tree *find_maximum(tree *node) {
    while(node->right)
        node = node->right;
    return node;
}

