#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _chain {
    int row;
    int col;
    int **mat;
    struct _chain *next;
} chain;

int **get_matrix(int, int);
int getdigit(int, int);
void print_list(chain *);
void insert_to_list(chain **, chain **, int **, int, int);
chain *create_node(int **, int, int);
void add_digit(int **, int, int);

int main() {
    int c = 0;
    int row = 0;
    int col = 0;
    int tmp = 0;
    int i = 0;
    int j = 0;
    int **ms_array = NULL;
    int **ms_list = NULL; // Holds different minesweeper geometries
    chain *head = NULL;
    chain *tail = NULL;

    while ((c = getchar()) != EOF) {
        if ((c != '\n') && (c != ' ') && (c >= '0' && c <= '9')) {
                tmp = getdigit(tmp, c - '0');
                continue;
        }
        if (c == ' ') {
            row = tmp;
            if (!tmp)
                break;
            tmp = 0;
        } else if(c == '\n' && tmp) {
            col = tmp;
            ms_array = get_matrix(row, col);
            insert_to_list(&head, &tail, ms_array, row, col);

            // reset ms_array indices once we get row & col.
            i = 0;
            j = 0;

            continue;
        }
        tmp = 0;

        /*
         * Once we have row and col, we start reading lines and fomr the
         * minesweeper geometry
         */
        if (c == '\n' || c == '.' || c == '*') {
            if (c == '\n') {
                j = 0;
                i++;
                continue;
            }
            if (i < row && j < col) {
                ms_array[i][j++] = c;
            } else {
                break;
            }
        }
    }
    print_list(head);
}

void print_list(chain *head) {
    int i = 0;
    int j = 0;
    chain *node = head;

    while (head) {
        for (i = 0; i < head->row; i++) {
            for (j = 0; j < head->col; j++) {
                if (head->mat[i][j] == '*') {
                    if (j > 0 
                        && j < head->col - 1 
                        && i > 0 
                        && i < head->row - 1) {
                        /*      
                         *  * * *
                         *   \|/
                         *  *-*-*
                         *   /|\
                         *  * * *
                         */

                        add_digit(head->mat, i + 1, j);
                        add_digit(head->mat, i + 1, j + 1);
                        add_digit(head->mat, i + 1, j - 1);

                        add_digit(head->mat, i, j + 1);
                        add_digit(head->mat, i, j - 1);

                        add_digit(head->mat, i - 1, j);
                        add_digit(head->mat, i - 1, j + 1);
                        add_digit(head->mat, i - 1, j - 1);
                    } else if (j == 0) {
                        if (i == head->row - 1) {
                            /*
                            * *-*
                            * |\
                            * * *
                            */
                            add_digit(head->mat, i, j + 1);
                            add_digit(head->mat, i - 1, j + 1);
                            add_digit(head->mat, i - 1, j);
                        } else if (i == 0) {
                           /*
                            * * *
                            * |/
                            * *-*
                            *   *
                            *   |
                            * *-*-*
                            *
                            */
                            add_digit(head->mat, i, j + 1);
                            add_digit(head->mat, i + 1, j);
                            add_digit(head->mat, i + 1, j + 1);
                        } else {
                           /* 
                            * * *
                            * |/
                            * *-*
                            * |\
                            * * *
                            */
                            add_digit(head->mat, i, j + 1);
                            add_digit(head->mat, i + 1, j);
                            add_digit(head->mat, i + 1, j + 1);
                            add_digit(head->mat, i - 1, j);
                            add_digit(head->mat, i - 1, j + 1);
                        }
                    } else if (j == head->col - 1 ) {
                        add_digit(head->mat, i, j - 1);
                        if (i == head->row - 1) {
                            /*
                             *  *-*
                             *   /|
                             *  * *
                             */
                            add_digit(head->mat, i - 1, j);
                            add_digit(head->mat, i - 1, j - 1);
                        } else if (i == 0) {
                            /*
                             *  * *
                             *   \|
                             *  *-*
                             */
                            add_digit(head->mat, i + 1, j);
                            add_digit(head->mat, i + 1, j - 1);
                        } else {
                           /*    
                            *  * *
                            *   \|
                            *  *-*
                            *   /|
                            *  * *
                            */
                            add_digit(head->mat, i + 1, j);
                            add_digit(head->mat, i + 1, j - 1);
                            add_digit(head->mat, i - 1, j);
                            add_digit(head->mat, i - 1, j - 1);
                        }
                    } else if (j > 0 && j < head->col - 1) {
                        /*    
                        *  * * *  
                        *   \|/
                        *  *-*-*
                        *
                        */
                        add_digit(head->mat, i, j - 1);
                        add_digit(head->mat, i, j + 1);
                        if (i == 0) {
                            add_digit(head->mat, i + 1, j);
                            add_digit(head->mat, i + 1, j + 1);
                            add_digit(head->mat, i + 1, j - 1);
                        } else {
                            /*
                            * *-*-*
                            *  /|\
                            * * * *
                            *
                            */
                            add_digit(head->mat, i - 1, j);
                            add_digit(head->mat, i - 1, j - 1);
                            add_digit(head->mat, i - 1, j + 1);
                        }                    
                    }
                } else if (head->mat[i][j] == '.') {
                    head->mat[i][j] = '0' - '0';
                }
            }
        }
        head = head->next;
    }

    /*
     * Once we formed the matrix with digits, let's print 
     *
     */
    while(node) {
        for(i = 0; i < node->row; i++) {
            for(j = 0; j < node->col; j++) {
                if (node->mat[i][j] == '*') {
                    printf("%c", node->mat[i][j]);
                } else {
                    printf("%d", node->mat[i][j]);
                }
            }
            printf("\n");
        }
        node = node->next;
    }
}

void add_digit(int **mat, int row, int col) {
    if (mat[row][col] != '*') {
        if (mat[row][col] == '.') {
            mat[row][col] = '0' - '0';
        }
        mat[row][col]++;
    }
}

void insert_to_list(chain **head, chain **tail, int **new_node, int row,
                    int col) {
    chain *node = NULL;

    node = create_node(new_node, row, col);
    if (!(*head)) {
        (*head) = node;
        (*tail) = node;
        return;
    }

    (*tail)->next = node;
    (*tail) = node;
    return;
}

chain *create_node(int **new_node, int row, int col) {
    chain *node = NULL;

    node = (chain *)malloc(sizeof(chain));
    node->row = row;
    node->col = col;
    node->mat = new_node;
    node->next = NULL;

    return node;
}

int getdigit(int val, int next_val) {
    int base = 10;

    val = val * 10 + next_val;
    return val;
}

int **get_matrix(int a, int b) {
    int i = 0;
    int j = 0;
    int **mat = NULL;

    mat = (int **)malloc(a * sizeof(int *));

    for (i = 0; i < a; i++) {
        mat[i] = (int *)malloc(b * sizeof(int));
    }
    return mat;
}


