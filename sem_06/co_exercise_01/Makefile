# Makefile zur Uebersetzung des Parsers bzw. Scanners aus Aufgabe 1
# J. Uhrmann, 09.11.2005

# Verwendung fuer Aufgabe 1:
#
#	make lexmain
#	make parsemain

# Hinweis zu den verwendeten "automatic variables":
# 	$@ kennzeichnet immer die zu erstellende Datei
#	$^ kennzeichnet immer die Liste der dazu benoetigten Dateien (ohne Duplikate)
#	$< kennzeichnet die _erste_ der benoetigten Dateien

# Hinweise zu den verwendeten Funktionen
#	$(wildcard muster)
#		sucht nach Dateien, auf die das Muster passt und gibt eine Liste
#		der Dateinamen zurueck. * und ? werden wie in der Shell verwendet
#
#	$(patsubst von, nach, eingabe)
#		ersetzt jedes Vorkommen von "von" in "eingabe" durch "nach"
#		Hier wird % als Wildcard verwendet.

# Variablendeklarationen
CC = gcc
CFLAGS = -Wall -g
LFLAGS = -lbsd
OBJS = error.o init.o lexan.o parsemain.o parser.o symbol.o

all : depend parsemain lexmain

parsemain : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

lexmain : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

.PHONY : depend
depend:
	$(CC) -E -MM *.c > .depend

-include .depend

.PHONY : clean
clean :
	rm $(OBJS)
