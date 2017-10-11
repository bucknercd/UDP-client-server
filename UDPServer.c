// Chris Buckner   men839

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>

#define PORT 10000
#define BUF_SIZ 1024

void error(char *);

int main(int argc, char **argv) {
    char buf[BUF_SIZ];
    struct sockaddr_in server;
    struct sockaddr_in client;

    // create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket < 0)
        error("---> Could not create a socket\n");

    // zero out structure
    memset(&server, 0, sizeof(struct sockaddr_in));

    // server ip and port setup
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");


    // socket binding
    if (bind(sockfd, (struct sockaddr *)&server,sizeof(struct sockaddr_in) ) == -1)
        error("---> Problem binding the socket\n");


    // receive messages
    int clientlen = sizeof(struct sockaddr_in);
    while (1) {
        memset(buf, 0, BUF_SIZ);
        int bytes_rec = recvfrom(sockfd, buf, BUF_SIZ, 0, (struct sockaddr *) &client, (socklen_t *)&clientlen);
        if (bytes_rec < 0)
            error("---> Problem receiving message");

        if (sendto(sockfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&client, sizeof(struct sockaddr_in)) < 0)
            perror("---> Problem sending message\n");
    }
}

void error(char * mesg) {
    fprintf(stderr, "%s", mesg);
    perror("Error: ");
    exit(-1);
}
