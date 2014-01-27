#include <stdio.h>
#include <stdlib.h>

void arrange_queens(char (*)[8], int x_pos, int y_pos, int queens);

int main() {
    char chess[8][8] = {{}};
    int no_of_queens = 8;
    arrange_queens(chess, 0, 0, 8);
}

void arrange_queens(char (*chess)[8], int x_pos, int y_pos, int no_of_queens) {
    int x = 0;
    int y = 0;
    int x_incr = x_pos;
    int x_tmp = 0;
    int y_tmp = 0;
    int i = 0;
    int j = 0;
    if (y_pos > 7 && no_of_queens != 0)
        return;
    if (no_of_queens == 0) 
        return;
    printf("Queen needs to be arranged at row [%d, %d], queens remaining"
                        ": %d\n", x_pos, y_pos, no_of_queens);

    while(x_incr <= 7) {
        if(x_pos == 0 && y_pos == 0) {
            chess[0][0] = 'x';
            printf("Putting the first queen");
            printf("[%d, %d]\n", x, y);
            arrange_queens(chess, 0, y_pos + 1, no_of_queens-1);
            printf("Not doing another round\n");
            return;
        }
        x_tmp = x_pos = x_incr++;
        y_tmp = y_pos;
        printf("Trying [%d, %d]\n", x_pos, y_pos);
        while(y_tmp >= 0 && chess[x_tmp][y_tmp--] != 'x');
        if (chess[x_tmp][++y_tmp] == 'x') {
            continue;
        }
        x_tmp = x_pos;
        y_tmp = y_pos;
        while(x_tmp >= 0 && y_tmp >= 0 && chess[x_tmp--][y_tmp--] != 'x');
        if (chess[++x_tmp][++y_tmp] == 'x') {
            continue;
        }
        x_tmp = x_pos;
        y_tmp = y_pos;
        while(x_tmp <= 8 && y_tmp >= 0 && chess[x_tmp++][y_tmp--] != 'x');
        if (chess[--x_tmp][++y_tmp] == 'x') {
            continue;
        }
        chess[x_pos][y_pos] = 'x';
        printf("[%d, %d]", x_pos, y_pos);
        if (no_of_queens == 1) {
            printf("First pass complete, the last position[%d, %d]", x_pos,
                    y_pos);
            for (j = 0; j <= 7; j++) {
                for (i = 0; i <= 7; i++) {
                    if (chess[i][j] == 'x') {
                        printf("[%d, %d]\n", i, j);
                    }   
                }   
            }   

        }
        arrange_queens(chess, 0, y_pos + 1, no_of_queens-1);
        printf("Removing [%d, %d]", x_pos, y_pos);
        chess[x_pos][y_pos] = '0'; 
    }
    return;
}
