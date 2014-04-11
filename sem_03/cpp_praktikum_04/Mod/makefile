BINPATH := ./bin/
SOURCEPATH := ./source/

mod: $(BINPATH)mod.o $(BINPATH)main.o
	g++ $(BINPATH)mod.o $(BINPATH)main.o -o mod

create_bin_folder:
	if [ ! -d "$(BINPATH)" ]; then mkdir $(BINPATH); fi

$(BINPATH)mod.o: $(SOURCEPATH)mod.h $(SOURCEPATH)mod.cpp
	make create_bin_folder
	g++ -c $(SOURCEPATH)mod.cpp -o $(BINPATH)mod.o

$(BINPATH)main.o: $(SOURCEPATH)mod.h $(SOURCEPATH)main.cpp
	g++ -c $(SOURCEPATH)main.cpp -o $(BINPATH)main.o


