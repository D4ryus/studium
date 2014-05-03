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

char ss[] = "Sender sends: ";
char rs[] = "Receiver sends: ";

char message_sender[] = "TheQuickBrownFoxOle";
char message_receiver[] = "JumpsOverTheLazyDog";

int state = 0;
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

/*
 * parrent/sender will
 * write to first_pipe[1]
 * read from second_pipe[0] and
 */
int sender(pid_t pid)
{
    char control_bit;
    char msg[MSG_LEN];

    control_bit = '0';
    msg[0] = message_sender[cursor];
    msg[1] = control_bit;
    msg[2] = '\0';
    cursor++;
    write(second_pipe[1], msg, MSG_LEN);
    kill(pid, SIGUSR1);

    state = 1;
    while(strlen(message_sender) > cursor)
    {
        pause();
        switch(state)
        {
            case 1:
                control_bit = '1';
                msg[0] = message_sender[cursor];
                msg[1] = control_bit;
                msg[2] = '\0';
                state = 2;
                break;
            case 2:
                control_bit = '0';
                msg[0] = message_sender[cursor];
                msg[1] = control_bit;
                msg[2] = '\0';
                state = 1;
                break;
        }
        cursor++;
        write(second_pipe[1], msg, MSG_LEN);
        kill(pid, SIGUSR1);
    }
}

/*
 * child/receiver will
 * write to second_pipe[1]
 * read from first_pipe[0] and
 */
int receiver()
{
    char control_bit;
    char msg[MSG_LEN];
    int ppid = getppid();
    state = 1;
    while(strlen(message_receiver) > cursor)
    {
        pause();
        switch(state)
        {
            case 1:
                control_bit = '0';
                msg[0] = message_receiver[cursor];
                msg[1] = control_bit;
                msg[2] = '\0';
                state = 2;
                break;
            case 2:
                control_bit = '1';
                msg[0] = message_receiver[cursor];
                msg[1] = control_bit;
                msg[2] = '\0';
                state = 1;
                break;
        }
        cursor++;
        write(first_pipe[1], msg, MSG_LEN);
        kill(ppid, SIGUSR2);
    }
}

void abp_sender()
{
    char msg_buf[BUF_LEN];

    if(read(first_pipe[0], msg_buf, MSG_LEN) == -1)
        error("abp_sender read error");

    write(STDIN_FILENO, rs, sizeof(rs)-1);
    msg_buf[2] = '\n';
    write(STDIN_FILENO, msg_buf, sizeof(msg_buf));
}

void abp_receiver()
{
    char msg_buf[BUF_LEN];

    if(read(second_pipe[0], msg_buf, MSG_LEN) == -1)
        error("abp_receiver read error");

    write(STDIN_FILENO, ss, sizeof(ss)-1);
    msg_buf[2] = '\n';
    write(STDIN_FILENO, msg_buf, sizeof(msg_buf));
}

int main()
{

    struct sigaction actionsender       = {0};
    struct sigaction actionreceiver     = {0};

    if(pipe(first_pipe) == -1 || pipe(second_pipe) == -1)
        error("Can't open pipe");

    pid_t pid = fork();

    if((pid < 0))
        error("unexpected fork error:");
    else if (pid == 0)
    {
        /* child/receiver process */
        close(first_pipe[0]);       /* close pipes from parent prozess */
        close(second_pipe[1]);

        actionreceiver.sa_handler = abp_receiver;
        sigaction(SIGUSR1, &actionreceiver, 0);

        receiver();

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
