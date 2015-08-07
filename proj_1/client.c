#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <openssl/md5.h>
#include "msg.h"

#define MAX_BUF 256
typedef struct addrinfo AI;
typedef struct sockaddr_in SA_I;
typedef struct sockaddr SA;

AI * get_ip_address(const char *);
int cli_connect(char *, int);
void prepare_packet(char *, packet *);
void send_request(int, packet *);
void read_request(int, char *);
void write_to_socket(int, void *, int);
void print_data(packet *, int);


int main(int argc, char **argv) {
    // socket
    int sockfd;
    // Command Line Variables
    char *hostname = NULL;
    unsigned short port = 0;

    // Packet attributes
    char *req_type = NULL;
    char *data = NULL;
    short m_type;

    packet cli_pkt;

    // Socket info
    AI *ipinfo;

    // Parse command line args
    req_type = argv[1];
    hostname = argv[2];
    port     = atoi(argv[3]);

    printf("Host: %s\n", argv[2]);

    /*
     * Parse command line args
     */
    if(!strcmp(req_type, "-a")) {
        cli_pkt.m_type = htons(ADR_REQ);
    } else if (!strcmp(req_type, "-f")) {
        cli_pkt.m_type = htons(FSZ_REQ);
    } else if (!strcmp(req_type, "-g")) {
        cli_pkt.m_type = htons(GET_REQ);
    } else {
        printf("Unknown request\n");
        exit(1);
    }

    printf("Command line data\n");
    printf(" Request Type: %s\n Hostname: %s\n Port: %d\n Data: %s\n", req_type, hostname,
            port, argv[4]);

    sockfd = cli_connect(hostname, port);

    prepare_packet(argv[4], &cli_pkt);
    send_request(sockfd, &cli_pkt);
    read_request(sockfd, argv[4]);
}

AI * get_ip_address(const char *host) {
    AI *ipinfo;

    getaddrinfo(host, 0, NULL, &ipinfo);
    return ipinfo;
}

void prepare_packet(char *arg, packet *cli_pkt) {
    int i;

    for (i = 0; arg[i] != '\0'; i++)
        ;

    // Allocate space for data
    printf("Data len: %d\n", i);
    printf("Data: %s\n", arg);
    cli_pkt->data = malloc(sizeof(char) * i);
    cli_pkt->data_len = htonl(i);
    memcpy(cli_pkt->data, arg, i);
}


void write_to_socket(int sockfd, void *data, int len) {
    char buf[MAX_BUF];
    int i = 0;

    memset(buf, 0, sizeof(buf));
    memcpy(buf, data, len);

    while (len) {
        write(sockfd, &buf[i++], 1);
        len--;
    }
}

void send_request(int sockfd, packet *cli_pkt) {
    int bytes = 0;

    bytes = sizeof(cli_pkt->m_type);
    printf("m_type: %#x\n", ntohs(cli_pkt->m_type));
    write_to_socket(sockfd, &cli_pkt->m_type, bytes);

    /* data length */
    bytes = sizeof(cli_pkt->data_len);
    printf("len: %d\n", ntohl(cli_pkt->data_len));
    write_to_socket(sockfd, &cli_pkt->data_len, bytes);

    /* data */
    bytes = ntohl(cli_pkt->data_len);
    write_to_socket(sockfd, cli_pkt->data, bytes);
}

void read_request(int sockfd, char *request) {
    char buf[MAX_BUF];
    char recv_buf[MAX_BUF];
    int i, index, h_len, n, timeout, retry;
    packet rply_pkt;
    char *data_ptr;

    /* Initialize data */
    memset(buf, 0, sizeof(buf));
    memset(recv_buf, 0, sizeof(recv_buf));
    i = 0;
    retry = 0;
    index = 0;
    timeout = 60;

    /* READ 
     * We need to read the packet header first in order to get the
     * data length. 
     */
    h_len = sizeof(rply_pkt.m_type) + sizeof(rply_pkt.data_len);

    while (h_len) {
        n = read(sockfd, buf, 1);

        /* Retry in case reponse from server is delayed */
        if (!n) {
            sleep(5);
            if (retry >= timeout) {
                printf("Time Out\n");
                exit(1);
            }
            printf("Retrying\n");
            retry++;
            continue;
        }

        if (index < 6) {
            memcpy(&recv_buf[i], buf, 1);
            i++;
        }

        // Packet header boundries
        index++;

        /* 0 - 1 = Message Type */
        if (index == 2) {
            /* We got the message type */
            i = 0;
            memcpy(&rply_pkt.m_type, recv_buf, sizeof(rply_pkt.m_type));
            rply_pkt.m_type = ntohs(rply_pkt.m_type);
            switch(rply_pkt.m_type) {
                case ADR_FAIL:
                    printf("\tADDR request for %s failed\n", request);
                    break;
                case FSZ_FAIL:
                    printf("\tFILESIZE request for %s failed\n", request);
                    break;
                case GET_FAIL:
                    printf("\tGET request for %s failed\n", request);
                    break;
            }
            printf("Received message type: %#x\n", rply_pkt.m_type);
            memset(recv_buf, 0, sizeof(recv_buf));
        }

        /* 2 - 5 = Data Length */
        if (index == 6) {
            /* We got the data length */
            i = 0;
            memcpy(&rply_pkt.data_len, recv_buf, sizeof(rply_pkt.data_len));
            rply_pkt.data_len = ntohl(rply_pkt.data_len);
            printf("Data len: %d\n", rply_pkt.data_len);
            /* Need to read the payload from socket */
            h_len = rply_pkt.data_len + 1;
            rply_pkt.data = malloc(sizeof(char) * rply_pkt.data_len);
            data_ptr = rply_pkt.data;
            memset(recv_buf, 0, sizeof(recv_buf));
        }

        /* 5+ = Data (Based on the Data Length) */
        if (index > 6 && rply_pkt.data_len) {
            memcpy(rply_pkt.data, buf, 1);
            rply_pkt.data++;
        }
    
        h_len--;
    }

    if (h_len <= 0 && rply_pkt.data_len) {
        rply_pkt.data = data_ptr;
        print_data(&rply_pkt, rply_pkt.data_len);
    }
}

int cli_connect(char *hostname, int port) {
    SA_I sa_i;
    int sockfd;

    // Initialize socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    sa_i.sin_family = AF_INET;
    sa_i.sin_port = htons(port);
    inet_pton(AF_INET, "127.0.0.1", &sa_i.sin_addr);

    if (connect(sockfd, (SA *)&sa_i, sizeof(SA))) {
        printf("ERROR: %s\n", strerror(errno));
        printf("Connect failed \n");
        exit(1);
    }
    return sockfd;
}

void print_data(packet *rply_pkt, int data_len) {
    unsigned char *md5 = malloc(sizeof(char) * MD5_DIGEST_LENGTH);
    int i = 0;

    switch(rply_pkt->m_type) {
        case ADR_RPLY:
            printf("\tADDR = ");
            break;
        case FSZ_RPLY:
            printf("\tFILESIZE = ");
            break;
        case GET_RPLY:
            printf("\tFILESIZE = %d", rply_pkt->data_len);
            break;
    }
    
    if (rply_pkt->m_type == GET_RPLY) {
        MD5((unsigned char *)rply_pkt->data, data_len, md5);
        printf(" MD5 = ");
        while (i < MD5_DIGEST_LENGTH) {
            printf("%x", md5[i]);
            i++;
        }
    } else {
        while (data_len) {
            printf("%c", *(rply_pkt->data));
            rply_pkt->data++;
            data_len--;
        }
    }

    printf("\n");
}
