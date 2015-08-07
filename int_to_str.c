#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *convert_ip_to_str(unsigned long);

int main() {
    unsigned long ip_addr = 4294967295;
    char *ip_addr_str;

    ip_addr_str = convert_ip_to_str(ip_addr);
    printf("%s\n", ip_addr_str);
}

char *convert_ip_to_str(unsigned long ip) {
    int rem = 0;
    int base = 256;
    char *ip_str = NULL;
    int nibbles[4] = {0};
    int i = 0;
    int len = 0;

    memset(nibbles, 0, 4 * sizeof(char));
    while (ip) {
        rem = ip % base; 
        nibbles[i++] = rem;
        ip = ip / base;
    }
    len = snprintf(NULL, 0, "%d.%d.%d.%d", nibbles[3], nibbles[2], nibbles[1], nibbles[0]);
    ip_str = malloc((len + 1) * sizeof(char));
    snprintf(ip_str, len + 1, "%d.%d.%d.%d", nibbles[3], nibbles[2], nibbles[1], nibbles[0]);
    return ip_str;
}

