/* author: d4ryus - https://github.com/d4ryus/
 * file: client.c
 */
#include "mq.h"

int main()
{
    init();

    char msg_send[MAX_SIZE];
    char msg_received[MAX_SIZE];

    sprintf(msg_send, "%d", getpid());

    int i;
    for(i = 0; i < 10; i++)
    {
        send(1, msg_send);
        printf("Sent: %s to %d\n", msg_send, 1);
        receive(getpid(), msg_received);
        printf("Received: %s from %d\n", msg_received, getpid());
    }

    sprintf(msg_send, "%d", -1);
    send(1, msg_send);

    exit(0);
}
