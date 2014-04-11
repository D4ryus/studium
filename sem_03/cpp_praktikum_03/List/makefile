BINPATH := ./bin/
SOURCEPATH := ./source/

list: $(BINPATH)car.o $(BINPATH)element.o $(BINPATH)list.o $(BINPATH)main.o
	g++ $(BINPATH)car.o $(BINPATH)element.o $(BINPATH)list.o $(BINPATH)main.o -o list

create_bin_folder:
	if [ ! -d "$(BINPATH)" ]; then mkdir $(BINPATH); fi

$(BINPATH)car.o: $(SOURCEPATH)car.h $(SOURCEPATH)car.cpp
	make create_bin_folder
	g++ -c $(SOURCEPATH)car.cpp -o $(BINPATH)car.o

$(BINPATH)element.o: $(SOURCEPATH)element.h $(SOURCEPATH)element.cpp $(SOURCEPATH)car.h 
	g++ -c $(SOURCEPATH)element.cpp -o $(BINPATH)element.o

$(BINPATH)list.o: $(SOURCEPATH)list.h $(SOURCEPATH)list.cpp $(SOURCEPATH)element.h $(SOURCEPATH)car.h
	g++ -c $(SOURCEPATH)list.cpp -o $(BINPATH)list.o

$(BINPATH)main.o: $(SOURCEPATH)car.h $(SOURCEPATH)element.h $(SOURCEPATH)list.h $(SOURCEPATH)main.cpp
	g++ -c $(SOURCEPATH)main.cpp -o $(BINPATH)main.o
