#include "mod.h"
#include <iostream>

/* set static q */
int Mod::q = 7;

Mod::Mod(){}

Mod::Mod(int x) : a(x) {}

Mod& Mod::operator=(const Mod& mod){
	set_a(mod.get_a());
}

Mod operator+(const Mod& mod1, const Mod& mod2){
	return Mod( mod1.get_a() + mod2.get_a() );
}

Mod operator-(const Mod& mod1, const Mod& mod2){
	return Mod( mod1.get_a() - mod2.get_a() );
}

Mod& Mod::operator++(){
	set_a( get_a() + 1 );
	return *this;
}

Mod& Mod::operator--(){
	set_a( get_a() - 1 );
	return *this;
}

Mod operator*(const Mod& mod1, const Mod& mod2){
	return Mod( mod1.get_a() * mod2.get_a() );
}

bool Mod::operator==(const Mod& mod){
	if( get_a() == mod.get_a() ){
		return true;
	}else{
		return false;
	}
}

bool Mod::operator!=(const Mod& mod){
	return !( *this == mod );
}

ostream& operator<<(ostream& cout, const Mod& mod){
	cout << mod.get_a();
}

/* function to calculate the potency (a^n % q) */
Mod Mod::pot(unsigned int n){
	if(n == 0){
		return Mod(1);
	}else{
		if(n == 1){
			return Mod(get_a());
		}
		if(n % 2 == 0){
			return pot(n/2) * pot(n/2);
		}
		if(n % 2 == 1){
			return pot(n-1) * Mod(get_a());
		}
	}
}

int Mod::get_modulo() const {
	return q;
}

int Mod::get_a() const {
	return a;
}

/* will set_a after x % q */
void Mod::set_a(int x){
	if( x >= 0 ){
		if(x >= q){
			a = x % q;
		}else{
			a = x;
		}
	}else{
		while(x < 0){
			x = x + q;
		}
		a = x;
	}
}
