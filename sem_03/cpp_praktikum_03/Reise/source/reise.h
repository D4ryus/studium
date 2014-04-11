#ifndef REISE_H
#define REISE_H

#include "place.h"
#include "betrag.h"

using namespace std;

class Reise{
private:
	Place place;
	Betrag betrag;
public:
	Reise(const Place& place, const Betrag& betrag);
	
	friend ostream& operator<<(ostream& cout, const Reise& reise);
	
	Place get_place() const;
	Betrag get_betrag() const;
	void set_place(const Place& place);
	void set_betrag(const Betrag& betrag);
};

#endif
