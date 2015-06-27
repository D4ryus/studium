#ifndef HELPER_H
#define HELPER_H

#define ERR_INFO __FILE__, __LINE__, __func__

#include <stdint.h>

void die(const char*, const int, const char *, const char *);
int starts_with(const char *, const char *, size_t);
double get_timestamp(void);
uint32_t generate_msg_id(void);

#endif
