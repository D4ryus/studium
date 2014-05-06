# author: d4ryus - https://github.com/d4ryus/
# file: Makefile
# vim:set noexpandtab:ft=sh:

CC=javac

all: DtgHeader DtgServer DtgClient

DtgHeader: DtgHeader.java
	${CC} DtgHeader.java

DtgServer: DtgServer.java DtgHeader
	${CC} DtgServer.java

DtgClient: DtgClient.java DtgHeader
	${CC} DtgClient.java
