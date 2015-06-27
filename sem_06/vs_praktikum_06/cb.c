#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#include "helper.h"
#include "cb.h"

/*
 * creates a new detachted thread and runs the given function with given
 * arguments
 */
void
run(void (*cb) (void *), void *arg)
{
	pthread_t thread;
	pthread_attr_t attr;

	/* init a pthread attribute struct */
	if (pthread_attr_init(&attr) != 0) {
		die(ERR_INFO, "pthread_attr_init()");
	}

	/* set threads to be detached, so they dont need to be joined */
	if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED) != 0) {
		die(ERR_INFO,
		    "pthread_attr_setdetachstate():PTHREAD_CREATE_DETACHED");
	}

	if (pthread_create(&thread, &attr, (void *(*) (void*))cb, arg) != 0) {
		die(ERR_INFO, "pthread_create()");
	}
}

/*
 * the given cb (call back) function will be called with a seperate thread after
 * timeout
 */
void
sleep_run(uint32_t timeout, void (*cb) (void *), void *arg)
{
	struct cb_data *data;

	data = malloc(sizeof(struct cb_data));
	data->call_back = cb;
	data->timeout = timeout;
	data->arg = arg;

	run(sleeper, data);
}

/* thread statring point, will sleep and then call callback */
void
sleeper(void *ptr)
{
	struct cb_data *data;

	data = ptr;
	usleep(data->timeout);
	data->call_back(data->arg);
	free(data);

	return NULL;
}
