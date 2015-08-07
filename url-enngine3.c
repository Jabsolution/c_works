#include <stdio.h>
#include <stdlib.h>


typedef void *(*match_func)(void *);
int main() {

}

void match() {

    match_func func_ptr;
    func_ptr = &match;

    if (posix)
        func_ptr = &posix_match;

    fp = fopen(urlfile, mode);
    while (tmp) {
        tmp = head;
        set++;
        strtmp = tmp->str_list;
        while (strtmp) {
            fseek(fp, 0L, SEEK_SET); // Reset read the pointer 
            while (fgets(line, 80, fp) != NULL) {
                if (!strcmp(line, "\n"))
                    continue;
                minfo[num].thread_id = num + 1;
                minfo[num].regex = regex;
                minfo[num].str   = line;
                minfo[num].set   = set;

                pthread_create(&minfo[num].thread_id, NULL, func_ptr, &minfo[num]);
                num++;
                // Recycle threads
                if (num > num_threads) {
                    print_match_results(minfo, num);
                    num = 0; // Reset numer of threads available
                }
            }

            // Recycle the remaining threads before inspecting another regex
            if (num) {
                print_match_results(minfo);
            }

            strtmp = strtmp->next;
        }
        tmp = tmp->next;
    }


}

void print_match_results(match_info *minfo, int num) {
    void *ret;

    while (num) {
        pthread_join(&minfo[num].thread_id, &ret);
        printf("url: %s pattern: %s set: %d\n",
                minfo[num].line, minfo[num].regex, minfo[num].set);
        num--;
    }
}
