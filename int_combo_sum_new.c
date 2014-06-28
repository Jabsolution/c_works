#include <stdio.h>
#include <stdlib.h>

void print_combo_sum(int, int, char *);

int main() {
    int no = 7;
    char str[no + 1];
    print_combo_sum(no, 0, str);
}

void print_combo_sum(int val, int position, char *str) {
    int i = 2;

    // If number has become 1 then print all the values in str
    if (val == 1) {
        str[position] = '0' + 1;
        str[position + 1] = '\0';
        printf("%s\n", str);
        return;
    }

    if (val) {
        str[position] = '0' + 1;
        print_combo_sum(val - 1, position + 1, str);
        // Insert and print the actual value after recursion
        if (position) {
            str[position] = '0' + val;
            str[position + 1] = '\0';
            printf("%s\n", str);
        }
        // After all the recursions have ended print the remaining unique 
        // combination (No duplicates)
        while (i <= val/2) {
            str[position++] = '0' + i;
            str[position++] = '0' + (val - i);
            str[position] = '\0';
            printf("%s\n", str);
            i++;
            position -= 2;
        }
    }
}

