#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_BUF 256
typedef struct addrinfo AI;
typedef struct sockaddr_in SA_I;
typedef struct sockaddr SA;

AI * print_ip_address(const char *);
void cli_connet(AI *);

int main(int argc, char **argv) {
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

    printf("Host: %s\n", argv[1]);

    /*
     * Parse command line args
     */
    req_type = argv[1];
    if(strcmp(req_type, "-a")) {
        cli_pkt.m_type = ADR_REQ;
    } else if (strcmp(req_type, "-f")) {
        cli_pkt.m_type = FSZ_REQ;
    } else if (strcmp(req_type, "-g")) {
        cli_pkt.m_type = GET_REQ;
    } else {
        printf("Unknown request\n");
        exit(1);
    }
    hostname = argv[2];
    port     = argv[3];
    cli_pkt.data_len = strlen(argv[4]);
    cli_pkt.data = malloc(sizeof(char) * cli_pkt.data_len);
    strncpy(cli_pkt.data, argv[4], cli_pkt.data_len);

    ipinfo = get_ip_address(hostname);
    cli_connet(ipinfo, port, &cli_pkt);
}

AI * get_ip_address(const char *host) {
    AI *ipinfo;
    char ipaddress[INET_ADDRSTRLEN];

    getaddrinfo(host, 0, NULL, &ipinfo);
    return ipinfo;
}

void cli_connet(AI *ipinfo, int port, packet *cli_pkt) {
    SA_I *sa_i;
    int sockfd, n, h_len, index, retry, timeout;
    int i, idx;
    unsigned int bytes;
    char buf[MAX_BUF];
    char recv_buf[MAX_BUF];
    retry   = 0;
    timeout = 60; // Out client waits for reponse from server form 5 mins, then timesout
    i       = 0;
    idx     = 0;

    // Initialize socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("Error creating socket\n");
        exit(1);
    }

    for (sa_i = (SA_I *)ipinfo->ai_addr; ipinfo != NULL; 
         ipinfo = ipinfo->ai_next) {
        sa_i = (SA_I *)ipinfo->ai_addr;

        // Take the first available IP address for the host
        if (sa_i->sin_addr) {
            inet_ntop(AF_INET, &(sa_i->sin_addr), ipaddress, 
                    INET_ADDRSTRLEN);
            printf("Host Info: %u %s\n", ntohs(sa_i->sin_port), ipaddress);
            break;
        }
    }

    if (connect(sockfd, (SA *)sa_i, sizeof(SA))) {
        printf("Connect failed \n");
        exit(1);
    }

    /*
     * Write 
     */

    /* Write message type */
    memset(buf, 0, sizeof(buf));
    memcpy(buf, &cli_pkt->m_type, byte);
    bytes = sizeof(cli_pkt->m_type);
    while (bytes) {
        write(sockfd, buf++, 1);
        bytes--;
    }

    /* Write data length */
    memset(buf, 0, sizeof(buf));

    /* Before transmission, convert from host to network */
    cli_pkt->data_len = htonl(cli_pkt->data_len);
    memcpy(buf, &cli_pkt->data_len, sizeof(bytes));
    bytes = sizeof(cli_pkt->data_len)
    while (bytes) {
       write(sockfd, buf++, 1);
       bytes--;
    }

    /* Write data */
    bytes = cli_pkt->data_len;
    while (bytes) {
       write(sockfd, (cli_pkt->data)++, 1);
       bytes--;
    }

    /* READ */
    /*
     * We need to read the packet header first in order to get the
     * data length. 
     *
     */
    h_len = sizeof(cli_pkt->m_type) + sizeof(cli->pkt->data_len);

    while (h_len) {
        n = read(sockfd, buf, 1);

        /* Retry in case reponse from server is delayed */
        if (!n) {
            sleep(5);
            if (retry >= timeout) {
                printf("Time Out\n");
                exit(1);
            }
            retry++;
            continue;
        }

        if (index < 6) {
            memcpy(recv_buf[i], buf, 1);
            i++;
        }

        // Packet header boundries
        index++;

        /* 0 - 1 = Message Type */
        if (index == 2) {
            /* We got the message type */
            memcpy(&cli_pkt->m_type, recv_buf, sizeof(cli_pkt->m_type));
            cli_pkt->m_type = ntohs(cli_pkt->m_type);
            printf("Received message type: %#x\n", cli_pkt->m_type);
            memset(recv_buf, 0, sizeof(recv_buf));
        }

        /* 2 - 5 = Data Length */
        if (index == 6) {
            /* We got the data length */
            memcpy(&cli_pkt->data_len, recv_buf, sizeof(cli_pkt->data_len));
            cli_pkt->data_len = ntohl(cli_pkt->data_len);
            printf("Data len: %d\n", cli_pkt->data_len);
            /* Need to read the payload from socket */
            h_len = cli_pkt->data_len;
            memset(recv_buf, 0, sizeof(recv_buf));
        }

        /* 5+ = Data (Based on the Data Length) */
        if (index > 6 && cli_pkt->data_len) {
            memcpy((cli_pkt->data)++, buf, 1);
        }
    
        h_len--;
    }
    
    if (h_len <= 0) {
        printf("Data: %s", cli_pkt->data);
    }
}

