# author: d4ryus - https://github.com/d4ryus/
# file: Makefile
# vim:noexpandtab:

CC = gcc
FLAGS = -lpthread

all: server client

server: mq.h server.c
	${CC} mq.h server.c -o server ${FLAGS}

client: mq.h client.c
	${CC} mq.h client.c -o client ${FLAGS}
