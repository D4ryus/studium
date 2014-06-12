/*
 * author: d4ryus https://github.com/d4ryus
 * file: main.c
 * vim:foldmethod=syntax:
 */
#include <stdio.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <string.h>
#include <stdlib.h>


#define MAX 30
int shm_key = 828282;

typedef struct
_buffer_entry
{
    int id;
    int number;
    char msg[20];
} buffer_entry;

typedef struct
_shared_buffer
{
    buffer_entry entry[MAX];
    int in;
    int out;
    sem_t full;
    sem_t empty;
    sem_t mutex;
} shared_buffer;

void
add_entry(shared_buffer* ptr, int id, int number, char* msg)
{
    sem_wait(&ptr->empty);
    sem_wait(&ptr->mutex);

            ptr->entry[ptr->in].id     = id;
            ptr->entry[ptr->in].number = number;
    strncpy(ptr->entry[ptr->in].msg,     msg, strlen(msg));

    ptr->in = (ptr->in + 1) % MAX;

    sem_post(&ptr->mutex);
    sem_post(&ptr->full);
}

buffer_entry*
take_entry(shared_buffer* ptr)
{
    buffer_entry* tmp = malloc(sizeof(buffer_entry));

    sem_wait(&ptr->full);
    sem_wait(&ptr->mutex);

            tmp->id     = ptr->entry[ptr->out].id;
            tmp->number = ptr->entry[ptr->out].number;
    strncpy(tmp->msg,     ptr->entry[ptr->out].msg, strlen(ptr->entry[ptr->out].msg));

    ptr->out = (ptr->out + 1) % MAX;

    sem_post(&ptr->mutex);
    sem_post(&ptr->empty);

    return tmp;
}

int
main()
{
    // create memory
    int shm_id = shmget(shm_key, sizeof(shared_buffer), IPC_CREAT | 0666);
    if(shm_id == -1)
    {
        printf("could not create shared memory\n");
        exit(0);
    }

    // attach memory
    shared_buffer* ptr = shmat(shm_id, 0, 0);
    if ((char *)ptr == (char *) -1)
    {
        printf("could not attach shared memory\n");
        exit(0);
    }

    // set default values
    ptr->in  = 0;
    ptr->out = 0;

    // create semaphore
    if (     ( sem_init(&ptr->mutex, 1, 1  ) < 0 )
          || ( sem_init(&ptr->full,  1, 0  ) < 0 )
          || ( sem_init(&ptr->empty, 1, MAX) < 0 ) )
    {
        printf("semaphore initilization\n");
        exit(0);
    }

    // detach memory
    shmdt(ptr);

    int id = fork();
    if(id == -1)
    {
        printf("could not fork\n");
        exit(0);
    }

    ptr = shmat(shm_id, 0, 0);
    if (id == 0)
    {
        // child process
        buffer_entry* tmp;
        while(1)
        {
            tmp = take_entry(ptr);
            printf("took an entry %d - %2d - %s\n", tmp->id, tmp->number, tmp->msg);
            if(tmp->number == 99)
                break;
            free(tmp);
        }
        printf("exiting!\n");
    }
    else
    {
        // parent process
        int i;
        for (i = 0; i < 100; i++)
        {
            add_entry(ptr, getpid(), i, "---");
            printf("added entry %d\n", i);
        }
        printf("exiting!\n");
        exit(0);
    }
    shmctl(shm_id, IPC_RMID, NULL);
}
