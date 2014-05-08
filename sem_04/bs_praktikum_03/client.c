/* author: d4ryus - https://github.com/d4ryus/
 * file: client.c
 */
#include "mq.h"

int main()
{
    init();

    char msg_send[MAX_SIZE];
    char msg_received[MAX_SIZE];
    int client_pid = getpid();
    int thread_pid;

    sprintf(msg_send, "%d", client_pid);
    send(1, msg_send);
    printf("Sent: %s to %d\n", msg_send, 1);

    receive(client_pid, msg_received);
    printf("Received: %s from %s\n", msg_received, msg_received);

    sscanf(msg_received, "%d", &thread_pid);
    while(1)
    {
        fgets(msg_send, MAX_SIZE, stdin);
        if ( strlen(msg_send) != ( MAX_SIZE - 1 ) )
            msg_send[strlen(msg_send) - 1] = '\0';
        send(thread_pid, msg_send);
        if ( (msg_send[0] == '-') &&
             (msg_send[1] == '1') )
             break;
        printf("Sent: '%s' to %d\n", msg_send, thread_pid);
        receive(client_pid, msg_received);
        printf("Received: %s from %d\n", msg_received, thread_pid);
    }
    exit(0);
}
