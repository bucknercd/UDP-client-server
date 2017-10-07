// Chris Buckner  men839

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

#define PORT 10000
#define BUF_SIZ 1024

void error(char *);

int main(int argc, char **argv) {
    char buf[BUF_SIZ];
    struct sockaddr_in host;
    struct sockaddr_in target;

    // create socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (socket < 0)
        error("---> Could not create a socket\n");

    // zero out structures
    memset(&host, 0, sizeof(struct sockaddr_in));
    memset(&target, 0, sizeof(struct sockaddr_in));

    // target ip and port setup
    target.sin_family = AF_INET;
    target.sin_port = htons(PORT);
    target.sin_addr.s_addr = inet_addr("127.0.0.1");

    // socket binding
    if (bind(sockfd, (struct sockaddr *)&host,sizeof(struct sockaddr_in) ) == -1)
        error("---> Problem binding the socket\n");


    printf("Enter message:\n");

    // zero out buffer (no need to null terminate now)
    memset(buf, 0, BUF_SIZ);

    // fill buffer
    int bytes_read = read(STDIN_FILENO, buf, BUF_SIZ);
    if (bytes_read < 0)
        error("Problem reading from STDIN\n");

    // send message
    int bytes_sent = sendto(sockfd, buf, strlen(buf) + 1, 0, (struct sockaddr *)&target, sizeof(struct sockaddr_in));
    if (bytes_sent < 0)
        error("---> Problem sending the message\n");

}

void error(char * mesg) {
    fprintf(stderr, "%s", mesg);
    perror("Error: ");
    exit(-1);
}
