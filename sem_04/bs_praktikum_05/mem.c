/*
 * author: d4ryus https://github.com/d4ryus
 * file: mem.c
 * vim:foldmethod=syntax:
 */
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _memblk memblk;

typedef struct
_memblk
{
    int pid;
    int size;
    int alloc_size;
    memblk* left;
    memblk* right;
} memblk;

memblk* head = NULL;

int
add(const int id, const int alloc_size, memblk* ptr)
{
    if(ptr->alloc_size > 0)
        return -1;

    if(ptr->size/2 >= alloc_size)
    {
        if(ptr->left == NULL)
        {
            ptr->left                       = malloc(sizeof(memblk));
            ptr->left->size                 = ptr->size/2;
            ptr->left->alloc_size           = 0;
            ptr->left->left                 = NULL;
            ptr->left->right                = NULL;
            add(id, alloc_size, ptr->left);
            return 1;
        }
        if(add(id, alloc_size, ptr->left) != -1)
            return 1;

        if(ptr->right == NULL)
        {
            ptr->right             = malloc(sizeof(memblk));
            ptr->right->size       = ptr->size/2;
            ptr->right->alloc_size = 0;
            ptr->right->left       = NULL;
            ptr->right->right      = NULL;
            add(id, alloc_size, ptr->right);
            return 1;
        }
        if(add(id, alloc_size, ptr->right) != -1)
            return 1;

        return -1;
    }

    if((ptr->left == NULL) && (ptr->right == NULL))
    {
        ptr->alloc_size = alloc_size;
        ptr->pid = id;
        return 1;
    }

    return -1;
}

int
print_mem(memblk* ptr)
{
    int i;
    if(ptr->alloc_size > 0)
    {
        for (i = 0; i < ptr->alloc_size; i++)
            printf("#");
        for (i = 0; i < (ptr->size - ptr->alloc_size); i++)
            printf("-");
        return 1;
    }
    if(ptr->left != NULL)
    {
        print_mem(ptr->left);
    }
    else
        for (i = 0; i < ptr->size/2; i++)
            printf("=");

    if((ptr->left != NULL) || (ptr->right != NULL))
        printf("|");

    if(ptr->right != NULL)
        print_mem(ptr->right);
    else
        for (i = 0; i < ptr->size/2; i++)
            printf("=");
}

int
del(const int id, memblk* ptr)
{
    if(ptr->left != NULL)
    {
        if(ptr->left->pid == id)
        {
            free(ptr->left);
            ptr->left = NULL;
            return 1;
        }
        if(del(id, ptr->left) != -1)
            return 1;
    }

    if(ptr->right != NULL)
    {
        if(ptr->right->pid == id)
        {
            free(ptr->right);
            ptr->right = NULL;
            return 1;
        }
        if(del(id, ptr->right)!= -1)
            return 1;
    }
    return -1;
}

int
rec_clean(memblk* ptr)
{
    if(ptr->left != NULL)
        rec_clean(ptr->left);

    if(ptr->right != NULL)
        rec_clean(ptr->right);

    if((ptr->left == NULL) && (ptr->right == NULL))
        return 1;

    if(ptr->left != NULL)
    {
        if(    (ptr->left->alloc_size == 0)
            && (ptr->left->left       == NULL)
            && (ptr->left->right      == NULL))
        {
            free(ptr->left);
            ptr->left = NULL;
        }
        else
            rec_clean(ptr->left);
    }

    if(ptr->right != NULL)
    {
        if(    (ptr->right->alloc_size == 0)
            && (ptr->right->left       == NULL)
            && (ptr->right->right      == NULL))
        {
            free(ptr->right);
            ptr->right = NULL;
        }
        else
            rec_clean(ptr->right);
    }
}

int
main(int argc, const char *argv[])
{
    if (argc <= 1)
    {
        printf("usage: ./mem [memory size]\n");
        exit(1);
    }

    int size;
    sscanf(argv[1], "%d", &size);
    printf("entered size: %d\n", size);

    int i;
    int x = 2;
    int flag = 0;
    for (i = 0; i < 100; i++) // check if size is 2^x
    {
        if(x != size)
        {
            x *= 2;
            continue;
        }
        else
        {
            flag = 1;
            break;
        }
    }

    if(!flag)
    {
        printf("entered value is not a acceptable memory size!\n");
        exit(1);
    }

    // malloc first element from linked list (full memory)
    head = malloc(sizeof(memblk));
    head->size       = size;
    head->pid        = 0;
    head->alloc_size = 0;
    head->right      = NULL;
    head->left       = NULL;

    srand(time(NULL));
    printf("[");
    print_mem(head);
    printf("]\n\n");
    for (i = 1; i < 11; i++)
    {
        int value = rand() % (size/4) + 1;
        if(add(i, value, head) != -1)
            printf("added %d\n", value);
        else
            printf("could not add %d\n", value);
        printf("[");
        print_mem(head);
        printf("]\n\n");
    }

    for (i = 10; i > 0; i--)
    {
        if(del(i, head) != -1)
            printf("deleted id %d\n", i);
        else
            printf("could not delete id %d\n", i);
        rec_clean(head);
        printf("[");
        print_mem(head);
        printf("]\n\n");
    }

    return 0;
}
