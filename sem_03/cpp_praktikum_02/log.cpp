#include <iostream>
#include <string.h>

using namespace std;

struct Place {
  char name[50];
  int x;
  int y;
};

void initPlace(Place *place){
  strcpy((*place).name,"");
  (*place).x = 0;
  (*place).y = 0;
}

int setPlace(Place *place, int x, int y, const char *name){
  if(strlen(name)>49 || strlen(name) < 1)
    return 0;
  strcpy((*place).name, name);
  (*place).x = x;
  (*place).y = y;
  return 1;
}

void copyPlace(Place *from, Place *to){
  strcpy((*to).name, (*from).name);
  (*to).x = (*from).x;
  (*to).y = (*from).y;
}

void printPlace(Place *place){
  if( ( (*place).x == 0 && (*place).y == 0 ) )
    cout << "Ort nicht gueltig!" << endl;
  else{
    cout << (*place).name 
      << ",\tx = " << (*place).x 
      << ",\ty = " << (*place).y << endl;
  }
}

void deletePlace(Place *place){
  initPlace(place);
}

int main(){
  struct Place landshut;
  struct Place munich;
  initPlace(&landshut);
  if(!setPlace(&landshut, 100, 150, "Landshut"))
      cout << "not able to set place" << endl;
  copyPlace(&landshut, &munich);
  printPlace(&landshut);
  printPlace(&munich);

  deletePlace(&landshut);
  printPlace(&landshut);

  return 0;
}
