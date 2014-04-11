#ifndef PLACE_H
#define PLACE_H

#include <iostream>
#include <string.h>

using namespace std;

class Place {
    char* name = NULL;
    char* sign = NULL;
    int x;
    int y;
public:
    Place();
	Place(const Place& place);
    Place(int setX, int setY, const char* setname, const char* setsign);
    ~Place();
	
    friend ostream& operator<<(ostream& cout, const Place& place);
	Place& operator=(const Place& place);
	
	char* get_name() const;
	char* get_sign() const;
	int get_x() const;
	int get_y() const;
    int set_place(int setX, int setY, const char* setname, const char* setsign);
};

#endif
