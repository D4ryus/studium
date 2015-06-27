#ifndef MULTICAST_H
#define MULTICAST_H

#include <arpa/inet.h>

#define MSG_SIZE 128

void mc_setup_socket(const char *, const int);
void mc_close_socket(void);
ssize_t mc_read(char*, size_t);
void mc_send_register(int);
void mc_send_deregister(int);
void mc_send_register_ok(int);
void mc_send_request(uint32_t, uint32_t, double);
void mc_send_request_ok(uint32_t, uint32_t);
void mc_send_data(const char *, uint64_t);

#endif
