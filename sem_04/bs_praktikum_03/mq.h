/* author: d4ryus - https://github.com/d4ryus/
 * file: mq.h
 */
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define MQ_KEY   0x1213214
#define MAX_SIZE 20

int msqid;

struct msgbuf
{
    long mtype;           /* msg type */
    char mtext[MAX_SIZE]; /* msg text */
};

void error(char *s)
{
  perror(s);
  exit(1);
}

void init()
{
    if ((msqid = msgget(MQ_KEY, IPC_CREAT | 0770)) < 0)
        error("could not execute msgget():");
}

void send(int msg_type, char* msg)
{
    struct msgbuf b;

    b.mtype = msg_type;
    strncpy(b.mtext, msg, MAX_SIZE);

    if (msgsnd(msqid, &b, MAX_SIZE, 0) < 0)
        error("could not execute msgsnd():");
}

void receive(int msg_type, char* msg)
{
    struct msgbuf b;

    if (msgrcv(msqid, &b, MAX_SIZE, msg_type, 0) < 0)
        error("could not execute msgrcv():");

    strncpy(msg, b.mtext, MAX_SIZE);
}
