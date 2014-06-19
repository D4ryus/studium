# author: d4ryus - https://github.com/d4ryus/
# X11 libs needed, also posix threads and alsa libs
# vim:noexpandtab

HEADER = UDP.h

all: server client

server: server.c ${HEADER}
	gcc server.c -o server

client: client.c ${HEADER}
	gcc client.c -o client
