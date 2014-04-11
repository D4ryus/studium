BINPATH := ./bin/
SOURCEPATH := ./source/
OBJS := $(BINPATH)car.o $(BINPATH)element.o $(BINPATH)list.o $(BINPATH)main.o
HEADER := $(SOURCEPATH)car.h $(SOURCEPATH)element.h $(SOURCEPATH)list.h

list: $(OBJS)
	g++ $(OBJS) -o list

clean:
	rm -rf $(BINPATH)

create_bin_folder:
	if [ ! -d "$(BINPATH)" ]; then mkdir $(BINPATH); fi

$(BINPATH)car.o: $(SOURCEPATH)car.h $(SOURCEPATH)car.cpp
	make create_bin_folder
	g++ -c $(SOURCEPATH)car.cpp -o $(BINPATH)car.o

$(BINPATH)element.o: $(SOURCEPATH)element.h $(SOURCEPATH)element.cpp $(SOURCEPATH)car.h 
	g++ -c $(SOURCEPATH)element.cpp -o $(BINPATH)element.o

$(BINPATH)list.o: $(HEADER) $(SOURCEPATH)list.cpp
	g++ -c $(SOURCEPATH)list.cpp -o $(BINPATH)list.o

$(BINPATH)main.o: $(HEADER) $(SOURCEPATH)main.cpp
	g++ -c $(SOURCEPATH)main.cpp -o $(BINPATH)main.o
