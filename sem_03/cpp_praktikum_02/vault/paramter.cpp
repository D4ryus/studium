#include <iostream>

using namespace std;

/* Function prototypes */
int Mult(int x, int y);
void MultC(int *x, int *y, int *erg);
int MultCpp(int &x, int &y);

int main() {
	int val1 = 3;
	int val2 = 5;
	int erg = 0;
	cout << Mult(val1, val2 ) << endl;
	MultC(&val1, &val2, &erg);
	cout << erg << endl;
	cout << MultCpp(val1, val2) << endl;
	return 0;
}

int Mult(int val1, int val2) { // Multiplicates 2 values with VALUE method
	return val1 * val2;
}

void MultC(int *val1, int *val2, int *erg) { // Multiplicates 2 values with ADRESS method
	*erg = *val1 * *val2;
}

int MultCpp(int &val1, int &val2) { // Multiplicates 2 values with REFERENCE method
	return val1 * val2;
}
