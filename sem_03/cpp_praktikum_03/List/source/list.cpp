#include "list.h"

/* Init Constructor */
List::List(){
	first = NULL;
}

/* Copy Constructor which will make a deep copy */
List::List(const List& list) {
	first = NULL;
    if( list.get_first() ) {
		Car cars[list.length()];
		Element* tmp = list.get_first();
		int count;
		for(count = 0; count < list.length(); count++){
			cars[count] = tmp->get_car();
			tmp = tmp->get_next();
		}
		for(count--; count > -1; count--){
			push_front(cars[count]);
		}
	} else { }
}

/* Recursiv Destructor */
List::~List(){
	if(first){
		first->clean();
		delete first;
	}
}

/* Function to add a Car to the List */
int List::push_front(const Car& car) {
    if (first) {
		Element* etmp = first;
		first = new Element(car);
        first->set_next(etmp);
    } else {
		first = new Element(car);
	}
	return 1;
}

/* Function to remove the first Car from the list */
Car List::pop_front() {
    if (first) {
		Element* tmp = first->get_next();
		Car car = first->get_car();
		delete first;
		first = tmp;
        return car;
    } else { }
}

/* Function to Check if list is empty */
int List::is_empty() const {
    if (first) {
        return 1;
    } else {
        return 0;
    }
}

/* Will check if List contains the given Car */
int List::is_in(const Car& checkcar) const {
    if (first) {
        if (first->get_car() == checkcar) {
            return 1;
        } else {
            return first->check_next(checkcar);
        }
    } else {
        return 0;
    }
}

/* Will remove the given Car from list, if exists */
int List::remove(const Car& car) {
    if (is_in(car)) {
        if (first->get_car() == car) {
            if (first->has_next()) {
				Element* tmp = first->get_next();
				delete first;
				first = tmp;
            } else {
                first = NULL;
            }
            return 1;
        } else {
            return first->remove(car);
        }
    } else {
        return 0;
    }
}

/* Returns the Length of the list */
int List::length() const{
    if (first) {
        return first->length() + 1;
    } else {
        return 0;
    }
}

/* Overloaded += operator to add a given list to "this" list */
List& List::operator+=(const List& list){
	if(first){
		if(list.get_first()){
			Car cars[length()];
			Element* tmp = first;
			int count;
			
			for(count = 0; count < length(); count++){
				cars[count] = tmp->get_car();
				tmp = tmp->get_next();
			}
			first->clean();
			first = NULL;
			*this = list;
			
			for(count--; count > -1; count--){
				push_front(cars[count]);
			}
			
		}else{ }
	}else{
		if(list.get_first()){
			*this = list;
	    }else{ }
	}
	return *this;
}

/* Overloaded -= operator to remove all elements which are 
   inside the given list */
List& List::operator-=(const List& list){
	if(first){
		if(list.get_first()){
			Car cars[list.length()];
			Element* tmp = list.get_first();
			int count;
			for(count = 0; count < list.length(); count++){
				cars[count] = tmp->get_car();
				tmp = tmp->get_next();
			}
			for(count--; count > -1; count--){
				remove(cars[count]);
			}
		} else { }
	} else { }
	return *this;
}

/* Overloaded = operator to copy Lists */
List& List::operator=(const List& list){
	if(first){
		first->clean();
	}
	first = NULL;
	if(list.get_first()){
		Car cars[list.length()];
		Element* tmp = list.get_first();
		int count;
		for(count = 0; count < list.length(); count++){
			cars[count] = tmp->get_car();
			tmp = tmp->get_next();
		}
		for(count--; count > -1; count--){
			push_front(cars[count]);
		}
	} else {
		cout << "cannot copy empty list" << endl;
	}
	return *this;
}

Element* List::get_first() const {
	return first;
}
	
void List::set_first(Element* first){
	this->first = first;
}

/* Overloaded operator to cout the full list */
ostream& operator<<(ostream& cout, const List& list){
	if (list.get_first()) {
	    cout << "---List---" << endl;
        cout << *(list.get_first()) << "----------" << endl;
    } else {
        cout << "List empty !!" << endl;
    }
	return cout;
}