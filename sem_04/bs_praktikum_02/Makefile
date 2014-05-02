# author: d4ryus - https://github.com/d4ryus/
# file: Makefile
# vim:noexpandtab

all: server client

server: mq.h server.c
	gcc mq.h server.c -o server

client: mq.h client.c
	gcc mq.h client.c -o client
