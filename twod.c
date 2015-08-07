#include <stdio.h>
#include <stdlib.h>

void test_array(int a[0][0]);

int main() {
    int a[2][6];

    test_array(&a[0]);
}
void test_array(int a[0][0]) {

}

