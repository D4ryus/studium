/* file: sem_04/algo_dat_praktikum_03/hash.c
 * author: d4ryus - https://github.com/d4ryus/
 * vim:foldmethod=syntax:
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float c        = 0.6180339887;
int   m        = 16384;
int   length   = 10;
int   datasets = 50;

typedef struct hash_node_t hash_node;

struct
hash_node_t
{
    int key;
    char* message;
    hash_node *next;
};

/* return's hash with size between 0 and max, generated out of k */
int
create_hash(int k, int max)
{
    return (int)( m * ( (float)k * c - ( (int)( (float)k * c ) ) ) ) % max;
}

/* insert's given message with key into given hashmap */
int
insert(hash_node** hashmap, int length, int key, char* message)
{
    int hash = create_hash(key, length);
    hash_node *node_ptr;
    if (hashmap[hash] == NULL)
    {
        hashmap[hash]          = malloc(sizeof(hash_node));
        hashmap[hash]->key     = key;
        hashmap[hash]->message = strdup(message);
    }
    else
    {
        if (hashmap[hash]->key == key)
        {
            free(hashmap[hash]->message);
            hashmap[hash]->message = strdup(message);
            return;
        }
        node_ptr = hashmap[hash];
        while(1)
        {
            if(node_ptr->next == NULL)
            {
                node_ptr->next = malloc(sizeof(hash_node));
                node_ptr->next->key = key;
                node_ptr->next->message = strdup(message);
                return;
            }
            if(node_ptr->next->key == key)
            {
                free(node_ptr->next->message);
                node_ptr->next->message = strdup(message);
                break;
            }
            node_ptr = node_ptr->next;
        }
    }
}

int
print_map(hash_node** hashmap, int length)
{
    hash_node *node_ptr;
    int i;
    for (i = 0; i < length; i++)
    {
        node_ptr = hashmap[i];
        if(node_ptr == NULL)
        {
            printf("%4d|\n", i);
            continue;
        }
        else
        {
            printf("%4d|%4d:\"%-10s\"", i, node_ptr->key, node_ptr->message);
            while(node_ptr->next != NULL)
            {
                printf(" +%4d:\"%-10s\"", node_ptr->next->key, node_ptr->message);
                node_ptr = node_ptr->next;
            }
            printf("\n");
        }
    }
}

/* free's hash_node and it's linked list */
void*
recursive_node_clean(hash_node* ptr)
{
    if (ptr->next != NULL)
        recursive_node_clean(ptr->next);
    if (ptr->message != NULL)
    {
        free(ptr->message);
        ptr->message = NULL;
    }
    if (ptr != NULL)
        free(ptr);
    return NULL;
}

/* free's given hashmap */
int
cleanup(hash_node** hashmap, int length)
{
    int i;
    for (i = 0; i < length; i++)
    {
        if(hashmap[i] != NULL)
            hashmap[i] = recursive_node_clean(hashmap[i]);
    }
}

/* will search through given hashmap for key, if not found NULL is returned */
hash_node*
find_node(hash_node** hashmap, int length, int key)
{
    hash_node *node_ptr;
    int i;
    for (i = 0; i < length; i++)
    {
        node_ptr = hashmap[i];
        if(node_ptr == NULL)
            continue;
        else
        {
            if(node_ptr->key == key)
                return node_ptr;
            while(node_ptr->next != NULL)
            {
                if(node_ptr->next->key == key)
                    return node_ptr->next;
                node_ptr = node_ptr->next;
            }
        }
    }
    return NULL;
}

int
print_node(hash_node* node, int length)
{
    if (node == NULL)
        printf("NULL\n");
    else
        printf("Hash: %d, Key: %d, Message: \"%s\"\n",
                                            create_hash(node->key, length),
                                            node->key,
                                            node->message);
}

int
main()
{
    hash_node *hashmap[length];
    int i;
    int key;
    int hash;
    srand (time(NULL));

    for (i = 0; i < length; i++)
        hashmap[i] = NULL;
    print_map(hashmap, length);
    printf("\n");

    for (i = 0; i < datasets; i++)
    {
        key = rand() % (datasets + 1);
        insert(hashmap, length, key, "first run");
    }
    print_map(hashmap, length);
    printf("\n");

    for (i = 0; i < datasets; i++)
    {
        key  = rand() % (datasets + 1);
        insert(hashmap, length, key, "second run");
    }
    print_map(hashmap, length);
    printf("\n");

    print_node(find_node(hashmap, length, 0), length);
    print_node(find_node(hashmap, length, 1), length);
    print_node(find_node(hashmap, length, 2), length);
    print_node(find_node(hashmap, length, 3), length);
    print_node(find_node(hashmap, length, 4), length);
    print_node(find_node(hashmap, length, 5), length);
    print_node(find_node(hashmap, length, 6), length);
    print_node(find_node(hashmap, length, 7), length);
    print_node(find_node(hashmap, length, 8), length);
    print_node(find_node(hashmap, length, 9), length);
    printf("\n");

    cleanup(hashmap, length);
    print_map(hashmap, length);
    printf("\n");
}
