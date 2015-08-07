#include <stdio.h>
#include <stdlib.h>

int main() {

}

tree *get_common_ancestor(tree *root, tree *a, tree *b) {
    tree *x = NULL;
    tree *y = NULL;

    if (!root)
        return NULL;
    if (root == a && root == b)
        return root;

    x = get_common_ancestor(root->left, p, q);
    if (x != NULL && x != p && x != q)
        return x;

    y = get_common_ancestor(root->right, p, q);
    if (y != NULL && y != p && y != q)
        return y;

    if (x != NULL && y != NULL)
        return root;
    if (root == x || root == y)
        return root;
    return (!x) ? y : x;
}


