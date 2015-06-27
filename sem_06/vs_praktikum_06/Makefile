CC = gcc

OBJS = main.o helper.o cb.o multicast.o data.o

EXECUTABLE = main

GPROF_FILE = performance.txt

CFLAGS = -Wall \
         -fPIC \
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
         -Wswitch \
         -Wswitch-default \
         -Wtrigraphs \
         -Wsequence-point \
         -Wimplicit \
         -Wstack-protector \
         -Woverlength-strings \
         -Waddress \
         -ggdb \
         -Wdeclaration-after-statement \
         -pg \
         -O2 \
         -D_FILE_OFFSET_BITS=64 \
         -Werror
       # -Wredundant-decls \
       # -Wpadded

LFLAGS = -lpthread

#OBJS   += ncurses_msg.o
#CFLAGS += -DNCURSES
#LFLAGS += -lcurses

# CFLAGS += -std=c99
# CFLAGS += -pedantic

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
	rm $(OBJS) $(EXECUTABLE) .depend

# targets to run
run_$(EXECUTABLE) : $(EXECUTABLE)
	./$<

perf :
	gprof $(EXECUTABLE) gmon.out > $(GPROF_FILE)

graph : perf
	gprof2dot $(GPROF_FILE) -n0 -e0 > graph.dot
	dot -Tsvg graph.dot -o graph.svg
	sfdp -Gsize=100! -Gsplines=true -Goverlap=prism -Tpng graph.dot > graph.png
