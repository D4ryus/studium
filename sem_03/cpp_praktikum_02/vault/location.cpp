#include <iostream>
#include <string.h>

using namespace std;

struct location {
	int x;
	int y;
	char sights[50];
};

/* Function prototypes */
void initLocation(location *l);
int setLocation(location *l, int x, int y, const char *sights);
void printLocation(location l);
void copyLocation(location *l1, location *l2);
void deleteLocation(location *l1);

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

void initLocation(location *l) { // Sets the Location to a default state
	(*l).x = 0;
	(*l).y = 0;
	strcpy((*l).sights, "");
}

int setLocation(location *l, int x, int y, const char *sights) { // If string is in boundry, set the Location
	if(strlen(sights) < 1 || strlen(sights) >49) {
		cout << "String error" << endl;
		return 0;
	}else{
		(*l).x = x;
		(*l).y = y;
		strcpy((*l).sights, sights);
		return 1;
	}
}

void copyLocation(location *l1, location *l2) { // Copys a Location to another
	(*l2).x = (*l1).x;
	(*l2).y = (*l1).y;
	strcpy((*l2).sights, (*l1).sights);
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







