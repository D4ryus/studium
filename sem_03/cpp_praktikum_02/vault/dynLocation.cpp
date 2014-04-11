#include <iostream>
#include <string.h>

using namespace std;

struct location {
	int x;
	int y;
	char *sights = NULL;
};

/* Function prototypes */
void copyLocation(location *l1, location *l2);
void deleteLocation(location *l1);
void printLocation(location l);
int setLocation(location *l, int x, int y, const char *sights);
void initLocation(location *l);

int main() {
	location Landshut;
	location Muenchen;
	initLocation(&Landshut);
	setLocation(&Landshut, 120, 330, "Haus");
	printLocation(Landshut);
	copyLocation(&Landshut, &Muenchen);
	printLocation(Muenchen);
	deleteLocation(&Muenchen);
	printLocation(Muenchen);
	return 0;
}

int setLocation(location *l, int x, int y, const char *sights) { // If string is in boundry, set the Location
	if(strlen(sights) < 1) {
		cout << "String error" << endl;
		return 0;
	}else{
		if((*l).sights){
			delete[] (*l).sights;
			(*l).sights = NULL;
		}else{
			(*l).x = x;
			(*l).y = y;
			(*l).sights = new char[strlen(sights)];
			strcpy((*l).sights, sights);
		}
		return 1;
	}
}

void initLocation(location *l) { // Sets the Location to a default state
	(*l).x = 0;
	(*l).y = 0;
	if((*l).sights) {
		delete[] (*l).sights;
		(*l).sights = NULL;
	}
}

void copyLocation(location *l1, location *l2) { // Copys a Location to another
	(*l2).x = (*l1).x;
	(*l2).y = (*l1).y;
	if((*l2).sights) {
		delete[] (*l2).sights;
		(*l2).sights = NULL;
	} else{
		(*l2).sights = new char[strlen((*l1).sights)];
		strcpy((*l2).sights, (*l1).sights);
	}
}

void deleteLocation(location *l) { // Sets the Location to a default state
	initLocation(l);
}

void printLocation(location l) { // If coordiantes are not 0, prints information about Location
	if( l.x == 0 && l.y == 0 ) {
		cout << "Koordinaten sind ungültig" << endl;
	}else{
		cout << "X: " << (l).x << "\t" << "Y: " << (l).y << "\t" << "Sight: " << (l).sights << endl;
	}
}