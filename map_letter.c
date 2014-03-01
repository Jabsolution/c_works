/*
 *
 * Mapping 
 * '1' = 'A','B','C' 
 * '2' = 'D','E','F' 
 * ... 
 * '9' = 
 *
 * input: 112 
 * output :ouput = [AAD, BBD, CCD, AAE, AAF, BBE, BBF, CCE, CCF]
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>

void generate_mapping(int (*arr)[], char *map_str, char *, int);

int main() {
    int alph[9][3];
    char buf_str[4] = {};
    alph[1][0] = 'a';
    alph[1][1] = 'b';
    alph[1][2] = 'c';
    alph[2][0] = 'd';
    alph[2][1] = 'e';
    alph[2][2] = 'f';

    generate_mapping(alph, "221", buf_str, 0);

}

void generate_mapping(int (*arr)[3], char *map_str, char *buf_str, 
                      int buf_str_idx) {
    int i = 0;
    int j = 0;
    int tmp = 0;
    int k = buf_str_idx;
    int same_digit = 0;
   
    if (!map_str) 
        return;
    while (j < 3) {
        i = 0;
        k = buf_str_idx;
        same_digit = 0;
        while (map_str[i]) {
            if (!tmp || ((map_str[i] - '0') == tmp)) {
                buf_str[k++] = arr[map_str[i] - '0'][j];
                tmp = map_str[i] - '0';
                same_digit++;
            } else {
                buf_str_idx = k;
                generate_mapping(arr, &map_str[i], buf_str, buf_str_idx);
                if (same_digit > 1) 
                    buf_str_idx = 0;
                else 
                    buf_str_idx = k - 1;
                break;
            }
            i++;
        }
        j++;
        if (!map_str[i]) {
            buf_str[k] = '\0';
            printf("%s\n", buf_str);
        }
    }
}
