#include <stdio.h>
#include <stdlib.h>

int main() {
    int no = 1000;
    int mul_of_three = 0;
    int mul_of_five = 0;
    int new_digit = 0;
    int i = 1;
    int j = 1;
    int k = 1;
    int subtract = 0;

    printf("Multiple of three: ");
    while ((new_digit = (3 * i)) < no) {
        mul_of_three += new_digit;
        printf("%d ", new_digit);
        i++;
    }
    new_digit = 0;
    printf("\nMultiple of five: ");
    while ((new_digit = (5 * j)) < no) {
        mul_of_five += new_digit;
        printf("%d ", new_digit);
        j++;
    }

    while ((new_digit = (3 * 5 * k)) < no) {
        subtract += new_digit;
        k++;
    }

    printf("\nTotal: %d\n", (mul_of_three + mul_of_five) - subtract);
}


