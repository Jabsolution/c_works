#include <stdio.h>
#include <stdlib.h>

typedef enum COLOR = {BLACK, RED};

typedef struct _node {
    int val;
    COLOR color;
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} node;

node *grandparent(node *);
node *uncle(node *);
node *right_rotate(node *, node *);
node *left_rotate(node *, node *);

int main() {

}

void insert(node *head, node *n) {
    node *u = NULL;
    /*
     * When !head
     */
    if (!head) {
        n->color = BLACK;
        head = n;
        return;
    }
    if (n->parent == BLACK) {

    } else if (n->parent == RED) {

    }

    u = uncle(n);

    if (u && u->color == RED) {

    } else if (u && u->color == BLACK) {

    } else {
        /*
         * No uncle
         */

    }
}

node *right_rotate(node *head, node *g) {
    /*  [head] if(!g->parent) 
     *  [g.parent, g->parent->left, g->parent->right]
     *  [p.parent, p->right, p->right->parent]
     *
     *           |
     *           g                        p
     *        /     \                  /     \
     *      p        u      ------>  p.l      g 
     *    /  \     /   \                    /   \
     *  p.l  p.r  u.l  u.r                p.r    u
     *                                         /  \
     *                                       u.l  u.r
     *
     */                                       
    node *p = NULL;
    if (!head || !g || !g->left)
        return NULL;

    p = g->left;
    g->left = p->right;

    if (p->right)
        p->right->parent = g;

    p->parent = g->parent;

    if (!g->parent) 
        head = p;
    else if (g->parent->left == g)
        g->parent->left = p;
    else
        g->parent-right = p;

    p->right = g;
    g->parent = p;

    return p;
}

node *left_rotate(node *head, node *n) {
    node *p = NULL;

    if (!head || !g || !g->right)
        return NULL;

    p = g->right;
    p->right = g->left;

    if (g->left) {
        g->left->parent = p;

    p->parent = g->parent;
    
    if (!g->parent)
        head = p;
    else if (g->parent->left == g) 
        g->parent->left = p;
    else
        g->parent->right = p;

    g->left = p;
    p->parent = g;

    return p;
}

node *grandparent(node *n) {
    if (!n || !n->parent)
        return NULL;
    if (n->parent) {
        return n->parent->parent;
    }
}

node *uncle(node *n) {
    node *g = grandparent(n);
    if (!g)
        return NULL;
    if (n->parent == g->left)
        return g->right;
    else 
        return g->left;
}

void rb_insert(tree *t, node n) {
    tree_insert(t, x);

    x->color = red;
    while ((x != t->root) && (x->parent->color == red)) {
        /*
         * If x's parent is a left, y is x's right 'uncle'
         */
    }

}
