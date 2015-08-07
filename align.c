#include <stdio.h>
#include <stdlib.h>

typedef struct _align {
   char s1;
   char s2;
   char s3;
} align;

typedef struct _align2 {
    char ch1;
    short s;
    char ch2;
    long long ll;
    int i;
} align2;

int main() {
    int i = 0;
    align addr1;

    printf("addr %p\n", &addr1.s1);
    printf("addr %p\n", &addr1.s2);
    printf("addr %p\n", &addr1.s3);

    printf("\n\n");

    printf("add %p\n", &i);

}

