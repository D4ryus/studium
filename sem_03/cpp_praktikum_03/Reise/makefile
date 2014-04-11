BINPATH := ./bin/
SOURCEPATH := ./source/

create_bin_folder:
	if [ ! -d "$(BINPATH)" ]; then mkdir $(BINPATH); fi

$(BINPATH)place.o: $(SOURCEPATH)place.h $(SOURCEPATH)place.cpp
	make create_bin_folder
	g++ -c $(SOURCEPATH)place.cpp -o $(BINPATH)place.o

$(BINPATH)betrag.o: $(SOURCEPATH)betrag.h $(SOURCEPATH)betrag.cpp
	g++ -c $(SOURCEPATH)betrag.cpp -o $(BINPATH)betrag.o

$(BINPATH)reise.o: $(SOURCEPATH)reise.h $(SOURCEPATH)reise.cpp
	g++ -c $(SOURCEPATH)reise.cpp -o $(BINPATH)reise.o

$(BINPATH)main.o: $(SOURCEPATH)place.h $(SOURCEPATH)betrag.h $(SOURCEPATH)reise.h $(SOURCEPATH)main.cpp
	g++ -c $(SOURCEPATH)main.cpp -o $(BINPATH)main.o

reise: $(BINPATH)place.o $(BINPATH)betrag.o $(BINPATH)reise.o $(BINPATH)main.o
	g++ $(BINPATH)place.o $(BINPATH)betrag.o $(BINPATH)reise.o $(BINPATH)main.o -o reise
