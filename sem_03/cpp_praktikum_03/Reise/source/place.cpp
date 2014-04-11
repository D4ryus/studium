#include "place.h"

/* Init Constructor */
Place::Place() {
    name = NULL;
    sign = NULL;
    x = 0;
    y = 0;
}

Place::Place(const Place& place) {
	name = NULL;
	sign = NULL;
	x = 0;
	y = 0;
	if (place.name && place.sign) {
        set_place(place.get_x(), place.get_y(), place.get_name(), place.get_sign());
    } else {
        cout << "Cannot copy NULL pointer!!" << endl;
    }
}

/* Regular Called Constructor to set x, y, name and sign */
Place::Place(int setX, int setY, const char* setname, const char* setsign) {
    set_place(setX, setY, setname, setsign);
}

/* Destructor */
Place::~Place() {
    if (name) {
        delete[] name;
        name = NULL;
    }
    if (sign) {
        delete[] sign;
        sign == NULL;
    }
}

/* Overloaded << operator to cout the object */
ostream& operator<<(ostream& cout, const Place& place){
	if ((place.x == 0 && place.y == 0) || !place.name || !place.sign) {
        cout << "Ort nicht gueltig!" << endl;
    } else {
        cout << place.name
                << ",\t" << place.sign
                << ",\tx = " << place.x
                << ",\ty = " << place.y << endl;
    }
	return cout;
}

Place& Place::operator=(const Place& place){
	if(this == &place){
		return *this;
	}else{
		set_place(place.get_x(), place.get_y(), place.get_name(), place.get_sign());
	}
}

char* Place::get_name() const {
	return name;
}
	
char* Place::get_sign() const {
	return sign;
}
	
int Place::get_x() const {
	return x;
}
	
int Place::get_y() const {
	return y;
}

int Place::set_place(int setX, int setY, const char* setname, const char* setsign) {
	if (name) {
        delete[] name;
        name = NULL;
    }
    if (sign) {
        delete[] sign;
        sign == NULL;
    }
    sign = new char[strlen(setsign)];
    name = new char[strlen(setname)];
    strcpy(name, setname);
    strcpy(sign, setsign);
    x = setX;
    y = setY;
    return 1;
}