#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/time.h>

#include "helper.h"
#include "cb.h"
#include "multicast.h"
#include "data.h"

/* linked lists for client, blocked resource and wanted resources */
struct linked_list *ll_cli;
struct linked_list *ll_res;
struct linked_list *ll_wan;

/* mutexes for each linkedlist */
static pthread_mutex_t m_cli;
static pthread_mutex_t m_res;
static pthread_mutex_t m_wan;

uint16_t multicast_port;
char *multicast_address;
int PID;

int main(int, const char**);
void init(int, const char**);
void handle_requests(void *);
void handle_register(char *);
void handle_register_ok(char *);
void handle_deregister(char *);
void handle_request(char *);
void handle_request_ok(char *);
void parse_user_input(char *);
void queue_request(struct linked_list *, uint32_t, uint32_t);
void free_resource(void *);
struct resource *gen_res(uint32_t, uint32_t *);
struct wanted *gen_wan(uint32_t, uint32_t, double, int, int);
void print_resource(void *);
void print_wanted(void *);

/* contains lcoked resources */
struct resource {
	uint32_t q_size;
	uint32_t *queue;
};

/* contains wanted resources */
struct wanted {
	uint32_t q_size;
	uint32_t *queue;
	uint32_t msg_id;
	uint32_t block_time;
	double timestamp;
	int ok_needed;
	int ok_count;
};

int
main(int argc, const char *argv[])
{
	char msg[256];

	init(argc, argv);
	memset(msg, 0, 256);
	/* will create thread which calls handle_incomming_messages */
	run(handle_requests, NULL);

	printf(
	    "%d>> started client with PID %d\n"
	    "    Possible commands:\n"
	    "        register (sends out a register to others)\n"
	    "        deregister (tells others that u left)\n"
	    "        request res_id block_time (requests the given resource, \n"
	    "                                   on success blocks for given\n"
	    "                                   time)\n"
	    "        list (c|w|b) (prints out list of other clients, wanted\n"
	    "                      wanted resources or blocked resources)\n"
	    "        quit (sends deregister and quits the client)\n"
	    , PID, PID);
	mc_send_register(PID);
	do {
		memset(msg, 0, 256);
		fgets(msg, 256, stdin);
		parse_user_input(msg);
	} while (strcmp(msg, "quit\n") != 0);

	printf("%d>> sending deregister\n", PID);
	mc_send_deregister(PID);
	mc_close_socket();

	return 0;
}

void
init(int argc, const char *argv[])
{
	size_t length;
	struct timeval t;

	if (argc < 3) {
		printf("usage: %s multicast_adress multicast_port\n", argv[0]);
		exit(1);
	}

	ll_cli = NULL;
	ll_res = NULL;
	ll_wan = NULL;

	gettimeofday(&t, NULL);
	srand((unsigned int)((t.tv_sec * 1000) + (t.tv_usec / 1000)));

	pthread_mutex_init(&m_cli, NULL);
	pthread_mutex_init(&m_res, NULL);

	length = strlen(argv[1]);
	multicast_address = malloc(length + 1);
	memset(multicast_address, '\0', length);
	strncpy(multicast_address, argv[1], length);
	multicast_port = (uint16_t)atoi(argv[2]);

	PID = getpid();
	mc_setup_socket(multicast_address, multicast_port);
}

/* handles all incomming requests from multicast socket */
void
handle_requests(void *arg)
{
	char msg[MSG_SIZE];
	ssize_t read;

	while (1) {
		memset(msg, '\0', MSG_SIZE);
		read = mc_read(msg, MSG_SIZE);
		if (read == -1) {
			die(ERR_INFO, "recv()");
		}
		printf("    multicast: %s\n", msg);
		if (starts_with(msg, "register_ok", 11)) {
			handle_register_ok(msg + 11);
		} else if (starts_with(msg, "register", 8)) {
			handle_register(msg + 8);
		} else if (starts_with(msg, "request_ok", 10)) {
			handle_request_ok(msg + 10);
		} else if (starts_with(msg, "request", 7)) {
			handle_request(msg + 7);
		} else if (starts_with(msg, "deregister", 10)) {
			handle_deregister(msg + 10);
		} else {
			die(ERR_INFO, "got msg on from socket i cannot parse");
		}
	}
}

void
handle_register(char *input)
{
	uint32_t client_pid;

	sscanf(input, " %u", &client_pid);
	pthread_mutex_lock(&m_cli);
	if (!data_contains(ll_cli, client_pid)) {
		ll_cli = data_add(ll_cli, client_pid, NULL);
	}
	pthread_mutex_unlock(&m_cli);
	if (client_pid != (uint32_t)PID) {
		mc_send_register_ok(PID);
	}
}

void
handle_register_ok(char *input)
{
	uint32_t client_pid;

	sscanf(input, " %u", &client_pid);
	pthread_mutex_lock(&m_cli);
	if (!data_contains(ll_cli, client_pid)) {
		ll_cli = data_add(ll_cli, client_pid, NULL);
	}
	pthread_mutex_unlock(&m_cli);
}

void
handle_deregister(char *input)
{
	uint32_t client_pid;
	struct linked_list *rem;

	sscanf(input, " %u", &client_pid);
	pthread_mutex_lock(&m_cli);
	ll_cli = data_remove(ll_cli, client_pid, (void **)&rem);
	pthread_mutex_unlock(&m_cli);
	free(rem);
}

void
handle_request(char *input)
{
	uint32_t msg_id;
	uint32_t res_id;
	double timestamp;

	sscanf(input, " %u %u %lf", &msg_id, &res_id, &timestamp);

	pthread_mutex_lock(&m_wan);
	if (data_contains(ll_wan, res_id)) {
		/* i want the ressource too */
		struct wanted *cur;

		cur = (struct wanted *)data_get(ll_wan, res_id);
		pthread_mutex_unlock(&m_wan);

		/* my own request msg */
		if (cur->msg_id == msg_id) {
			mc_send_request_ok(msg_id, res_id);
			return;
		}
		/* in case timestamp is the same a simple
		 * compare wont be enough, since both clients
		 * would send a ok because they are mirrored */
		if (cur->timestamp == timestamp) {
			if (cur->msg_id > msg_id) {
				timestamp += 1;
			} else {
				timestamp -= 1;
			}
		}
		if (cur->timestamp < timestamp) {
			pthread_mutex_lock(&m_res);
			queue_request(ll_wan, res_id, msg_id);
			pthread_mutex_unlock(&m_res);
		} else {
			struct wanted *rem;

			pthread_mutex_lock(&m_res);
			ll_wan = data_remove(ll_wan, res_id, (void **)&rem);
			pthread_mutex_unlock(&m_res);
			free(rem);
			mc_send_request_ok(msg_id, res_id);
		}
		return;
	} else {
		pthread_mutex_unlock(&m_wan);
	}
	pthread_mutex_lock(&m_res);
	if (data_contains(ll_res, res_id)) {
		/* i have the resource */
		queue_request(ll_res, res_id, msg_id);
	} else {
		/* i dont have the resource */
		mc_send_request_ok(msg_id, res_id);
	}
	pthread_mutex_unlock(&m_res);
}

void
handle_request_ok(char *input)
{
	uint32_t msg_id;
	uint32_t res_id;

	sscanf(input, " %u %u", &msg_id, &res_id);
	pthread_mutex_lock(&m_wan);
	if (data_contains(ll_wan, res_id)) {
		struct wanted *wan;

		pthread_mutex_unlock(&m_wan);
		wan = (struct wanted *)data_get(ll_wan, res_id);
		if (wan->msg_id != msg_id) {
			return;
		}
		if (++wan->ok_count == wan->ok_needed) {
			struct resource *res;
			uint32_t *res_id_callback;

			// generate a new entry on resource list
			res = gen_res(wan->q_size, wan->queue);
			pthread_mutex_lock(&m_res);
			ll_res = data_add(ll_res, res_id, res);
			pthread_mutex_unlock(&m_res);

			/* have to make id persistent cause it
			 * would go out of scope before callback
			 * thread could read it */
			res_id_callback = malloc(sizeof(uint32_t));
			*res_id_callback = res_id;

			printf("%d>> blocking %u, for %ums\n", PID, res_id,
			    wan->block_time / 1000);

			/* kick of callback */
			sleep_run(wan->block_time, free_resource,
			    res_id_callback);

			/* remove resource from wanted list */
			pthread_mutex_lock(&m_wan);
			ll_wan = data_remove(ll_wan, res_id, (void **)&wan);
			pthread_mutex_unlock(&m_wan);
			free(wan);
		}
	} else {
		pthread_mutex_unlock(&m_wan);
	}
}

void
parse_user_input(char* input)
{
	if (starts_with(input, "register", 8)) {
		mc_send_register(PID);
	} else if (starts_with(input, "deregister", 10)) {
		mc_send_deregister(PID);
	} else if (starts_with(input, "request", 7)) {
		struct wanted *wan;
		uint32_t res_id;

		pthread_mutex_lock(&m_cli);
		wan = gen_wan(generate_msg_id(), 0, get_timestamp(),
		    (int)data_length(ll_cli), 0);
		pthread_mutex_unlock(&m_cli);

		sscanf(input, "%*s %u %u", &res_id, &(wan->block_time));
		if (res_id == 0 || wan->block_time == 0) {
			printf("usage: request res_id block_time (in ms)\n");
			free(wan);
			return;
		}
		wan->block_time *= 1000;

		pthread_mutex_lock(&m_wan);
		ll_wan = data_add(ll_wan, res_id, (void *)wan);
		pthread_mutex_unlock(&m_wan);

		mc_send_request(wan->msg_id, res_id,
		    wan->timestamp);

		pthread_mutex_lock(&m_wan);
		printf("%d>> wanted_list:\n", PID);
		data_print(ll_wan, print_wanted);
		pthread_mutex_unlock(&m_wan);
	} else if (starts_with(input, "list", 4)) {
		char type;

		sscanf(input, "%*s %c", &type);
		switch (type) {
			case 'c':
				printf("%d>> clients:\n", PID);
				pthread_mutex_lock(&m_cli);
				data_print(ll_cli, NULL);
				pthread_mutex_unlock(&m_cli);
				break;
			case 'w':
				printf("%d>> wanted resources: \n", PID);
				pthread_mutex_lock(&m_wan);
				data_print(ll_wan, print_wanted);
				pthread_mutex_unlock(&m_wan);
				break;
			case 'b':
				printf("%d>> blocked resources: \n", PID);
				pthread_mutex_lock(&m_res);
				data_print(ll_res, print_resource);
				pthread_mutex_unlock(&m_res);
				break;
			default:
				printf("specify a type: c (clients), "
				    "w (wanted resources), "
				    "b (blocked resources)\n");
				break;
		}
	}
}

/* adds the given msg_id to the given res_id-data's queue */
void
queue_request(struct linked_list *first, uint32_t res_id, uint32_t msg_id)
{
	struct resource *res;

	res = data_get(first, res_id);
	res->queue = realloc(res->queue, sizeof(uint32_t)
		           * res->q_size + 1);
	res->queue[res->q_size] = msg_id;
	res->q_size++;

	return;
}

/* callback function which frees the ressource */
void
free_resource(void *ptr)
{
	uint32_t res_id;
	struct resource *cur;
	struct resource *rem;
	uint32_t i;

	res_id = *(uint32_t *)ptr;
	pthread_mutex_lock(&m_res);
	cur = data_get(ll_res, res_id);
	pthread_mutex_unlock(&m_res);
	if (cur == NULL) {
		die(ERR_INFO, "locked ressource not found\n");
		return;
	}
	for (i = 0; i < cur->q_size; i++) {
		mc_send_request_ok(cur->queue[i], res_id);
	}
	pthread_mutex_lock(&m_res);
	ll_res = data_remove(ll_res, res_id, (void **)&rem);
	pthread_mutex_unlock(&m_res);

	printf("%d>> removed resource %d from blocked list\n", PID, res_id);
	free(rem);
	free(ptr);

	return;
}

/* generates a struct resource with given data */
struct resource *
gen_res(uint32_t q_size, uint32_t *queue)
{
	struct resource *ret;

	ret = malloc(sizeof(struct resource));
	ret->q_size = q_size;
	ret->queue = queue;

	return ret;
}

/* generates a struct wanted with given data */
struct wanted *
gen_wan(uint32_t msg_id, uint32_t block_time, double timestamp, int ok_needed,
    int ok_count)
{
	struct wanted *ret;

	ret = malloc(sizeof(struct wanted));
	ret->q_size = 0;
	ret->queue = NULL;
	ret->msg_id = msg_id;
	ret->block_time = block_time;
	ret->timestamp = timestamp;
	ret->ok_needed = ok_needed;
	ret->ok_count = ok_count;

	return ret;
}

/* prints a struct resource */
void
print_resource(void *ptr)
{
	uint32_t i;
	struct resource *data;

	data = (struct resource *)ptr;
	printf("        queue:\n");
	for (i = 0; i < data->q_size; i++ ) {
		printf("            %u\n", data->queue[i]);
	}

	return;
}

/* prints a struct wanted */
void
print_wanted(void *ptr)
{
	struct wanted *data;

	data = (struct wanted *)ptr;
	printf("        msg_id: %u\n"
	       "        block_time: %ums\n"
	       "        timestamp: %lf\n"
	       "        ok_needed: %d\n"
	       "        ok_count: %d\n",
		data->msg_id,
		data->block_time / 1000,
		data->timestamp,
		data->ok_needed,
		data->ok_count);

	return;
}
