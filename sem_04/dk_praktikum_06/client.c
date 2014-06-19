#include <arpa/inet.h>
#include "UDP.h"

int main(int argc, const char *argv[])
{
    if( argc < 2 ) {
        printf("usage: ./client [ip-from-server]\n");
        exit(1);
    }

    init_structs();
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd == -1)
        error("could not get a socket");

    char buffer[MAXLINE];
    bzero(buffer, MAXLINE);

    while(buffer[0] != '-') {
        fgets(buffer, MAXLINE - 1, stdin);
        buffer[strlen(buffer)-1] = '\0';

        printf("sending message: %s\n", buffer);
        if( sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr) ) == -1)
            error("could not send message");

        int msg_size = recvfrom(sockfd, buffer, MAXLINE, 0, NULL, NULL);
        buffer[msg_size] = '\0';
        printf("got message: %s\n", buffer);
    }
    printf("exiting...\n");

    close(sockfd);
    return 0;
}
