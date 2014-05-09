/* file: abp.c
 * author: d4ryus - https://github.com/d4ryus/
 * vim:foldmethod=syntax:foldcolumn=5:
 */
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define BUF_LEN 3
#define MSG_LEN 3

char message_sender[]    = "TheQuickBrownFoxOle";
char message_responder[] = "JumpsOverTheLazyDog";

//int RANDOM = 10; /* 10% */
int RANDOM = 5;  /* 20% */
//int RANDOM = 2;  /* 50% */

int state  = 0;
int cursor = 0;

/* child write, parrent read */
int first_pipe[2];
/* parrent write, child read */
int second_pipe[2];

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int sender(pid_t pid)
{
    char msg[MSG_LEN];

    msg[0] = message_sender[cursor];
    msg[1] = '0';
    msg[2] = '\0';
    cursor++;
    write(second_pipe[1], msg, MSG_LEN);
    kill(pid, SIGUSR1);

    printf("Sender sends: %s\n", msg);

    state = 1;
    while(strlen(message_sender) > cursor)
    {
        pause();
        switch(state)
        {
            case 1:
                msg[1] = '1';
                break;
            case 2:
                msg[1] = '0';
                break;
        }
        msg[0] = message_sender[cursor];
        alarm(1);

        if(rand() % RANDOM != 1)
        {
            write(second_pipe[1], msg, MSG_LEN);
            kill(pid, SIGUSR1);
        }

        printf("Sender sends: %s\n", msg);
    }
}

int responder()
{
    char msg[MSG_LEN];
    int pid = getppid();
    msg[2] = '\0';

    state = 2;
    while(strlen(message_responder) > cursor)
    {
        pause();
        switch(state)
        {
            case 1:
                msg[1] = '0';
                break;
            case 2:
                msg[1] = '1';
                break;
        }
        msg[0] = message_responder[cursor];
        alarm(1);

        if(rand() % RANDOM != 1)
        {
            write(first_pipe[1], msg, MSG_LEN);
            kill(pid, SIGUSR2);
        }

        printf("Responder sends: %s\n", msg);
    }
}

void abp_alarm()
{
}

void set_state(char* msg)
{
    if      ((state == 1) && (msg[1] == '0'))
    {
        state = 2;
        cursor++;
    }
    else if ((state == 2) && (msg[1] == '1'))
    {
        state = 1;
        cursor++;
    }
}

void abp_sender()
{
    char b[BUF_LEN];

    if(read(first_pipe[0], b, MSG_LEN) == -1)
        error("abp_sender read error");

    printf("Sender received: %s\n", b);

    set_state(b);
}

void abp_responder()
{
    char b[BUF_LEN];

    if(read(second_pipe[0], b, MSG_LEN) == -1)
        error("abp_responder read error");

    printf("Responder received: %s\n", b);

    set_state(b);
}

int main()
{
    struct sigaction actionsender    = {0};
    struct sigaction actionresponder = {0};

    struct sigaction actionalarm = {0};

    actionalarm.sa_handler = abp_alarm;
    sigaction(SIGALRM, &actionalarm, 0);

    if(pipe(first_pipe) == -1 || pipe(second_pipe) == -1)
        error("Can't open pipe");

    pid_t pid = fork();

    if((pid < 0))
        error("unexpected fork error:");
    else if (pid == 0)
    {
        /* child/responder process */
        close(first_pipe[0]);       /* close pipes from parent prozess */
        close(second_pipe[1]);

        actionresponder.sa_handler = abp_responder;
        sigaction(SIGUSR1, &actionresponder, 0);

        responder();

        sleep(2);
        close(first_pipe[1]);
        close(second_pipe[0]);
        exit(0);
    }
    else
    {
        /* parrent/sender processs */
        close(first_pipe[1]);       /* close pipes from child prozess */
        close(second_pipe[0]);

        actionsender.sa_handler       = abp_sender;
        sigaction(SIGUSR2, &actionsender,       0);

        sleep(1);
        sender(pid);

        sleep(2);
        close(first_pipe[0]);
        close(second_pipe[1]);
        exit(0);
    }
    int pid_status;
    if(waitpid(pid, &pid_status, 0) == -1)
        error("Error waiting for child process");
}
