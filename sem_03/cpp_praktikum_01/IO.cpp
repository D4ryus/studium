/* 
 * made by d4ryus 
 */
#include <iostream>
#include <fstream>

using namespace std;

const int EMLOYEE_LIST_LENGTH = 50;
const char *OUTPUT_FILE = "Adressdaten.txt";

struct Employee {
    char name[20];
    float height;
    int age;
    char gender;
};

void getNewGuy(Employee *employee) { // will fill the struct
    cout << "Please tell me ur name (max 20 characters): ";
    cin >> (*employee).name;

    cout << "Please tell me ur height: ";
    cin >> (*employee).height;

    cout << "Please tell me ur age: ";
    cin >> (*employee).age;

    cout << "Please tell me ur gender('m'/'f'): ";
    cin >> (*employee).gender;
}

void writeInFile(Employee *employee) { // appends the struct data onto the file.
    ofstream myfile(OUTPUT_FILE, std::ofstream::app);
    if (!myfile.is_open())
        myfile.open(OUTPUT_FILE, std::ofstream::app);
    myfile << (*employee).name << " "
            << (*employee).height << " "
            << (*employee).age << " "
            << (*employee).gender << endl;
    myfile.close();
}

void writeOnTerminal(Employee *employee) { // prints out the struct data.
    cout << "You have added: " << endl;
    cout << (*employee).name << " "
            << (*employee).height << " "
            << (*employee).age << " "
            << (*employee).gender << "." << endl;
}

int fillArray(Employee *employeeList) { // reads the file and writes the contend into the Array.
    ifstream myfile(OUTPUT_FILE);

    int count = 0;
    while (!myfile.eof() && count < EMLOYEE_LIST_LENGTH) {
        myfile >> (*employeeList).name
                >> (*employeeList).height
                >> (*employeeList).age
                >> (*employeeList).gender;
        *employeeList++;
        count++;
    }
    myfile.close();
    return count;
}

void printArray(Employee *employeeList, int *count) {
    for (int i = 1; i < *count; i++) {
        cout << (*employeeList).name << " "
                << (*employeeList).height << " "
                << (*employeeList).age << " "
                << (*employeeList).gender << endl;
        *employeeList++;
    }
}

int main() {
    struct Employee guy;
    struct Employee guyList[EMLOYEE_LIST_LENGTH];
    while (true) { // will continue until a return statement is reached.
        cout << "What do u want to do?" << endl
                << "'a' to add a new Employee," << endl
                << "'p' to print the Employee list, " << endl
                << "'q' to quit. " << endl
                << "(a/p/q): ";
        char input;
        cin >> input;
        if (input == 'a') {
            getNewGuy(&guy);
            writeInFile(&guy);
            writeOnTerminal(&guy);
            return 0;
        } else if (input == 'p') {
            int count = fillArray(guyList);
            printArray(guyList, &count);
            return 0;
        } else if (input == 'q') {
            return 0;
        } else {
            cout << "wrong input, try again." << endl;
        }
    }
}
