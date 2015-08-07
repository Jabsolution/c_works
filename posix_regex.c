#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

char *get_regerror(int, regex_t *);
char *format_str(char *);
int main() {
    char *regex = "*.bb.cc/*";
    char *nstr = NULL;
    char *str   = "aa.bb.cc/ddx/cc";
    char *err_str = NULL;
    int status = 0;
    regex_t *comp_regex = malloc(sizeof(regex_t));
    regmatch_t matches[1];

    nstr = format_str(regex);
    printf("str %s", nstr);
    if (!(status = regcomp(comp_regex, nstr, REG_EXTENDED))) {
        if (!(regexec (comp_regex, str, 1, matches, 0))) {
            printf("Match");
        }
    }
    if (status) {
        err_str = get_regerror(status, comp_regex);
        printf("ERROR: %s", err_str);
    }
    

}

char *format_str(char *regex) {
    int i = 0;
    int j = 0;
    int rep = 0;
    char *nstr = NULL;
    while (regex[i] != '\0') {
        if (regex[i] == '*') {
            rep++;
        }
        i++;
    }
    if (rep) {
        nstr = malloc(sizeof(char) * (i + rep + 1));
        i = 0;
        while (regex[i] != '\0') {
            if (regex[i] == '*') {
                nstr[j] = '.';
                nstr[j + 1] = '*';
                j = j + 2;
            } else {
                nstr[j] = regex[i];
                j++;
            }
            i++;
        }
        nstr[j] = '\0';
    }
    printf("New str: %s", nstr);
    return nstr;

}

char *get_regerror (int errcode, regex_t *compiled)
{
    size_t length = regerror (errcode, compiled, NULL, 0);
    char *buffer = malloc(sizeof(char) * length);
    (void) regerror (errcode, compiled, buffer, length);
    return buffer;
}

