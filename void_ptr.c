#include <stdio.h>
#include <stdlib.h>

int main() {
    void *p;
    char *str;
    p = "jay";

    str = (char *)p;
    printf("The string is %s", str);
}


