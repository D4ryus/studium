#ifndef BETRAG_H
#define BETRAG_H

#include <iostream>
#include <string.h>

using namespace std;

class Betrag{
	int euro;
	int cent;
public:
	Betrag();
	Betrag(int euro, int cent);
	Betrag(const Betrag& betrag);
	
	friend ostream& operator<<(ostream& cout, const Betrag& betrag);
	Betrag& operator=(const Betrag& betrag);
	
	int get_euro() const;
	int get_cent() const;
	void set_betrag(int euro, int cent);
	void set_euro(int euro);
	void set_cent(int cent);
};

#endif
