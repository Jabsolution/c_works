// Jay Desai //
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 512

typedef struct _table_info {
    char read;
    char write;
    int direction;
    int new_state;
    struct _table_info *next;
} table_info;
    
typedef struct _action_tbl {
    table_info *state_info_head;
    table_info *state_info_tail;
} action_tbl;

void read_state_machine(char *, action_tbl **, char **, int *, int *, int *);
void insert(table_info **, table_info **, table_info *);
int run(char *, int, int, int, action_tbl *);
void chomp_new_line(char *, int *);
int get_total_bytes(char *);
void free_state_machine(action_tbl *, int);

int main(int argc, char **argv) {
    action_tbl *tbl = NULL;
    char *file_name = NULL;
    file_name = argv[1];
    char *tape = NULL;
    int head_offset = 0;
    int start_idx = 0;
    int halt_idx = 0;
    int ret_code = 0;

    if (!file_name) {
        printf("Please provide a file\n");
        exit(1);
    }

    read_state_machine(file_name, &tbl, &tape, &head_offset, &start_idx, &halt_idx);
    ret_code = run(tape, head_offset, start_idx, halt_idx, tbl);
    free_state_machine(tbl, halt_idx);

    if (!ret_code) // Failure
        exit(1);
    else
        exit(0);
}

void free_state_machine(action_tbl *tbl, int halt_idx) {
    table_info *tbl_info = NULL;
    table_info *tmp = NULL;
    int index = 0;

    if(!tbl)
        return;

    while (index < halt_idx) {
        tbl_info = tbl[index].state_info_head;
        while (tbl_info) {
            tmp = tbl_info;
            tbl_info = tbl_info->next;
            free(tmp);
        }
        tbl[index].state_info_head = NULL;
        tbl[index].state_info_tail = NULL;
        index += 1;
    }
    free(tbl);
}

int run(char *tape, int head_offset, int start_idx, int halt_idx, action_tbl *tbl) {
    int index = start_idx;
    table_info *tbl_info = NULL;
    char *st_str = NULL;
    st_str = tape;

    if (*tape == '\0')
        return 0;

    printf("%s \n", tape);
    tape += start_idx + head_offset;

    while (*tape != '\0') {
        // If we reach the halt state then return //
        if (index == halt_idx) {
            printf("%s", st_str);
            return 1;
        }

        tbl_info = tbl[index].state_info_head;

        while (tbl_info) {
            if (tbl_info->read == *tape || tbl_info->read == '*') {
                if (tbl_info->read != '*') {
                    // Write new content //
                    *tape = tbl_info->write;
                    printf("%s \n", st_str);
                } 

                // Which way to move //
                if (tbl_info->direction == 1) {
                    tape += 1;
                } else if (tbl_info->direction == -1) {
                    tape -= 1;
                }
                    
                // Go to next state //
                index = tbl_info->new_state;
                break;
            } 
            // Visit all possibilities for the current state
            tbl_info = tbl_info->next;
        }
        if (!tbl_info) {
            return 0;
        }
    }
    printf("%s", st_str);

    return 1;
}

void read_state_machine(char *file_name, action_tbl **tbl, char **tape, 
                        int *head_offset, int *start_idx, int *halt_idx) {
    FILE *fp = NULL;
    char *mode = "r";
    char match_str[LINE_SIZE];
    char *lines = NULL;
    char *line = NULL;
    int i = 0;
    int size = 0;
    char *str = NULL;
    int prevState = 0;
    char *tmp = NULL;
    int st_idx = 0;
    int total_bytes = 0;
    int file_offset = 0;

    table_info *tbl_info = NULL;
   
    fp = fopen(file_name, mode);

    /* Tape Information */
    fgets(match_str, LINE_SIZE, fp);
    chomp_new_line(match_str, &size);
    *tape = malloc(sizeof(char) * size);
    strncpy(*tape, match_str, size);
    
    file_offset = ftell(fp);
    fseek(fp, 0, SEEK_END);
    total_bytes = ftell(fp);
    total_bytes -= file_offset;
    fseek(fp, file_offset, SEEK_SET);
    lines = malloc(sizeof(char) * total_bytes);
    fread(lines, 1, total_bytes, fp);

    line = strtok(lines, "\n");

    // Offset //
    *head_offset = atoi(line);

    // Start Index // 
    line = strtok(NULL, "\n");
    *start_idx = atoi(line);

    // Halt Index //
    line = strtok(NULL, "\n");
    *halt_idx = atoi(line);

    *tbl = malloc(sizeof(action_tbl) * (*halt_idx));
    (*tbl)[0].state_info_head = NULL;
    (*tbl)[0].state_info_tail = NULL;

    line = strtok(NULL, "\n");
    
    while (line) {
        st_idx = 0;
        if (!strcmp(line, "\n")) {
            break;
        }
                
        total_bytes = get_total_bytes(line);
        tmp = malloc(sizeof(char) * total_bytes + 1);
        strncpy(tmp, line, total_bytes);
        i = atoi(tmp);
        free(tmp);
        
        if (prevState != i) {
            (*tbl)[i].state_info_head = NULL;
            (*tbl)[i].state_info_tail = NULL;
        }
        prevState = i;

        tbl_info = malloc(sizeof(table_info));

        st_idx += total_bytes + 1;
        strncpy(&tbl_info->read, &line[st_idx], 1);

        st_idx += 2;
        strncpy(&tbl_info->write, &line[st_idx], 1);
        
        st_idx += 2;
        total_bytes = get_total_bytes(&line[st_idx]);
        tmp = malloc(sizeof(char) * total_bytes);
        strncpy(tmp, &line[st_idx], total_bytes);
        tbl_info->direction = atoi(tmp);
        free(tmp);
        
        st_idx += total_bytes + 1;
        total_bytes = get_total_bytes(&line[st_idx]);
        tmp = malloc(sizeof(char) * total_bytes);
        strncpy(tmp, &line[st_idx], total_bytes);
        tbl_info->new_state = atoi(tmp);
        tbl_info->next = NULL;
        insert(&((*tbl)[i].state_info_head), &((*tbl)[i].state_info_tail), tbl_info);
        free(tmp);
        
        line = strtok(NULL, "\n");
    }
}

int get_total_bytes(char *line) {
    int total_bytes = 0;
    while (*line != '\0') {
        if (*line == ' ')
            break;
        total_bytes += 1;
        line += 1;
    }
    return total_bytes;
}

void insert(table_info **st_info_head, table_info **st_info_tail, table_info *tbl_info) {
    if (!tbl_info)
        return;

    if (!*st_info_head) {
        *st_info_head = tbl_info;
    } else {
        (*st_info_tail)->next = tbl_info;
    }
    *st_info_tail = tbl_info;
}

void chomp_new_line(char *str, int *str_len) {
    int len = 0;
    while (*str != '\0') {
        if (*str == '\n') {
            *str = '\0';
            *str_len = len + 1;
            return;
        }
        len += 1;
        str++;
    }
}
