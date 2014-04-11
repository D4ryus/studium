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
