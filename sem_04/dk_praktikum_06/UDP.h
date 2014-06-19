#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SERV_PORT 9877
#define MAXLINE 4096

struct sockaddr_in servaddr;
struct sockaddr_in cliaddr;

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int init_structs()
{
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(SERV_PORT);
}
