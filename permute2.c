#include <stdio.h> 
#include <stdlib.h> 


int count = 0;
void swap (char *x, char *y) 
{ 
    char temp; 
    temp = *x; 
    *x = *y; 
    *y = temp; 
} 


void permute(char *a, int i, int n) 
{ 
    int j; 
    if (i == n) {
        ++count;
        printf("%d: %s\n", count, a);
        if (count == 1000002) {
            printf("This is the end\n");
            exit(1);
        }
    }
    else 
    { 
        for (j = i; j <= n; j++) 
        { 
            swap((a + j), (a + i)); 
            permute(a, i+1, n); 
            swap((a + j), (a + i)); 
        } 
    } 
} 


int main() 
{ 

    char a[] = "021"; 
    permute(a, 0, 2); 
    return 0; 
}


