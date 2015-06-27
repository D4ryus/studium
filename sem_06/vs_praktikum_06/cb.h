#ifndef CB_H
#define CB_H

#include <stdint.h>

typedef void (*cb_fun) (void *);

/* hold call_back data */
struct cb_data {
	cb_fun call_back;
	void *arg;
	uint32_t timeout;
};

void run(void (*) (void *), void *);
void sleep_run(uint32_t, void (*) (void *), void *);
void sleeper(void *);

#endif
