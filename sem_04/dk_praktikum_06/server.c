#include "UDP.h"

int main()
{
    init_structs();
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if(sockfd == -1)
        error("could not get a socket");

    if(bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == -1)
        error("could not bind socket");

    printf("listening on port %d\n", SERV_PORT);

    char buffer[MAXLINE];
    bzero(buffer, MAXLINE);

    while(buffer[0] != '-') {
        int length = sizeof(cliaddr);
        int msg_size = recvfrom(sockfd, buffer, MAXLINE, 0,
                                          (struct sockaddr*)&cliaddr, &length);
        buffer[msg_size] = '\0';
        printf("got message: %s\n", buffer);

        int  i;
        for(i = 0; i < strlen(buffer); i++)
            buffer[i] = toupper(buffer[i]);

        printf("sending message: %s\n", buffer);
        if( sendto(sockfd, buffer, strlen(buffer), 0,
                           (struct sockaddr*)&cliaddr, sizeof(cliaddr) ) == -1)
            error("could not send message");
    }
    printf("exiting...\n");

    close(sockfd);
    return 0;
}
