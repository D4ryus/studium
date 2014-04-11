#ifndef MOD_H
#define MOD_H

#include <iostream>

using namespace std;

class Mod{
private:
	int a;
public:
	static int q;
	
	Mod();
	Mod(int x);
	
	Mod& operator=(const Mod& mod);
	Mod& operator++();
	Mod& operator--();
	bool operator==(const Mod& mod);
	bool operator!=(const Mod& mod);	
	friend ostream& operator<<(ostream& cout, const Mod& mod);
	
	Mod pot(unsigned int n);
	
	int get_modulo() const;
	int get_a() const;
	void set_a(int x);
};
	
Mod operator*(const Mod& mod1, const Mod& mod2);
Mod operator+(const Mod& mod1, const Mod& mod2);
Mod operator-(const Mod& mod1, const Mod& mod2);


#endif
