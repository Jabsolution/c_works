#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    int exponent = 0;
    int number = 0;
    int digit = 0;
    int total = 0;
    int rem = 0;
    int msb = 0;
    int tens = 0;
    int hundred = 0;
    int no_of_digits = 20;

    scanf("%d", &number);
    scanf("%d", &digit);

    // Count number of tens
    while (number) {
        exponent = (int)log10(number);
        tens = (int)pow(10, exponent);
        hundred = tens / 100;
        msb = number / tens;
        rem = number % tens;

        printf("%d %d", msb, rem);
        if (hundred) {
            total += (hundred * msb * no_of_digits); 
        } else if (tens == 10) {
            total += msb;
        }
    
        if (msb > digit) {
            total += tens;
        } else if (msb == digit) {
            total += rem + 1;
        } 

        printf(" %d \n", total);
        number = rem;
    }

    printf("%d", total);

}

