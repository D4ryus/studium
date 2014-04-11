#include "car.h"

/* Init Constructor */
Car::Car() : id(0) {}

/* Copy constructor */
Car::Car(const Car& car) {
	driver = new char[strlen(car.driver)];
    strcpy(driver, car.driver);
    id = car.id;
}

/* Regular called Constructor */
Car::Car(const char* newDriver, int newID) {
    driver = new char[strlen(newDriver)];
    strcpy(driver, newDriver);	
    id = newID;
}

/* Destructor to clean up the Heap */
Car::~Car() {
	if (driver) {
		delete[] driver;
		driver = NULL;
	}
}

/* Assignment operator = */
Car& Car::operator=(const Car& car){
	if(this == &car){
		return *this;
	} else {
		driver = new char[strlen(car.driver)];
		strcpy(driver, car.driver);
		id = car.id;
		return *this;
	}
}

char* Car::get_driver() const {
	return driver;
}

int Car::get_id() const {
	return id;
}

/* Overloaded == operator function to comparte Car objects */
bool operator== (const Car& car1, const Car& car2){
	if(car1.get_id() == car2.get_id()){
		return 1;
	} else {
		return 0;
	}
}

/* Overloaded != operator function to compare Car objects */
bool operator!= (const Car& car1, const Car& car2){
	return !(car1 == car2);
}

/* Overloaded << operator function to cout the Car object */
ostream& operator<<(ostream& cout, const Car& car){
	if (car.get_driver()) {
	    cout << "Driver:" << setw(10) << right << car.get_driver() << ", ID: ";
        cout.fill('0');
        cout << setw(8) << right << car.get_id() << endl;
        cout.fill(' ');
    } else {
        cout << "No Driver set!" << endl;
    }
	return cout;
}