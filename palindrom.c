#include <stdio.h>
#include <stdlib.h>

int main() {
    int no = 141;
    int val = 0;
    int final_no = 0;
    int next_val = 0;
    int temp = 0;

    temp = no;
    while (no) {
        val = no % 10;
        next_val = no / 10;
        no = next_val;
        final_no = final_no * 10 + val;
    }

    printf("%d", final_no);
    if (final_no == temp) {
        printf("The number: %d is a palindrome number\n", temp);
    }
}

