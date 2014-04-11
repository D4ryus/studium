#include <iostream>
#include <string.h>

using namespace std;

struct Place {
  char *name = NULL;
  int x;
  int y;
};

void initPlace(Place *place){
  if((*place).name){
      delete[] (*place).name;
      (*place).name = NULL;
  }
  (*place).x = 0;
  (*place).y = 0;
}

int setPlace(Place *place, int x, int y, const char *setname){
  if(strlen(setname)>250 || strlen(setname) < 1)
    return 0;
  if((*place).name){
      delete[] (*place).name;
      (*place).name = NULL;
  }
  (*place).name = new char[strlen(setname)];
  strcpy((*place).name, setname);
  (*place).x = x;
  (*place).y = y;
  return 1;
}

void copyPlace(Place *from, Place *to){
  if((*to).name){
      delete[] (*to).name;
      (*to).name = NULL;
  }
  (*to).name = new char[strlen((*from).name)];
  
  strcpy((*to).name, (*from).name);
  (*to).x = (*from).x;
  (*to).y = (*from).y;
}

void printPlace(Place *place){
  if( ( (*place).x == 0 && (*place).y == 0 ) || !(*place).name ) {
    cout << "Ort nicht gueltig!" << endl;
  }else{
    cout << (*place).name 
      << ",\tx = " << (*place).x 
      << ",\ty = " << (*place).y << endl;
  }
}

void deletePlace(Place *place){
  (*place).x = 0;
  (*place).y = 0;
  if((*place).name){
      delete[] (*place).name;
      (*place).name = NULL;
  }
}

int main(){
  struct Place landshut;
  struct Place munich;
  
  initPlace(&landshut);
  initPlace(&munich);
  
  printPlace(&landshut);
  printPlace(&munich);
  
  if(!setPlace(&landshut, 100, 150, "Landshut"))
      cout << "not able to set place" << endl;
  if(!setPlace(&munich,   200, 250, "München"))
      cout << "not able to set place" << endl;
  
  printPlace(&landshut);
  printPlace(&munich);
  
  copyPlace(&landshut, &munich);
  
  printPlace(&landshut);
  printPlace(&munich);

  deletePlace(&landshut);
  deletePlace(&munich);

  printPlace(&landshut);
  printPlace(&munich);

  return 0;
}
