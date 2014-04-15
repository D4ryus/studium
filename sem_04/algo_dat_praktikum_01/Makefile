# author: d4ryus - https://github.com/d4ryus/
# vim:set noexpandtab:ft=sh:

main: algolib.o algomain.o
	gcc algolib.o algomain.o -o main

algolib.o: algolib.c algolib.h
	gcc -c algolib.c -o algolib.o

algomain.o: algolib.h algomain.c
	gcc -c algomain.c -o algomain.o
