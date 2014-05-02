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
    struct msgbuf buffer;

    buffer.mtype = msg_type;
    strncpy(buffer.mtext, msg, MAX_SIZE);

    if (msgsnd(msqid, &buffer, MAX_SIZE, 0) < 0)
        error("could not execute msgsnd():");
}

void receive(int msg_type, char* msg)
{
    struct msgbuf buffer;

    if (msgrcv(msqid, &buffer, MAX_SIZE, msg_type, 0) < 0)
        error("could not execute msgrcv():");

    strncpy(msg, buffer.mtext, MAX_SIZE);
}
