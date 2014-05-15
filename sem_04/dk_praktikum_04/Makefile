# author: d4ryus - https://github.com/d4ryus/
# file: Makefile
# vim:set noexpandtab:ft=sh:

CC=javac

all: Header Server Client

Header: Header.java
	${CC} Header.java

Server: Server.java Header
	${CC} Server.java

Client: Client.java Header
	${CC} Client.java
