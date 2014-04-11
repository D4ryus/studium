#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <iomanip>
#include <string.h>

using namespace std;

class Car {
private:
    char* driver = NULL;
    int id;
public:
	Car();
	Car(const Car& car);
    Car(const char* newDriver, int newID);
    ~Car();
	
	Car& operator=(const Car& car);
    
	char* get_driver() const;
	int get_id() const;
};

bool operator== (const Car& car1, const Car& car2);
bool operator!= (const Car& car1, const Car& car2);
ostream& operator<< (ostream& cout, const Car& car);

#endif 
