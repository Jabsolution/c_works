#include <stdio.h>

void get_path(int (*)[]);

int main() {
    int name[2][2] = {1, 2, 4, 5};
    get_path(name);
}
void get_path(int (*name)[2]) {
    printf("%d", name[0][1]);
}
