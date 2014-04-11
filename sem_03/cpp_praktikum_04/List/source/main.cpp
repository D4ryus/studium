#include <string.h>
#include <iostream>
#include "car.h"
#include "list.h"
#include "element.h"

using namespace std;

int main() {
	
    Car car0("Steven", 0);
    Car car1("Tony", 1);
    Car car2("Sven", 2);
    Car car3("Marc", 3);
    Car car4("Tom", 4);
    Car car5("Franc", 5);
    Car car6("Hank", 6);
    Car car7("Walt", 7);
	
	cout << "Created Cars :" << endl
		 << car0 << car1 
		 << car2 << car3 
		 << car4 << car5 
		 << car6 << car7;
	

    List* list1 = new List();
    list1->push_front(car0);
    list1->push_front(car1);
    list1->push_front(car2);
    list1->push_front(car3);
    list1->push_front(car4);
    list1->push_front(car5);
    list1->push_front(car6);
    list1->push_front(car7);
	
	cout << "Created list and pushed all created cars in: " << endl
		 << *list1;
	
	
    List* list2 = new List(*list1);
	
	cout << "Created another list with Copy construtor using first list: " << endl
		 << *list2;
	
	
	list2->remove(car3);
	list2->remove(car1);
	list2->remove(car5);
	list2->remove(car6);
	
	cout << "Removed some cars from the second list: " << endl
	     << *list2;
	
	
	*list1 -= *list2;
	
	cout << "First list after removing all cars from list2 (list1 -= list2) " << endl
		 << *list1;
	
	
	*list1 += *list2;
	
	cout << "Frist list after adding all cars from list2 (list1 += list2) " << endl
	     << *list1;
}
