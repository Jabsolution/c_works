#include <stdio.h>
#include <stdlib.h>

typedef struct _State {
    char c;
    struct _State *out;
    struct _State *out1;
} State;

// Create a DFA or NFA from regex
State *compile_regex(char *);

// Match string against the compiled regex (State Machine)
int ismatch(State *, char *, int, int);
int get_regex_len(char *);


int main(int argc, char **argv) {
    char *regex = argv[1];
    char *str   = argv[2];
    int regex_l = get_regex_len(str);
    State *start = NULL;

    start = compile_regex(regex);
    printf("REGEX: %s\n", regex);
    printf("STRING: %s\n", str);
    if (ismatch(start, str, 0, regex_l)) 
        printf("Match\n");
    else
        printf("No Match\n");

}

int get_regex_len(char *regex) {
    int i = 0;

    for (;regex[i] != '\0'; i++)
        ;

    return i + 1;
}

int ismatch(State *start, char *str, int st_index, int len) {
    int i = st_index;
    State *tmp;
    State *prev_state;
    int l_match_char = 0;
    int one_or_more  = 0;

    if (!start)
        return 0;

    for (;str[i] != '\0'; i++) {
        if (start->out1 && (start->out1->c == '.' || start->out1->c == str[i]) ) {
            start = start->out1;
        } else if (start->out && (start->out->c == '.' || start->out->c == str[i])) {
            start = start->out;
        } 
    }

    if (str[i] == '\0') {
        if (!start->out->out) {
            return 1;
        } else {
            /*
             * We need to backtrack and match 
             */
            if (start->out->c == start->out1->c)
                one_or_more++;
            start = start->out;
            for(i = len - 2;i >= one_or_more; i--) {
                if (start->out && (start->out->c == str[i])) {
                    tmp          = start;
                    l_match_char = i;
                    start        = start->out;
                    i++;
                    while (start && str[i] != '\0') {
                        if (start->out && (start->out->c == str[i++])) {
                            start = start->out;
                        } else {
                            if (start->out && start->out->out1) {
                                /*
                                 * Found Greedy search. Do recursive matching
                                 */
                                if (!ismatch(start, str, i, len))
                                    return 0;
                                else 
                                    return 1;
                            }
                            break;
                        }
                    }

                    if (str[i] == '\0' && !start->out->out) {
                        return 1;
                    } else {
                        /*
                        * Start again where we left off
                        */
                        i = l_match_char;
                        start = tmp;
                    }
                }
            }


        }
    } 

    return 0;
}

State *compile_regex(char *regex) {
    State *st_state   = NULL;
    State *prev_state = NULL;
    State *start      = NULL;
    State *end        = NULL;
    State *cstate     = NULL;
    int i = 0;

    /*
     * Initialize start and end state
     */
    start = malloc(sizeof(State));
    start->c = '0';
    start->out = NULL;
    start->out1 = NULL;

    end = malloc(sizeof(State));
    end->c = '\0';
    end->out = NULL;
    end->out1 = NULL;

    prev_state = start;

    for(;regex[i] != '\0'; i++) {
        switch(regex[i]) {
            default:
                cstate = malloc(sizeof(State));
                cstate->c = regex[i];
                cstate->out = end;
                cstate->out1 = NULL;

                if (!start->out)
                    start->out = cstate;
                else
                    prev_state->out = cstate;

                prev_state = cstate;
                break;
            case '*':
                /*
                 * CASE 1:
                 *                - - 
                 *                | |
                 *                | |
                 *               \ /|
                 * --|start|----| . |-----|end|--
                 *            \         /
                 *             \-------/
                 *
                 * CASE: 2 
                 *                     - - 
                 *                     | |
                 *                     | |
                 *                    \ /|
                 * --|prev_state|----| . |-----|end|--
                 *                 \         /
                 *                  \-------/
                 */
                cstate->out1 = cstate;
                if (!start->out1)
                    start->out1 = end;
                else
                    prev_state->out1 = end;
                break;
            case '+':
                cstate->out1 = cstate;
                if (!start->out1)
                    start->out1 = cstate;
                else
                    prev_state->out1 = cstate;
                break;
        }
    }
    return start;
}

