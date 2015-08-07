#include <stdio.h>
#include <stdlib.h>

int main() {
    int coins[3] = {1, 3, 5};
    int sum = 11;
    int min[12] = {0};
    int i = 0;
    int j = 0;

    for (i = 1; i <= 11; i++) {
        for (j = 0; j < 3; j++) {
            if (coins[j] <= i) {
                min[i] = min[i - coins[j]] + 1;
            }
        }
    }
    for (i = 1; i <= 11; i++) {
        printf("min: %d\n", min[i]);
    }

}

