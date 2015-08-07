#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void roman_to_int(int *, char *);
char *int_to_roman(int *, int);
void str_rev(char *, int);

int main() {
    char *val = "MMCDXX";
    int int_val = 3333;
    char *roman_str = NULL;
    int i = 0;
    int total = 0;
    int prevChar = 0;
    int letters[26];
    letters['I' - 65] = 1;
    letters['V' - 65] = 5;
    letters['X' - 65] = 10;
    letters['L' - 65] = 50;
    letters['C' - 65] = 100;
    letters['D' - 65] = 500;
    letters['M' - 65] = 1000;

    roman_to_int(letters, val);
    roman_str = int_to_roman(letters, int_val);

}

char *int_to_roman(int *letters, int val) {
    char *roman_chars = "IVXLCDM";
    char *ret_str = malloc(sizeof(char) * 256);
    int i = 0;
    int r = 0;
    int q = 0;
    int prevChar = 0;
    int str_idx = 0;

    while (val) {
        for (i = 0; roman_chars[i] != '\0'; i++) {
            if (val > letters['M' - 65]) {
                q = val / letters['M' - 65];
                r = val % letters['M' - 65];
                prevChar = 'M';
            } else if (val < letters[roman_chars[i] - 65]) {
                q = val / letters[prevChar - 65];
                r = val % letters[prevChar - 65];
            } else {
                prevChar = roman_chars[i];
                continue;
            }

            val = r;
            if (q) {
                if (q == 4) {
                    ret_str[str_idx++] = prevChar;
                    ret_str[str_idx++] = roman_chars[i];
                } else {
                    while (q) {
                        ret_str[str_idx++] = prevChar;
                        q--;
                    }
                }
            } else if (r == 4) {
                ret_str[str_idx++] = prevChar;
                ret_str[str_idx++] = roman_chars[i];
            } 
            break;
        }
    }

    ret_str[str_idx] = '\0';
    printf("Str %s", ret_str);

    return NULL;

}

void str_rev(char *str, int len) {
    int tmp = 0;
    char *s_ptr = &str[0];
    char *e_ptr = &str[len - 1];

    while (s_ptr <= e_ptr) {
        tmp = *s_ptr;
        *s_ptr = *e_ptr;
        *e_ptr = tmp;
        s_ptr++;
        e_ptr--;
    }

}

void roman_to_int(int *letters, char *val) {
    int i = 0;
    int total = 0;
    int prevChar = 0;

    for (i = 0; val[i] != '\0'; i++) {
        if (prevChar && letters[prevChar - 65] < letters[val[i] - 65]) {
            total -= letters[prevChar - 65];
            total += letters[val[i] - 65] - letters[prevChar - 65];
        } else {
            total += letters[val[i] - 65];
        }
        prevChar = val[i];
    }
    printf("Total %d", total);

}

