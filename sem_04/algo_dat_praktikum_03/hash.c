#include <stdio.h>
#include <stdlib.h>

float c        = 0.6180339887;
int   m        = 16384;
int   length   = 1000;
int   datasets = 100000;

typedef struct hash_node hash_node_t;

struct hash_node
{
    int key;
    hash_node_t *next;
};

int create_hash(int k)
{
    return (int)( m * ( (float)k * c - ( (int)( (float)k * c ) ) ) ) % length;
}

int main()
{
    hash_node_t *hashmap[length];

    int i;
    for (i = 0; i < length; i++)  // init all structs with NULL pointer
        hashmap[i] = NULL;

    int key;
    int hash;
    hash_node_t *node_ptr;
    srand (time(NULL));
    for (i = 0; i < datasets; i++)  // fill hashmap with random values
    {
        key  = rand() % (datasets + 1);
        hash = create_hash(key);
        if (hashmap[hash] == NULL)
        {
            hashmap[hash] = malloc(sizeof(hash_node_t));
            hashmap[hash]->key = key;
        }
        else
        {
            node_ptr = hashmap[hash];
            while(node_ptr->next != NULL)
                node_ptr = node_ptr->next;

            node_ptr->next = malloc(sizeof(hash_node_t));
            node_ptr->next->key = key;
        }
    }

    for (i = 0; i < length; i++)  // print hashmap
    {
        node_ptr = hashmap[i];
        if(node_ptr == NULL)
        {
            printf("%5d|\n", i);
            continue;
        }
        else
        {
            printf("%5d| %5d", i, node_ptr->key);
            while(node_ptr->next != NULL)
            {
                printf(" + %5d", node_ptr->next->key);
                node_ptr = node_ptr->next;
            }
            printf("\n");
        }
    }
}
