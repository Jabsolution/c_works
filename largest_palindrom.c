/*
 * Project Eular: Problem - 4
 *
 * A palindromic number reads the same both ways. The largest palindrome 
 * made from the product of two 2-digit numbers is 9009 = 91 × 99.
 *
 * Find the largest palindrome made from the product of two 3-digit numbers.
 *
 */
#include <stdio.h>
#include <stdlib.h>

void show_product(int);

int main() {
    int a = 111;
    show_product(a);
}

void show_product(int a) {
    int i = 0;
    int product = 0;
    int remainder = 0;
    int number = 0;
    int tmp = 0;
    int quo = 0;
    int largest_palin = 0;

    for (; a <= 999; a++) {
        for (i = a; i <= 999; i++, number = 0) {
            product = a * i;
            quo = product;
           // printf("Prod: %d", product);

            while (quo) {
                //printf("\nquo: %d", quo);
                remainder = quo % 10;
               // printf("\nremainder: %d", remainder);
                number = number * 10 + remainder;
                quo = quo / 10;
            }
            if (number == product) {
                if (largest_palin < number)
                    largest_palin = number;
                printf("Palindrom: %d\n", largest_palin);
            }
        }
    }
}
