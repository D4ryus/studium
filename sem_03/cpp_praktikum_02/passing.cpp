#include <iostream>

using namespace std;

int iAddMultValue(int iVal1, int iVal2){
  return iVal1*iVal2;
}

void iAddMultReference(int *iVal1, int *iVal2,int *resolution){
  (*resolution) = (*iVal1) * (*iVal2);
}

void iAddMultReferenceCPP(int &iVal1, int &iVal2, int &resolution){
  resolution = iVal1 * iVal2;
}

int main(){
  cout << iAddMultValue(2, 3) << endl;

  int x = 2;
  int y = 3;

  int z = 0;
  iAddMultReference(&x, &y, &z);
  cout << z << endl;

  int a = 0;
  iAddMultReferenceCPP(x, y, a);
  cout << a << endl;

  return 1;
}
