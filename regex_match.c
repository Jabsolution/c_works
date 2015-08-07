#include <stdio.h>
#include <stdlib.h>

int search_token(char *, int, char);

int main() {
    char *regex = "dup.com";
    char *str = "dup.com";
    int token_position = -1;
    int last_regex_pos = 0;
    int last_str_pos   = 0;
    int i = 0;
    int j = 0;
    int match = 0;
    int state = 0;

    /*
     * Initial states
     */
    if (regex[i] == '*')
        state = '*'; // Start matching
    else
        state = 'c'; // Start comparing 

    while (!match) {
        if (state == '0')
            break;
        switch(state) {
            case '*':
                i++;
                while (str[j] != '\0') {
                    j++;
                }
                if (regex[i] == '\0') {
                    match = 1;
                } else {
                    j--; // Not NULL
                    state = 's'; // Search for the token
                }
                break;
            case 's': // Search token
                token_position = search_token(str, j, regex[i]);
                /*
                 * Remember where we last matched
                 */ 
                last_regex_pos  = i;
                last_str_pos    = token_position;
                state = 'm';
                break;
            case 'm': // Match token
                j = token_position; // Start matching str at this position
                if (token_position != -1) {
                    while (regex[i] != '\0' && str[j] != '\0') {
                        if (regex[i] == str[j]) {
                            i++;
                            j++;
                        } else {
                            /*
                             * If non-match char is a metachar then we
                             * go to state '*' again
                             */
                            if (regex[i] == '*') {
                                state = '*';
                            } else {
                                i = last_regex_pos;
                                j = last_str_pos - 1;
                                token_position = -1; // Reset token pos
                                state = 's';
                            }
                            break;
                        }
                    }
                    // If regex and str matches then we say it's a MATCH
                    if (regex[i] == '\0' && str[j] == '\0') {
                        match = 1;
                    }
                } else {
                    match = 0;
                    state = '0';
                }
                break;
            case 'c':
                token_position = 0;
                state = 'm';
                break;
        }
    }
    if (match) 
        printf("Match");
    else
        printf("No Match");
}

int search_token(char *str, int j, char token) {
    while (j >= 0) {
        if (str[j] == token) {
            return j;
        }
        j--;
    }
    return -1;
}

