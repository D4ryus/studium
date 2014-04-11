#include "betrag.h"

Betrag::Betrag(){}

/* Regular called Constructor */
Betrag::Betrag(int euro = 0, int cent = 0) {
	set_betrag(euro, cent);
}

/* Copy Constructor */
Betrag::Betrag(const Betrag& betrag){
	set_betrag(betrag.get_euro(), betrag.get_cent());
}

/* Overloaded << Operator to cout the Class */
ostream& operator<<(ostream& cout, const Betrag& betrag){
	cout.width(5);
	cout << betrag.euro << ',';
	cout.fill('0');
	cout.width(2);
	cout << betrag.cent << " Euro" << endl;
	cout.fill(' ');
	return cout;
}

Betrag& Betrag::operator=(const Betrag& betrag){
	if(this == &betrag){
		return *this;
	}else{
		set_betrag(betrag.get_euro(),betrag.get_cent());
	}
}

int Betrag::get_euro() const { 
	return euro; 
}
	
int Betrag::get_cent() const { 
	return cent; 
}

void Betrag::set_betrag(int euro, int cent){
	set_euro(euro);
	set_cent(cent);
}
	
void Betrag::set_euro(int euro){ 
	this->euro = euro; 
}
	
void Betrag::set_cent(int cent){ 
	this->cent = cent; 
}