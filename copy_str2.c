#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[] = "Mr John Smith    ";
    int len = 0;
    int i = 0;
    int k = 0;
    int j = len;
    int space_count = 0;
    int new_len = 0;

    /*
     * Find str length
     */
    len = sizeof(str) / sizeof(char);
    printf("Size: %d", len);

    while (str[i] != '\0') {
        if (str[i] == ' ') {
            space_count++;
            new_len += (space_count * 2);
            if (new_len > len) {
                space_count--;
                new_len -= 2;
                break;
            }
        }
        i++;
    }
    printf("New_len: %d", new_len);
    printf("Original len: %d", len);
            
}
            
            
