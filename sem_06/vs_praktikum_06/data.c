#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>

#include "data.h"
#include "helper.h"

struct linked_list *
data_add(struct linked_list *first, uint32_t id, void *data)
{
	struct linked_list *cur;

	if (first == NULL) {
		first = malloc(sizeof(struct linked_list));
		cur = first;
	} else {
		cur = first;
		while (cur->next) {
			cur = cur->next;
		}
		cur->next = malloc(sizeof(struct linked_list));
		cur = cur->next;
	}

	cur->next = NULL;
	cur->id = id;
	cur->data = data;

	return first;
}

int
data_contains(struct linked_list *first, uint32_t id)
{
	struct linked_list *cur;

	cur = first;
	while (cur) {
		if (cur->id == id) {
			return 1;
		}
		cur = cur->next;
	}

	return 0;
}

struct linked_list *
data_remove(struct linked_list *first, uint32_t id, void **removed_data)
{
	struct linked_list *cur;

	if (first == NULL) {
		die(ERR_INFO, "tried to remove data on non existing list");
	}
	if (first->id == id) {
		*removed_data = first->data;
		first = first->next;
		return first;
	}
	cur = first;
	while (cur->next) {
		if (cur->next->id == id) {
			*removed_data = cur->next->data;
			cur->next = cur->next->next;
			return first;
		}
		cur = cur->next;
	}

	return first;
}

void *
data_get(struct linked_list *first, uint32_t id)
{
	struct linked_list *cur;

	cur = first;
	while (cur) {
		if (cur->id == id) {
			return cur->data;
		}
		cur = cur->next;
	}

	return 0;
}

void
data_free(struct linked_list *ll)
{
	struct linked_list *cur;
	struct linked_list *tmp;

	cur = ll;

	while (cur) {
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}

	return;
}

uint32_t
data_length(struct linked_list *ll)
{
	struct linked_list *cur;
	uint32_t length;

	length = 0;
	cur = ll;
	while (cur) {
		length ++;
		cur = cur->next;
	}

	return length;
}

void
data_print(struct linked_list *first, void (*print_fun) (void *))
{
	struct linked_list *cur;

	cur = first;
	while (cur) {
		printf("    id: %d\n", cur->id);
		if (print_fun != NULL) {
			print_fun(cur->data);
		}
		cur = cur->next;
	}
}
