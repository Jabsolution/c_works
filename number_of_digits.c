#include <stdio.h>
#include <stdlib.h>

int main() {
    int given_number = 0;
    int number = 0;
    int i = 0;
    int rem = 0;
    int nines = 0;
    int total = 0;

    scanf("%d", &given_number);
    scanf("%d", &number);

    rem = number % 10;
    number = number / 10; // How many at ten's place
    total += number;

    if (number > given_number) {
        total += 9;

        if (rem >= given_number) 
            total += 1;

    } else if (number == given_number) {
        total += rem + 1;

        if (rem >= given_number) 
            total += 1;
    }

    printf("Total for %d\n", total);

}
