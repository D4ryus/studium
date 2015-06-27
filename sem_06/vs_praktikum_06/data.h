#ifndef DATA_H
#define DATA_H

#include <stdint.h>

struct linked_list {
	struct linked_list *next;
	uint32_t id;
	void *data;
};

struct linked_list *data_add(struct linked_list *, uint32_t, void *);
int data_contains(struct linked_list *, uint32_t);
struct linked_list *data_remove(struct linked_list *, uint32_t, void **);
void *data_get(struct linked_list *, uint32_t);
void data_free(struct linked_list *);
uint32_t data_length(struct linked_list *);
void data_print(struct linked_list *, void (*) (void *));

#endif
