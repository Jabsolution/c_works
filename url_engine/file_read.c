#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINE_SIZE 18

typedef struct _table_info {
    int start_state;
    char read;
    char write;
    int direction;
    int next_state;
} table_info;

table_info tbl_info;
void chomp_new_line(char *, int *);
void print_fields(char *);
int get_total_bytes(char *);

int main() {
    FILE *fp = NULL;
    char *line1 = NULL;
    char *lines = NULL;
    char line[LINE_SIZE];
    int len = 0;
    char *tap = NULL;
    int offset = 0;
    int st_index = 0;
    int halt_index = 0;
    char *st_info = NULL;
    int read = 0;
    int file_offset = 0;
    int total_bytes = 0;

    fp = fopen("file.txt", "r");
    fgets(line, 10, fp);
    chomp_new_line(line, &len);
    tap = malloc(sizeof(char) * len);
    strncpy(tap, line, len);
    printf("Tape: %s\n", tap);

    fgets(line, 10, fp);
    offset = atoi(line);
    printf("Offset: %d\n", offset);

    fgets(line, 10, fp);
    st_index = atoi(line);
    printf("Start Index: %d\n", st_index);

    fgets(line, 10, fp);
    halt_index = atoi(line);
    printf("Halt Index: %d\n", halt_index);

    file_offset = ftell(fp);
    fseek(fp, 0, SEEK_END);
    total_bytes = ftell(fp);
    total_bytes = total_bytes - file_offset;
    fseek(fp, file_offset, SEEK_SET);
    lines = malloc(sizeof(char) * total_bytes);
    fread(lines, 1, total_bytes, fp);
    printf("%s ", lines);

    line1 = strtok(lines, "\n");
    while (line1) {
        print_fields(line1);
        line1 = strtok(NULL, "\n");
    }

}

void print_fields(char *line) {
    char *line_char = NULL;
    char *tmp = NULL;
    int st_idx = 0;
    int total_bytes = 0;

    printf("%s ", line);

    total_bytes = get_total_bytes(line);
    tmp = malloc(sizeof(char) * total_bytes + 1);
    strncpy(tmp, line, total_bytes);
    tmp[total_bytes + 1] = '\0';
    tbl_info.start_state = atoi(tmp);
    free(tmp);

    st_idx += total_bytes + 1;
    total_bytes = get_total_bytes(&line[st_idx]);
    strncpy(&tbl_info.read, &line[st_idx], total_bytes);

    st_idx += total_bytes + 1;
    total_bytes = get_total_bytes(&line[st_idx]);
    strncpy(&tbl_info.write, &line[st_idx], total_bytes);

    st_idx += total_bytes + 1;
    total_bytes = get_total_bytes(&line[st_idx]);
    tmp = malloc(sizeof(char) * total_bytes + 1);
    tmp[total_bytes + 1] = '\0';
    tbl_info.direction = atoi(tmp);
    free(tmp);

    st_idx += total_bytes + 1;
    total_bytes = get_total_bytes(&line[st_idx]);
    tmp = malloc(sizeof(char) * total_bytes + 1);
    tmp[total_bytes + 1] = '\0';
    tbl_info.next_state = atoi(tmp);
    free(tmp);

    printf("new state: %d", tbl_info.start_state);
    printf("Read: %c", tbl_info.read);
}

int get_total_bytes(char *line) {
    int total_bytes = 0;
    while (*line != ' ') {
        total_bytes += 1;
        line += 1;
    }
    return total_bytes;
}

void chomp_new_line(char *str, int *str_len) {
    int len = 0;
    while (str) {
        if (*str == '\n') {
            *str = '\0';
            *str_len = len + 1;
            return;
        }
        str += 1;
        len += 1;
    }
}
