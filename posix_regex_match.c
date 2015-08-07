#include <stdio.h>
#include <stdlib.h>
#include <regex.h>

int is_match(const char *, const char *);
void print_regex_error(int, regex_t *);

int main() {
    const char *regex = ".*/(.+)$";
    const char *str = "/isan/bin/fex.srs";

    if(is_match(regex, str)) {
        printf("Match");
    }
}

int is_match(const char *regex, const char *str) {
    regex_t *regexCompiled = malloc(sizeof(regex_t));
    regmatch_t matches[1];
    int status = 0;
    int match = 0;

    if ((status = regcomp(regexCompiled, regex, REG_EXTENDED)) == 0) {
        printf("%zu", regexCompiled->re_nsub);
        if((status = regexec(regexCompiled, str, 1, matches, 0)) == 0) {
            printf("Matched string starts at %lld and ends at %lld", 
                    matches[0].rm_so, matches[0].rm_eo);
        }
    }
    if (status) {
        print_regex_error(status, regexCompiled);
        match = 0;
    } else {
        match = 1;
    }
    free(regexCompiled);
    return match;
}

void print_regex_error(int status, regex_t *regexCompiled) {
    char *err_desc;
    int err_desc_size;

    err_desc_size = regerror(status, regexCompiled, (char *) NULL, 0);
    err_desc = malloc(sizeof(char) * err_desc_size);
    regerror(status, regexCompiled, err_desc, err_desc_size);
    printf("ERROR: %s", err_desc);
    free(err_desc);
}
