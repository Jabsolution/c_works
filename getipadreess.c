#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>


int main() {
    char *s[] = {"www.yahoo.com", "www.google.com", "www.facebook.com"};
    struct sockaddr_in inet_sockaddr;

    memset(&inet_sockaddr, 0, sizeof(struct inet_sockaddr));
    inet_sockaddr.sin_family = AF_INET;
    inet_sockaddr.sin_port   = 0;
    inet_sockaddr.sin_addr   = 0;
}

