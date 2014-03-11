/*
 * Project Eular: Problem - 5
 *
 *
 * 2520 is the smallest number that can be divided by each of the 
 * numbers from 1 to 10 without any remainder.
 *
 * What is the smallest positive number that is evenly divisible by all of 
 * the numbers from 1 to 20?
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
void print_smallest_multiple(int no);

int main() {
    int no = 20;
    print_smallest_multiple(no);
}

void print_smallest_multiple(int no) {
    int i = 0;
    int tmp = 0;

    for (i = no;; i++) {
        tmp = no;
        while (tmp != 1) {
            if (!(i % tmp)) {
                tmp--;
            } else {
                break;
            }
        }
        if (tmp == 1) {
             printf("Largest number: %d", i);
             break;
        }
    }
}
