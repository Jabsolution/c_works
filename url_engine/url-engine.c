#include <stdio.h>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <stdlib.h>
#include <strings.h>
#include <regex.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>
#include <errno.h>


#define handle_error_en(en, msg) \
    do { errno = en; perror(msg); exit(EXIT_FAILURE); } while (0)

#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)


typedef struct _strList {
    char *str;
    struct _strList *next;
} strList;

typedef struct _patternList {
    strList *str_list;
    unsigned int count;   
    unsigned int set;
    struct _patternList *next;
} patternList;

typedef struct _match_info {
    pthread_t thread_id;
    char *regex;
    char *str;
    unsigned int set;
    unsigned int thread_num;
} match_info;

typedef void *(*match_func)(void *);

void parseXML(const char *, const char *, int);
void createSetList(patternList **, patternList *, patternList **);
void createStrList(strList **, strList *, strList **);
patternList *createStrNode(char *);

//Clean functions
int cleanList(patternList *);

// Matching functions
void *ismatch(void *);
void *posix_match(void *);

//Utility Functions
int get_str_len(char *);
int search_token(char *, int, char);
char *format_str(char *);
void print_match_results(match_info *, int);
void chomp_new_line(char *);
void usage();

int main(int argc, char **argv) {
    char *docname; 
    char *setpatterns; 
    char *urlfile;
    int posix = 0;
    if (argc <= 1) {
        usage();
    }
    docname = argv[1];
    urlfile = argv[2];
    if (argv[3]) {
        if (!strcmp(argv[3], "posix")) {
            posix = 1;
        } else {
            printf("Unkown arg: %s\n", argv[3]);
            usage();
        }

    }
    parseXML(docname, urlfile, posix);
}

void parseXML(const char *file, const char *urlfile, int posix) {
    FILE *fp;
    char *mode = "r";
    char line[50];
    // XML Processing
    xmlDocPtr doc;
    xmlNodePtr cnode;
    xmlChar *key;
    // Pattern set list
    patternList *head = NULL;
    patternList *tail = NULL;
    patternList *node = NULL;
    patternList *tmp  = NULL;
    strList     *strtmp = NULL;

    // thread info;
    int num_threads = 3;
    int num = -1;
    match_info *minfo = malloc(num_threads * sizeof(match_info));
    match_func  func_ptr;
    func_ptr = &ismatch;
    int s = 0;
     
    int set = 0;
    int strlen = 0;

    doc = xmlParseFile(file);
    cnode = xmlDocGetRootElement(doc);

    cnode = cnode->children;
    while (cnode) {
        key = xmlNodeListGetString(doc, cnode->children, 1);
        if (!xmlStrcmp(cnode->name, (const xmlChar *) "algo")) {
        // Create node with set strings
            if (!xmlStrcmp(key, (const xmlChar *) "posix")) {
                posix = 1;
                printf("Will run POSIX regex");
            }
        } else {
            if (key) {
                node = createStrNode((char *)key);
                // Create link list of all available pattern sets
                createSetList(&head, node, &tail);
            }
        }
        cnode = cnode->next;
    }
   
    
    // Read example-url.txt
    fp = fopen(urlfile, mode);

    if (posix)
        func_ptr = &posix_match;

    tmp = head;
    while (tmp) {
        set++;
        strtmp = tmp->str_list;
        while (strtmp) {
            fseek(fp, 0, SEEK_SET); // Reset the read pointer 
           
            chomp_new_line(strtmp->str);

            /*
             * Read URLs from the file
             */
            while (fgets(line, 50, fp) != NULL) {
                if (!strcmp(line, "\n"))
                    continue;

                num++;
                chomp_new_line(line);
                minfo[num].thread_num = num + 1;

                minfo[num].regex = strtmp->str;

                strlen = get_str_len(line);
                minfo[num].str   = malloc(sizeof(char) * strlen);
                strncpy(minfo[num].str, line, strlen);

                minfo[num].set   = set;
                memset(&minfo[num].thread_id, 0, sizeof(pthread_t));
                s = pthread_create(&minfo[num].thread_id, NULL, &ismatch, &minfo[num]);
                if (s != 0)
                    handle_error_en(s, "pthread_create");

                // Recycle threads
                if (num >= num_threads - 1) {
                    print_match_results(minfo, num);
                    num = -1; // Reset the number of threads available
                }
            }

            // Recycle the remaining threads before inspecting another regex
            print_match_results(minfo, num);
            num = -1;
            strtmp = strtmp->next;
        }   
        tmp = tmp->next;
    }
    
    /*
     * Now Clean Up :-)
     */ 
    // XML Cleanup
    xmlFreeDoc(doc);

    // Clean patternList
    if (cleanList(head)) {
        head = NULL; // Everything is cleaned
    }
}

int cleanList(patternList *head) {
    patternList *tmp;
    strList     *strtmp;
    patternList *fnode;
    tmp = head;
    while (tmp) {
        strtmp = tmp->str_list;
        while (strtmp) {
            tmp->str_list = strtmp->next;           
            free(strtmp);
            strtmp = tmp->str_list;
        }
        fnode = tmp;
        tmp = tmp->next;
        free(fnode);
    }
    if (!tmp) 
        return 1;
    return 0;
}

void *ismatch(void *minfo) {
    int token_position = -1;
    int last_regex_pos = 0;
    int last_str_pos   = 0;
    int i = 0;
    int j = 0;
    int match = 0;
    int state = 0;
    match_info *mlocal = (match_info *)minfo;
    char *regex = mlocal->regex;
    char *str   = mlocal->str;

    char *ret_val = malloc(sizeof(char));
    *ret_val = 0;

    /*
     * Initial states
     */
    if (regex[i] == '*')
        state = '*'; // Start matching
    else
        state = 'c'; // Start comparing 

    while (!match) {
        if (state == '0')
            break;
        switch(state) {
            case '*':
                i++;
                while (str[j] != '\0') {
                    j++;
                }
                if (regex[i] == '\0') {
                    match = 1;
                } else {
                    j--; // Not NULL
                    state = 's'; // Search for the token
                }
                break;
                  case 's': // Search token
                token_position = search_token(str, j, regex[i]);
                /*
                 * Remember where we last matched
                 */
                last_regex_pos  = i;
                last_str_pos    = token_position;
                state = 'm';
                break;
            case 'm': // Match token
                j = token_position; // Start matching str at this position
                if (token_position != -1) {
                    while (regex[i] != '\0' && str[j] != '\0') {
                        if (regex[i] == str[j]) {
                            i++;
                            j++;
                        } else {
                            /*
                             * If non-match char is a metachar then we
                             * go to state '*' again
                             */
                            if (regex[i] == '*') {
                                state = '*';
                            } else {
                                i = last_regex_pos;
                                j = last_str_pos - 1;
                                token_position = -1; // Reset token pos
                                state = 's';
                            }
                            break;
                        }
                    }
                    // If regex and str matches then we say it's a MATCH
                    if (regex[i] == '\0' && str[j] == '\0') {
                        match = 1;
                    }
                } else {
                    match = 0;
                    state = '0';
                }
                break;
            case 'c':
                token_position = 0;
                state = 'm';
                break;
        }
    }
    if (match) {
        *ret_val = 1;
        return ret_val;
    } else {
        return ret_val;
    }
}

int search_token(char *str, int j, char token) {
    while (j >= 0) {
        if (str[j] == token) {
            return j;
        }
        j--;
    }
    return -1;
}


patternList * createStrNode(char *key) {
    unsigned int charCount = 0;
    char *str              = NULL;
    int i                  = 0;
    int j                  = 0;
    int st_index           = 0;
    int end_index          = 0;
    int no_of_str          = 0;
    int strLen             = 0;
    int r_space            = 0;

    patternList *node      = NULL;
    strList     *tmp       = NULL;
    strList     *strNode   = NULL;
    strList     *strHead   = NULL;
    strList     *strTail   = NULL;

    node = (patternList *)malloc(sizeof(patternList));

    for (i = 0; key[i] != '\0'; i++) {
        if (key[i] == ' ') {
            st_index++;
            end_index++;
            continue;
        }

        if (key[i] != ' ') {
            end_index++;
            if (key[i + 1] == '\0' || key[i + 1] == ' ') {
                no_of_str++;
                strLen = (end_index - st_index);
                strNode = (strList *)malloc(sizeof(strList));
                strNode->str = malloc(sizeof(char) * strLen);
                strncpy(strNode->str, &key[st_index], strLen);
                strNode->str[strLen] = '\0';
                strNode->next = NULL;
                createStrList(&strHead, strNode, &strTail);
                st_index = end_index;
                end_index = st_index;
            }
        } 
    }

    node->str_list = strHead;
    node->count = no_of_str;
    node->next = NULL;

    return node;
}

void createStrList(strList **head, strList *node, strList **tail) {
    if (!*head) {
        *head = node;
        *tail = node;
        return;
    }
    (*tail)->next = node;
    *tail = node;
    return;
}

void createSetList(patternList **head, patternList *node, 
                   patternList **tail)
{
    if (!*head) {
        *head = node;
        *tail = node;
        return;
    }
    (*tail)->next = node;
    *tail = node;
    return;
}

void * posix_match(void *minfo) {
    char *nstr = NULL;
    regex_t *comp_regex = malloc(sizeof(regex_t));
    regmatch_t matches[1];
    int status = 0;
    int i = 0;
    char *regex = ((match_info *)minfo)->regex;
    char *str   = ((match_info *)minfo)->str;
    char *ret_val = malloc(sizeof(char));
    *ret_val = 0;

    nstr = format_str(regex);
    if (!(status = regcomp(comp_regex, nstr, REG_EXTENDED))
        && !(regexec(comp_regex, str, 1, matches, 0))) {
        if (nstr != regex)
            free(nstr);
        *ret_val = 1;
        return ret_val;
    }
    if (status && nstr != regex)
        free(nstr);

    return ret_val;
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
        return nstr;
    } else {
        return regex;
    }
}

void print_match_results(match_info *minfo, int num) {
    void *ret;
    int s = 0;

    while (num >= 0) {
        s = pthread_join(minfo[num].thread_id, &ret);
        if (s != 0) {
            printf("Pthread_join error");
            handle_error_en(s, "pthread_join");
        }
        if ((*(char *)ret) == 1) {
            printf("url: %s pattern: %s set: %d\n",
                    minfo[num].str, minfo[num].regex, minfo[num].set);
        }
        free(minfo[num].str);
        num--;
        free(ret);
    }
}

void chomp_new_line(char *str) {
    int i = 0;
    if (!str)
        return;

    while (str[i] != '\0') {
        if (str[i] == '\n') {
            str[i] = '\0';
            return;
        }
        i++;
    }
}
    
int get_str_len(char *str) {
    int len = 0;
    
    while (str) {
        if (*str == '\0')
            return (len + 1);
        len++;
        str++;
    }
    return len;
}

void usage() {
    printf("USAGE: \nurl-engine <xml_file> <url_pattern_file> [posix]\n");
    printf("Specify \"posix\" if you want to use POSIX regex library.");
    printf(" It is optional.\n");
    exit(1);
}
