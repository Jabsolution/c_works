#include <stdio.h>
#include <stdlib.h>

typedef struct _trie {
    char c;
    int val;
    struct _trie *children[26];
} trie;

typedef struct _trieRoot {
    trie *next;
} trieRoot;

void addToTrie(trieRoot **, char *, int);
void print_trie(trieRoot *);
int isMember(trieRoot *, char *);
trie *search(trieRoot *, char *);
void print_words_starts_with(trieRoot *, char *);
void recursive_print(trie *);
trie *createNode(char *, int);

int main() {
    trieRoot *rt = malloc(sizeof(trieRoot));
    rt->next = NULL;

    addToTrie(&rt, "amy", 56);
    addToTrie(&rt, "ann", 15);
    addToTrie(&rt, "emma", 30);
    addToTrie(&rt, "emra", 30);
    addToTrie(&rt, "rob", 27);
    addToTrie(&rt, "roger", 52);

    //isMember(rt, "roger");
    isMember(rt, "roger");
    print_words_starts_with(rt, "em");

}

void print_words_starts_with(trieRoot *rt, char *str) {
    int i = 0;
    trie *node = NULL;

    if ((node =search(rt, str))) {
        recursive_print(node);
    } else {
        printf("None");
    }
}

void recursive_print(trie *node) {
    int i = 0;

    if (!node) 
        return;

    for (i = 0; i < 26; i++) {
        if (node->children[i]) {
            printf("%c",node->children[i]->c);
            recursive_print(node->children[i]);
        }
    }

}

trie *search(trieRoot *rt, char *str) {
    int i = 0;
    trie *node = rt->next;

    if (node && node->children[str[0] - 'a']) {
        node = node->children[str[0] - 'a'];
    } else {
        return NULL;
    }

    while (str[i] != '\0') {
        if (node->c == str[i]) {
            i++;
        } else if (node && node->children[str[i] - 'a']) {
            node = node->children[str[i] - 'a'];
        } else {
            return NULL;
        }
    }

    if (!str[i]) {
        printf("Node value: %d", node->val);
    }

    return node;

}

int isMember(trieRoot *rt, char *str) {

    if (search(rt, str)) {
        return 1;
    }

    return 0;
}

void addToTrie(trieRoot **rt, char *str, int val) {
    trie *node = NULL;
    trie *next = NULL;
    int i = 0;
    int prevChar = 0;

    if (!str) {
        return;
    }

    // The trie is empty
    if (!(*rt)->next) {
        node = malloc(sizeof(trie));
        node->c = 0;
        node->children[str[0] - 'a']= createNode(&str[0], val);
        (*rt)->next = node;
    } else {
        node = (*rt)->next;
        if (!node->children[str[0] - 'a']) {
            node->children[str[0] - 'a'] = createNode(&str[0], val);
        } else {
            node = node->children[str[0] - 'a'];
            while (str[i] != '\0') { 
                if (node && (node->c == str[i])) {
                    i++;
                } else if (node->children[str[i] - 'a']) {
                    node = node->children[str[i] - 'a'];
                } else {
                    node->children[str[i] - 'a'] = createNode(&str[i], val);
                    break;
                }
            }
        }
    }
}

trie *createNode(char *str, int val) {
    trie *node = NULL;
    trie *prevNode = NULL;
    trie *rt_node = NULL;
    int i = 0;
    int prevChar = 0;

    /*           |
     *           0
     *        [a....]
     *         /
     *        0
     *     [.b...]
     *       /
     *      10
     *  [..c..]
     *     /
     *  NULL
     *      
     */
    while (*str != '\0') {
        node = malloc(sizeof(trie));

        // Save the initial node
        if (!rt_node) {
            rt_node = node;
        }
        node->c = *str;
        node->val = 0;
        for (i = 0; i < 26; i++) {
            node->children[i] = NULL;
        }
        if (prevNode) {
            prevNode->children[*str - 'a'] = node;
        }
        prevNode = node;
        str++;
    }
    if (!*str) {
        node->val = val;
    }

    return rt_node;
}
