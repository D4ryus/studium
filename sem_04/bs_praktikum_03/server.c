/* author: d4ryus - https://github.com/d4ryus/
 * file: server.c
 */

#include "mq.h"
#include <pthread.h>

int count = 1;

void *handle_client(void * msg)
{
    int  thread_pid = count;
    char msg_received[MAX_SIZE];
    strncpy(msg_received, msg, MAX_SIZE);

    char msg_send[MAX_SIZE];
    int client_pid;

    sscanf(msg_received, "%d", &client_pid);

    printf("Created Thread: %d, which is connected to: %d\n",
                                                    thread_pid, client_pid);
    sprintf(msg_send, "%d", thread_pid);
    send(client_pid, msg_send);
    printf("Sent: %s to %d\n", msg_send, client_pid);

    while(1) {
        if ( (msg_received[0] == '-') &&
             (msg_received[1] == '1') )
        {
            printf("Closing Thread %d\n", thread_pid);
            pthread_exit(NULL);
        }
        receive(thread_pid, msg_received);
        printf("Received: '%s' from %d\n", msg_received, thread_pid);
        strncpy(msg_send, "got it!", MAX_SIZE);
        send(client_pid, msg_send);
        printf("Sent: %s to %d\n", msg_send, client_pid);
    }
}

int main()
{
    init();

    char msg_received[MAX_SIZE];

    while(1)
    {
        receive(1, msg_received);
        count++;
        printf("Received: %s from %s\n", msg_received, msg_received);

        pthread_t thread;
        if( pthread_create(&thread, NULL, &handle_client, (void *)msg_received) != 0)
            error("couldn't create thread\n");
        pthread_setname_np(thread, msg_received);
    }
    msgctl(msqid, IPC_RMID, 0);
    printf("exiting.\n");
    exit(0);
}
