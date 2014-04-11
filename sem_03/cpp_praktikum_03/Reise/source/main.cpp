#include "betrag.h"
#include "place.h"
#include "reise.h"

using namespace std;

int main(){
	Place place(140, 230, "Landshut", "Kirche");
	cout << place;
	
	Place second_place(place);	
	cout << second_place;
	
	Betrag betrag(10, 99);
	cout << betrag << endl;
	
	cout << place << betrag;
	
	Reise reise(place, betrag);
	cout << reise;
}