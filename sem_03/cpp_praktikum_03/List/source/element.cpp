#include "element.h"

/* Constructor which will add the given Car to the Element */
Element::Element(const Car& set_car) {
	next = NULL;
	car = set_car;
}

/* Function which will return true if there is a next Element, 
 * otherwise return false */
int Element::has_next() {
    if(next){
		return 1;
	} else {
		return 0;
	}
}

/* Will check if the Next Element contains the Car, if so it
 * will print out that the car exists and return true,
 * if next does not exist it will print out that the 
 * Car is not in, else it will recursivly call the check_next
 * function from next Element */
int Element::check_next(const Car& checkcar) {
    if (next) {
        if (next->get_car() == checkcar) {
            return 1;
        } else {
            return next->check_next(checkcar);
        }
    } else {
        return 0;
    }
}

/* Will remove the Next Element if it contains the Car, if it doesnt
 * contain the car it will recursivly call the remove function from
 * the next Element */
int Element::remove(const Car& car) {
	if(next){
		if (next->get_car() == car) {
			Element* tmp = next->get_next();
			delete next;
			set_next(tmp);
			return 1;
		} else {
			return next->remove(car);
		} 
	} else {
		return 0;
	}
}

/* Function to figure out the length of the List */
int Element::length() {
    if (next) {
        return next->length() + 1;
    } else {
        return 0;
    }
}

/* Function to recursivly clean up a List */
void Element::clean(){
	if(next){
		next->clean();
		delete next;
	}
}

Car Element::get_car() const{
	return car;
}

Element* Element::get_next() const{
	return next;
}

void Element::set_next(const Car& car){
	next = new Element(car);
}

void Element::set_next(Element* element){
	next = element;
} 

/* overloaded << operator to cout a Element */
ostream& operator<<(ostream& cout, const Element& element){
	cout << element.get_car();
	if(element.get_next()){
		cout << *(element.get_next());
	}
	return cout;
}