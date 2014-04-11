#ifndef LIST_H
#define LIST_H

#include "car.h"
#include "element.h"

using namespace std;

class List{
private:
    Element* first;
public:
    List();
    List(const List& list);
	~List();
	
    int push_front(const Car& car);
    int push_back(const Car& car);
	Car pop_front();
    int is_empty() const;
    int is_in(const Car& checkcar) const;
    int remove(const Car& car);
    int length() const;
	
	List& operator+=(const List& list);
	List& operator-=(const List& list);
	List& operator=(const List& list);
    
	Element* get_first() const;
	void set_first(Element* first);
};

ostream& operator<<(ostream& cout, const List& list);

#endif
