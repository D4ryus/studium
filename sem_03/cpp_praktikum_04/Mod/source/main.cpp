#include "mod.h"

int main(){
	
	Mod a(2);
	Mod b(5);
	Mod c,d,e;
	
	bool eq, uq;
	c = a + b;
	d = a - b;
	e = a * b;
	
	eq = (a == b);
	uq = (a != b);
	
	cout << "Der Modulowert ist " << a.get_modulo() << endl;
	cout << a << "  + " << b << " = " << c << endl;
	cout << a << "  - " << b << " = " << d << endl;
	cout << a << "  * " << b << " = " << e << endl;
	cout << a << " == " << b << " = " << eq << endl;
	cout << a << " != " << b << " = " << uq << endl;
	cout << "  ++ " << a << " = "; ++a; cout << a << endl;
	cout << "  -- " << a << " = "; --a; cout << a << endl << endl;

	for(int i = 0; i < 6; i++){
		cout << a << " ^ " << i << " = " << a.pot(i) << endl;
	}
}
