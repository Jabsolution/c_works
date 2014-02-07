#include <stdio.h>
#include <stdlib.h>

void permute_str(char *str, int count);

int main() {
    char str[] = {"abc"};
    int count = 1;
    permute_str(str, count);
}

void permute_str(char *str, int count) {
    char temp_char;
    if (!str[count]) 
        return;
    permute_str(str, count + 1);
    printf("%s", str);
    return;
    while(str[count + 1]) {
        temp_char = str[count];
        str[count] = str[count + 1];
        str[count + 1] = temp_char;
        permute_str(str, count + 1);
    }
    return;
}

