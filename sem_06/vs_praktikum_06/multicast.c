#include <stdio.h>
#include <string.h>

#include "helper.h"
#include "multicast.h"

static struct sockaddr_in address;
static struct sockaddr_in mc_sin;
static struct ip_mreq command;
static socklen_t sin_len;
int sock;

void
mc_setup_socket(const char *ip, const int port)
{
	int loop;

	memset(&command, 0, sizeof(struct ip_mreq));
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ip);
	address.sin_port = htons(port);

	memset(&mc_sin, 0, sizeof(struct sockaddr_in));
	mc_sin.sin_family = AF_INET;
	mc_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	mc_sin.sin_port = htons(port);

	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		die(ERR_INFO, "socket()");
	}

	loop = 1;
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &loop,
	    sizeof(loop)) < 0) {
		die(ERR_INFO, "setsockopt:SO_REUSEADDR");
	}

	sin_len = sizeof(mc_sin);
	if (bind(sock, (struct sockaddr *)&mc_sin, sizeof(mc_sin)) < 0) {
		die(ERR_INFO, "bind()");
	}

	loop = 1;
	if (setsockopt(sock, IPPROTO_IP, IP_MULTICAST_LOOP, &loop,
	        sizeof(loop)) < 0) {
		die(ERR_INFO, "setsockopt:IP_MULTICAST_LOOP");
	}
	/* Join the broadcast group: */
	command.imr_multiaddr.s_addr = inet_addr(ip);
	command.imr_interface.s_addr = htonl(INADDR_ANY);
	if (command.imr_multiaddr.s_addr == 0) {
		die(ERR_INFO, "htonl(INADDR_ANY)\n");
	}
	if (setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, &command,
	    sizeof(struct ip_mreq)) < 0) {
		die(ERR_INFO, "setsockopt:IP_ADD_MEMBERSHIP");
	}

	return;
}

void
mc_close_socket()
{
	if (setsockopt(sock, IPPROTO_IP, IP_DROP_MEMBERSHIP, &command,
	        sizeof(command)) < 0 )
	{
		perror("setsockopt:IP_DROP_MEMBERSHIP");
	}
}

ssize_t
mc_read(char *msg, size_t msg_size)
{
	return recvfrom(sock, msg, msg_size, 0,
	           (struct sockaddr *) &mc_sin, &sin_len);
}

void
mc_send_register(int pid)
{
	char msg[MSG_SIZE];

	snprintf(msg, MSG_SIZE, "register %d", pid);
	mc_send_data(msg, strlen(msg));

	return;
}

void
mc_send_deregister(int pid)
{
	char msg[MSG_SIZE];

	snprintf(msg, MSG_SIZE, "deregister %d", pid);
	mc_send_data(msg, strlen(msg));

	return;
}

void
mc_send_register_ok(int pid)
{
	char msg[MSG_SIZE];

	snprintf(msg, MSG_SIZE, "register_ok %d", pid);
	mc_send_data(msg, strlen(msg));

	return;
}

void
mc_send_request(uint32_t msg_id, uint32_t res_id, double timestamp)
{
	char msg[MSG_SIZE];

	snprintf(msg, MSG_SIZE, "request %u %u %lf", msg_id, res_id, timestamp);
	mc_send_data(msg, strlen(msg));

	return;
}

void
mc_send_request_ok(uint32_t msg_id, uint32_t res_id)
{
	char msg[MSG_SIZE];

	snprintf(msg, MSG_SIZE, "request_ok %u %u", msg_id, res_id);
	mc_send_data(msg, strlen(msg));

	return;
}

void
mc_send_data(const char *data, uint64_t length)
{
	int sending;
	size_t max;
	ssize_t write_res;
	size_t buff_size;
	size_t sent_bytes;
	uint64_t cur_pos;

	max = (size_t)-1;
	sending    = 1;
	write_res  = 0;
	buff_size  = 0;
	sent_bytes = 0;
	cur_pos    = 0;

	while (sending) {
		/* check if length is longer than size_t */
		if (length - cur_pos > (uint64_t)max) {
			buff_size = max;
		} else {
			buff_size = (size_t)(length - cur_pos);
			sending = 0;
		}
		sent_bytes = 0;
		while (sent_bytes < buff_size) {

			write_res = sendto(sock,
					data + sent_bytes + cur_pos,
					buff_size - sent_bytes,
					MSG_NOSIGNAL,
					(struct sockaddr *) &address,
					sizeof(address));
			/* write_res = send(sock, data + sent_bytes + cur_pos, */
			/*     buff_size - sent_bytes, MSG_NOSIGNAL); */
			if (write_res == -1) {
				die(ERR_INFO, "send():WRITE_CLOSED");
			} else if (write_res == 0) {
				die(ERR_INFO, "send():ZERO_WRITTEN");
			}
			sent_bytes += (size_t)write_res;
		}
		cur_pos += (uint64_t)buff_size;
	}

	return;
}
