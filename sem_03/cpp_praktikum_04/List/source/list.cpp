#include "list.h"

/* Init Constructor */
List::List() : first(NULL) {}

/* Copy Constructor which will make a deep copy */
List::List(const List& list) {
	first = NULL;
    if( list.get_first() ) {
		Element* tmp = list.get_first();
		while(tmp->has_next()){
			push_back(tmp->get_car());
			tmp = tmp->get_next();
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

/* Function to add Car at the end of the List */
int List::push_back(const Car& car) {
	if (first){
		Element* tmp = first;
		while(tmp->has_next()){
			tmp = tmp->get_next();
		}
		Element* new_last = tmp->get_next();
		new_last = new Element(car);
	} else {
		first = new Element(car);
	}
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
		Element* tmp = first;
		if(tmp->get_car() == checkcar){
			return 1;
		}
		while(tmp->has_next()){
			tmp = tmp->get_next();
			if(tmp->get_car() == checkcar){
				return 1;
			} else { }
		}
    } else {
        return 0;
    }
}

/* Will remove the given Car from list, if exists */
int List::remove(const Car& car) {
    if (is_in(car)) {
        if(first->get_car() == car ){
			Element* tmp = first->get_next();
			delete first;
			first = tmp;
		} else {
			Element* tmp = first;
			while(tmp->has_next()){
				if(tmp->get_next()->get_car() == car){
					Element* tmpp = tmp->get_next()->get_next();
					delete tmp->get_next();
					tmp->set_next(tmpp);
					tmp = tmp->get_next();
				} else {
					tmp = tmp->get_next();
				}
			}
		}
    } else {
        return 0;
    }
}

/* Returns the Length of the list */
int List::length() const{
    if (first) {
        int count = 1;
		Element* tmp = first;
		while(tmp->has_next()){
			count++;
			tmp = tmp->get_next();
		}
		return count;
    } else {
        return 0;
    }
}

/* Overloaded += operator to add a given list to "this" list */
List& List::operator+=(const List& list){
	if(first){
		if(list.get_first()){
			Element* tmp = list.get_first();
			push_back(tmp->get_car());
			while(tmp->has_next()){
				tmp = tmp->get_next();
				push_back(tmp->get_car());
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
			Element* tmp = list.get_first();
			remove(tmp->get_car());
			while(tmp->has_next()){
				tmp = tmp->get_next();
				remove(tmp->get_car());
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
		Element* tmp = list.get_first();
		push_back(tmp->get_car());
		while(tmp->has_next()){
			tmp = tmp->get_next();
			push_back(tmp->get_car());
		}
	} else { }
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
