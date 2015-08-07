#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "msg.h"

#define MAX_BUF 256
#define PORT 12323

typedef struct addrinfo AI;
typedef struct sockaddr_in SA_I;
typedef struct sockaddr SA;

void start_server();
int get_ip_address(char *, char **, int *);
int get_file_size(char *, char **, int *);
int get_file(char *, char **, int *);
void read_request(int, packet *);
void send_request(int, packet *);
void reply_to_client(int, packet *);

int main() {
    start_server();
}

/*
 * Server needs to do the following steps,
 *
 * 1) Create a socket
 * 2) Bind a socket
 * 3) Listen on socket
 * 4) Accept connects
 * 5) Get request from (read from) socket
 * 6) Reply to the socket(Write)
 *
 */
void start_server() {
    char hostname[INET_ADDRSTRLEN];
    // Socket info
    int sockfd, c_sock;
    unsigned int serv_len;
    SA_I serv_addr, cli_addr;

    packet req_pkt;
    packet rply_pkt;

    // Ip address
    AI *ipinfo;

    // Error handling
    int errno;
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Get Network address of localhost
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr); 

    bind(sockfd, (SA *)&serv_addr, sizeof(SA));

    if (listen(sockfd, 5)) {
        printf("ERROR: %s", strerror(errno));
        printf("Listen failed\n");
        exit(1);
    }
    
    serv_len = sizeof(SA);

    for (;;) {
        c_sock = accept(sockfd, (SA *)&cli_addr, &serv_len);
        /* Print client's info */
        printf("Connected with the following client\n");
        inet_ntop(AF_INET, &cli_addr.sin_addr, hostname, INET_ADDRSTRLEN);
        printf("Host: %s\n Port: %d\n", hostname, htons(cli_addr.sin_port));

        read_request(c_sock, &req_pkt);
        send_request(c_sock, &req_pkt);
    }
}

void send_request(int c_sock, packet *req_pkt) {
    int h_len, data_len;
    packet rply_pkt;
    char *free_ptr = NULL;

    h_len = data_len = 0;

    memset(&rply_pkt, 0, sizeof(rply_pkt));
    if (h_len <= 0) {
        /* Now we need to start proceesing the client's request */

        /* What kind of message */
        switch(req_pkt->m_type) {
            case ADR_REQ:
                if (get_ip_address(req_pkt->data, &rply_pkt.data, &data_len)) {
                    rply_pkt.m_type = htons(ADR_RPLY);
                    rply_pkt.data_len = htonl(data_len);
                    printf("Got ipadress: %s", rply_pkt.data);
                } else {
                    rply_pkt.m_type   = htons(ADR_FAIL);
                    rply_pkt.data_len = 0;
                }
                free_ptr = rply_pkt.data;
                reply_to_client(c_sock, &rply_pkt);
                break;
            case FSZ_REQ:
                if (get_file_size(req_pkt->data, &rply_pkt.data, &data_len)) {
                    rply_pkt.m_type = htons(FSZ_RPLY);
                    rply_pkt.data_len = htonl(data_len);
                    printf("Got size: %s", rply_pkt.data);
                } else {
                    rply_pkt.m_type = htons(FSZ_FAIL);
                    rply_pkt.data_len = 0;
                }
                free_ptr = rply_pkt.data;
                reply_to_client(c_sock, &rply_pkt);
                break;
            case GET_REQ:
                if (get_file(req_pkt->data, &rply_pkt.data, &data_len)) {
                    rply_pkt.m_type = htons(GET_RPLY);
                    rply_pkt.data_len = htonl(data_len);
                } else {
                    rply_pkt.m_type = htons(GET_FAIL);
                    rply_pkt.data_len = 0;
                }
                free_ptr = rply_pkt.data;
                reply_to_client(c_sock, &rply_pkt);
                break;
        }
        free(free_ptr);
        close(c_sock);
    }
}

void read_request(int c_sock, packet *req_pkt) {
    int index, h_len, idx, n, i, retry, timeout;
    index = h_len = retry = idx = n = i = 0;
    timeout = 60;
    char buf[MAX_BUF];
    char recv_buf[MAX_BUF];
    /*
     * Read the incoming packets, starting from header
     * h_len is the header info we need to read from socket/client in order to 
     * determine the request type and process the data
     */
    h_len = sizeof(req_pkt->m_type) + sizeof(req_pkt->data_len);

    while (h_len) {
        n = read(c_sock, buf, 1);

        if (!n) {
            sleep(5);
            if (retry >= timeout) {
                printf("Server read timed out\n");
                exit(1);
            }
            retry++;
        }

        if (index < 6) {
            memcpy(&recv_buf[i], buf, 1);
            i++;
        }

        // Calculate packet header boundries
        index++;

        /* 0 - 1 = Message Type */
        if (index == 2) {
            /* We got the message type */
            i = 0;
            memcpy(&req_pkt->m_type, recv_buf, sizeof(req_pkt->m_type));
            req_pkt->m_type = ntohs(req_pkt->m_type);
            printf("Received message type: %#x\n", req_pkt->m_type);
            memset(recv_buf, 0, sizeof(recv_buf));
        }   

        /* 2 - 5 = Data Length */
        if (index == 6) {
            /* We got the data length */
            i = 0;
            memcpy(&req_pkt->data_len, recv_buf, sizeof(req_pkt->data_len));
            req_pkt->data_len = ntohl(req_pkt->data_len);
            printf("Data len: %d\n", req_pkt->data_len);
            /* Need to read the payload from socket */
            h_len = req_pkt->data_len + 1;

            // Allocate storage
            req_pkt->data = malloc(sizeof(char) * h_len);
            memset(recv_buf, 0, sizeof(recv_buf));
        }   

        /* 5+ = Data (Based on the Data Length) */
        if (index > 6 && req_pkt->data_len) {
            memcpy(&req_pkt->data[idx], buf, 1); 
            idx++;
        }   

        h_len--;
    }
}

void reply_to_client(int sockfd, packet *rply_pkt) {
    char buf[MAX_BUF];
    char recv_buf[MAX_BUF];
    int i = 0;
    unsigned int bytes = 0;
     /*
     * Write 
     */

    /* Write message type */
    memset(buf, 0, sizeof(buf));
    i = 0;
    bytes = sizeof(rply_pkt->m_type);
    memcpy(buf, &rply_pkt->m_type, bytes);
    printf("Writing m_type: %#x\n", rply_pkt->m_type);
    while (bytes) {
        write(sockfd, &buf[i++], 1);
        bytes--;
    }

    memset(buf, 0, sizeof(buf));
    i = 0;

    /* Before transmission, convert from host to network */
    bytes = sizeof(rply_pkt->data_len);
    memcpy(buf, &rply_pkt->data_len, bytes);
    printf("Writing len: %d\n", ntohl(rply_pkt->data_len));
    while (bytes) {
       write(sockfd, &buf[i++], 1);
       bytes--;
    }

    /* Write data */
    bytes = ntohl(rply_pkt->data_len);
    while (bytes) {
        write(sockfd, (rply_pkt->data)++, 1);
        bytes--;
    }
}

int get_ip_address(char *host, char **data, int *data_len) {
    AI *ipinfo;
    SA_I *sa_i;
    int len = 0;
    int ret_code = 0;
    int i = 0;
    char *ipaddress = malloc(sizeof(char) * INET_ADDRSTRLEN);

    ret_code = getaddrinfo(host, 0, NULL, &ipinfo);
    if (ret_code) {
        printf("Encountered Error: %s\n", gai_strerror(ret_code));
        return 0;
    }

    for (sa_i = (SA_I *)ipinfo->ai_addr; ipinfo != NULL; ipinfo = ipinfo->ai_next) {
        sa_i = (SA_I *)ipinfo->ai_addr;

        if (sa_i->sin_addr.s_addr) {
            inet_ntop(AF_INET, &(sa_i->sin_addr), ipaddress, INET_ADDRSTRLEN);
            *data = ipaddress;
            while (ipaddress[i] != '\0') {
                i++;
            }
            *data_len = i;
            return 1;
            /* Count the actual data length without NULL character */
        }
    }
    return 0;
}

int get_file(char *file, char **data, int *data_len) {
    FILE *fp = NULL;
    char *mode = "r";
    int file_size = 0;
    int i = 0;
    int errno;

    printf("file name: %s", file);

    fp = fopen(file, mode);

    if (!fp) {
        printf("Error: %s", strerror(errno));
        return 0;
    }

    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);
    printf("File size: %d\n", file_size);

    *data_len = file_size;
    *data = malloc(sizeof(char) * file_size);

    fread(*data, 1, file_size, fp);

    return 1;
}

int get_file_size(char *file, char **data, int *data_len) {
    FILE *fp = NULL;
    char *mode = "r";
    int file_size = 0;
    int i = 0;
    int errno;
    char *buf = malloc(sizeof(char) * 256);

    printf("file name: %s", file);

    memset(buf, 0, sizeof(char) * 256);
    fp = fopen(file, mode);

    if (!fp) {
        printf("Error: %s", strerror(errno));
        return 0;
    }
    fseek(fp, 0L, SEEK_END);
    file_size = ftell(fp);
    printf("File size: %d\n", file_size);
    snprintf(buf, 256, "%d", file_size);
    printf("File size: %s\n", buf);

    *data = buf;
    while(buf[i] != '\0') {
        i++;
    }
    *data_len = i;

    return 1;
}

