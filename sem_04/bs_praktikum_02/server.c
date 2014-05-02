/* author: d4ryus - https://github.com/d4ryus/
 * file: server.c
 */

#include "mq.h"

int main()
{
    init();

    char msg_send[MAX_SIZE];
    char msg_received[MAX_SIZE];
    int client_pid;

    sprintf(msg_send, "%d", getpid());

    while(1)
    {
        receive(1, msg_received);
        printf("Received: %s from %d\n", msg_received, 1);

        if ( (msg_received[0] == '-') &&
             (msg_received[1] == '1') )
            break;

        sscanf(msg_received, "%d", &client_pid);
        send(client_pid, msg_send);
        printf("Sent: %s to %d\n", msg_send, client_pid);
    }
    msgctl(msqid, IPC_RMID, 0);
    printf("exiting.\n");
    exit(0);
}
