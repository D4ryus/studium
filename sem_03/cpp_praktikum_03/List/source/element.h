#ifndef ELEMENT_H
#define ELEMENT_H

#include "car.h"

using namespace std;

class Element {
private:
    Car car;
    Element* next;
public:
	Element(const Car& setCar);
	
    int has_next();
    int check_next(const Car& checkcar);
    int remove(const Car& car);
    int length();
	void clean();
	
	Car get_car() const;
	Element* get_next() const;
    void set_next(const Car& car);
	void set_next(Element* element); 
};

ostream& operator<<(ostream& cout, const Element& element);

#endif