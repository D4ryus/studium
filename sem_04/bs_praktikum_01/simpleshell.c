#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define BUFF_LENGTH 512
#define ARG_LENGTH 10


void error(char *msg) {
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main() {

    char buffer[BUFF_LENGTH] = "";
    const char delimeter[] = "\n\t ";
    char* args[ARG_LENGTH];

    while(1) {

        printf(">> ");

        if ( fgets(buffer, BUFF_LENGTH, stdin) == NULL ) {
            error ("error getting command");
        }

        if (buffer[0] == '\n') {
            continue;
        }

        args[0] = strtok(buffer, delimeter);
        int i;
        for (i = 1 ;; i++) {
            args[i] = strtok(NULL, delimeter);
            if (args[i] != NULL && i < ARG_LENGTH ) {
                continue;
            } else {
                break;
            }
        }

        if (!strcmp(args[0], "exit")) {
            exit(0);
        }

        pid_t pid;
        int pid_status;
        pid = fork();
        if(pid != 0) {
            if(waitpid(pid, &pid_status, 0) == -1) {
                error("Error waiting for child process");
            }
        } else if ( pid == 0 ){
            execvp(args[0], args);
        } else {
            error("error forking prozess");
        }
    }
}
