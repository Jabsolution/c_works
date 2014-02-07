#include <stdio.h>
#include <stdlib.h>

void print_para(int, int, char *, int);

int main() {
    int right_para = 3;
    int left_para = 3;
    char str[3+3] = {""};
    int count = 0;

    print_para(left_para, right_para, str, count);    
}

void print_para(int left_para, int right_para, char *str, int count) {
    if (left_para < 0 || left_para > right_para) 
        return;
    if (!left_para && !right_para) {
        printf("%s\n", str);
    }
    else {
        if (left_para > 0) {
            str[count] = '(';
            print_para(left_para-1, right_para, str, count+1);
        }
        if (right_para > left_para) {
            str[count] = ')';
            print_para(left_para, right_para-1, str, count+1);
        }
    }
}

