#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#include "helper.h"

void
die(const char *file, const int line, const char *function,
    const char *msg)
{
	fprintf(stderr, "%s:%d:%s: error: %s: %s\n",
	    file, line, function, msg, strerror(errno));
	exit(1);
}

/*
 * check if first string starts with second string
 */
int
starts_with(const char *line, const char *prefix, size_t prefix_length)
{
	size_t i;

	if (line == NULL || prefix == NULL) {
		return 0;
	}

	for (i = 0; i < prefix_length; i++) {
		if (prefix[i] != line[i]) {
			return 0;
		}
	}

	return 1;
}

double
get_timestamp()
{
	struct timeval tv;
	double result;
	char msg[32];

	memset(msg, '\0', 32);
	gettimeofday(&tv,NULL);
	snprintf(msg, 32, "%ld.%lu", tv.tv_sec, tv.tv_usec);
	result = strtod(msg, NULL);

	return result;
}

/* returns a generated msg_id which will be random but not zero */
uint32_t
generate_msg_id()
{
	uint32_t msg_id;

	do {
	    msg_id = (uint32_t)rand();
	} while (msg_id == 0);

	return msg_id;
}
