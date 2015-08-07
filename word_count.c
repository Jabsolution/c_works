#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _word {
    char *str;
    int count;
    struct _word *left;
    struct _word *right;
} word_t_node;

typedef struct _word_count_node {
    word_t_node *word_ptr;
    struct _word_count_node *left;
    struct _word_count_node *right;
} word_count_node;

void insert_bintree(word_t_node **, char *);
void count_words(word_t_node *, char *);
word_t_node *create_node(char *);
word_count_node * create_word_count_node(word_t_node *node);
void print_bintree(word_t_node *);
void print_wc_bintree(word_count_node *);
void traverse_w_t_nodes(word_t_node *, word_count_node **);
void create_tree_by_wordcount(word_t_node *, word_count_node **);

int main() {
    char c;
    char word[1000] = {'\0'};
    int i = 0;
    word_t_node *root = NULL;
    word_count_node *root_wc = NULL;

    while ((c = getchar()) != EOF) {
        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) 
            word[i++] = c;
        /*
         * We only print words if we encounter a non-word character and 
         * word[] array has alphabetic characters. i.e. It's index i > 0.
         */
        if ((c == ' ' || c == '\n' || c == ',' || c == '.') && i > 0) {
            word[i] = '\0'; // End of word 
            insert_bintree(&root, word);
            i = 0; // Reset word index
        }
    }
    //print_bintree(root);
    /*
     * Word count tree nodes are pointers to the word tree nodes in such a way
     * that the resulting "word_count_tree" nodes forms a binary search tree 
     * order by word counts. 
     */
     traverse_w_t_nodes(root, &root_wc);
     print_wc_bintree(root_wc);
}

void create_tree_by_wordcount(word_t_node *node, word_count_node **root_wc) {
    word_count_node *tmp_wc_t_node = *root_wc;
    word_count_node *prevNode = NULL;

    if (!*root_wc) {
        *root_wc = create_word_count_node(node);
        return;
    }

    /*
     * We traverse the word_t_node in preorder and checking the word_t_node
     * count against the existing word_count_node 
     */
    
    while (tmp_wc_t_node) {
        prevNode = tmp_wc_t_node;
        if ((tmp_wc_t_node->word_ptr)->count > node->count) {
            tmp_wc_t_node = tmp_wc_t_node->left;
        } else {
            tmp_wc_t_node = tmp_wc_t_node->right;
        }
    }

    if ((prevNode->word_ptr)->count > node->count) {
        prevNode->left = create_word_count_node(node);
    } else {
        prevNode->right = create_word_count_node(node);
    }
}

word_count_node * create_word_count_node(word_t_node *node) {
    word_count_node *wc_node;

    wc_node = malloc(sizeof(word_count_node));
    wc_node->word_ptr = node;
    wc_node->left = NULL;
    wc_node->right = NULL;

    return wc_node;
}

void traverse_w_t_nodes(word_t_node *node, word_count_node **root) {
    if (!node)
        return;
    traverse_w_t_nodes(node->left, root);
    create_tree_by_wordcount(node, root);
    traverse_w_t_nodes(node->right, root);
}

void print_wc_bintree(word_count_node *node) {
    if (!node)
        return;
    print_wc_bintree(node->right);
    printf("%s: %d\n", (node->word_ptr)->str, (node->word_ptr)->count);
    print_wc_bintree(node->left);
}

void print_bintree(word_t_node *node) {
    if (!node)
        return;
    print_bintree(node->left);
    printf("%s %d", node->str, node->count);
    print_bintree(node->right);
}

void insert_bintree(word_t_node **root, char *str) {
    word_t_node *tmp_word;
    word_t_node *prevNode;

    if (!str) 
        return;

    if (!*root) {
        *root = create_node(str);
        return;
    }

    tmp_word = *root;
    while (tmp_word) {
        prevNode = tmp_word;
        if (strcmp(tmp_word->str, str) > 0) {
            // Go right
            tmp_word = tmp_word->right;
        } else if (strcmp(tmp_word->str, str) < 0) {
            // Go left
            tmp_word = tmp_word->left;
        } else {
            tmp_word->count++;
            return;
        }
    }

    if (strcmp(prevNode->str, str) > 0) {
        prevNode->right = create_node(str);
    } else {
        prevNode->left = create_node(str);
    }
}

word_t_node *create_node(char *str) {
    word_t_node *tmp_word;

    tmp_word = malloc(sizeof(word_t_node));
    tmp_word->str = malloc(sizeof(char)*1000);
    memcpy(tmp_word->str, str, sizeof(char)*1000);
    tmp_word->count = 1;
    tmp_word->left = NULL;
    tmp_word->right = NULL;

    return tmp_word;
}
