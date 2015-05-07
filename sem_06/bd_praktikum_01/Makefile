# magic place

CC = gcc

OBJS = hashes.o main.o bloom.o
LFLAGS = -lbsd

EXECUTABLE = main

CFLAGS = -Wall \
         -Wstrict-prototypes \
         -Wmissing-prototypes \
         -Wno-main \
         -Wno-uninitialized \
         -Wbad-function-cast \
         -Wcast-align \
         -Wcast-qual \
         -Wextra \
         -Wmissing-declarations \
         -Wpointer-arith \
         -Wshadow \
         -Wsign-compare \
         -Wuninitialized \
         -Wunused \
         -Wno-unused-parameter \
         -Wnested-externs \
         -Wunreachable-code \
         -Winline \
         -Wdisabled-optimization \
         -Wconversion \
         -Wfloat-equal \
         -Wswitch \
         -Wswitch-default \
         -Wtrigraphs \
         -Wsequence-point \
         -Wimplicit \
         -Wredundant-decls \
         -Wstack-protector \
         -Woverlength-strings \
         -Waddress \
         -O3 \
       # -ggdb \
       # -g3 \
       # -Werror \
       # -pg \
       # -g3 \
       # -g \
       # -Wpadded
       # -Wdeclaration-after-statement

.PHONY : all
all : depend $(EXECUTABLE)

.PHONY : $(EXECUTABLE)
$(EXECUTABLE) : $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

-include .depend

.PHONY : depend
depend:
	$(CC) -E -MM *.c > .depend

.PHONY : clean
clean :
	rm $(OBJS)
