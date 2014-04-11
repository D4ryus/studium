#include "reise.h"

/* Regular called Constructor */
Reise::Reise(const Place& place, const Betrag& betrag){
	set_place(place);
	set_betrag(betrag);
}

/* Overloaded << operator to cout the "Reise" object */
ostream& operator<<(ostream& cout, const Reise& reise){
	cout << reise.place << reise.betrag;
}

Place Reise::get_place() const {
	return place;
}

Betrag Reise::get_betrag() const {
	return betrag;
}

void Reise::set_place(const Place& place){
	this->place = place;
}

void Reise::set_betrag(const Betrag& betrag){
	this->betrag = betrag;
}