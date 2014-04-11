/* 
 * made by d4ryus 
 */
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

const char *OUTPUT_FILE = "Calculation.txt";

struct Input { //Struct which holds the Input from the User
    int loan;
    float interest;
    int mRate;
    int yRate;
    int runTime;
};

struct Year { //The yearly Buffer struct
    int year;
    float interest;
    float interestMonth[12];
    float grace;
    float restDebt;
};

void getInput(Input *input) { // will get input from the User and store it inside the input Struct
    cout << "Please input ur Data:" << endl
            << "Loan:\t\t";
    cin >> (*input).loan;

    cout << "Interest:\t";
    cin >> (*input).interest;

    cout << "Rate per Month:\t";
    cin >> (*input).mRate;

    cout << "Rate per Year:\t";
    cin >> (*input).yRate;

    cout << "Runtime:\t";
    cin >> (*input).runTime;
}

double magicRound(double Zahl, int Stellen = 2) { // the magic round 2 function :D
    double v[] = {1, 10, 1e2, 1e3, 1e4, 1e5, 1e6, 1e7, 1e8};
    return floor(Zahl * v[Stellen] + 0.5) / v[Stellen];
}

int magicRoundInt(double d) { // the magic round function :D
    return d < 0 ? d - .5 : d + .5;
}

void calculateYears(Input input, Year *years) { //this function will calculate one year and store the data inside the Yearly Buffer

    years[0].restDebt = input.loan;

    for (int year = 0; year < input.runTime; year++) {

        if (year != 0)
            years[year].restDebt = years[year - 1].restDebt;

        for (int month = 0; month < 12; month++) {
            years[year].interestMonth[month] = (years[year].restDebt * (input.interest / 100.0)) / 12.0; //calculate the monthly interest
            years[year].restDebt = (years[year].restDebt + years[year].interestMonth[month] - input.mRate); //calculate the monthtly RestDebt
            years[year].interest += years[year].interestMonth[month]; //sum up the monthly interest
        }

        years[year].restDebt -= input.yRate; //dont forget the yearly Rate!
        years[year].grace = ((input.mRate * 12.0)+input.yRate) - years[year].interest; //calculating the yearly grace
        years[year].year = year + 1; //year finished, +1 to keep track.
    }
}

void autoFill(Input *input) { //just a quick funktion to autoFill the struct so i dont have to enter it every time
    (*input).loan = 100000;
    (*input).interest = 8.0;
    (*input).mRate = 1000;
    (*input).yRate = 2000;
    (*input).runTime = 10;
}

void coutInput(Input input) { //this function will print out the input
    cout << "Loan:\t\t" << input.loan << endl
            << "Interest:\t" << input.interest << endl
            << "Rate per Month:\t" << input.mRate << endl
            << "Rate per Year:\t" << input.yRate << endl
            << "Runtime:\t" << input.runTime << endl;
}

void coutYears(Input input, Year *years) { //function to print out whats inside the Yearly Buffer
    cout << "Jahr\t"
            << "Zins\t\t"
            << "Tilgung\t\t"
            << "Restschuld" << endl;
    for (int year = 0; year < input.runTime; year++) {
        cout << years[year].year << "\t"
                << years[year].interest << "\t\t"
                << years[year].grace << "\t\t"
                << years[year].restDebt << endl;
    }
}

void writeInFileHead(Input input){
    ofstream myfile(OUTPUT_FILE, std::ofstream::app);
    
    if (!myfile.is_open())
        myfile.open(OUTPUT_FILE, std::ofstream::app);

    myfile << "Loan:\t\t" << input.loan << endl
            << "Interest:\t" << input.interest << endl
            << "Rate per Month:\t" << input.mRate << endl
            << "Rate per Year:\t" << input.yRate << endl
            << "Runtime:\t" << input.runTime << endl

            << "Jahr\t"
            << "Zins\t\t"
            << "Tilgung\t\t"
            << "Restschuld" << endl;
    myfile.close();
}

void writeInFile(Input input, Year *years) { // appends the struct data onto the file.
    
    writeInFileHead(input);
    
    ofstream myfile(OUTPUT_FILE, std::ofstream::app);

    for (int year = 0; year < input.runTime; year++){
        
        if (!myfile.is_open())
                myfile.open(OUTPUT_FILE, std::ofstream::app);
        
        myfile << years[year].year << "\t"
                << years[year].interest << "\t\t"
                << years[year].grace << "\t\t"
                << years[year].restDebt << endl;
    }
    myfile.close();
}

void writeInFileRound2(Input input, Year *years) { // will Round the Output
   
    writeInFileHead(input);
    
    ofstream myfile(OUTPUT_FILE, std::ofstream::app);

    for (int year = 0; year < input.runTime; year++){
        
        if (!myfile.is_open())
                myfile.open(OUTPUT_FILE, std::ofstream::app);
        
        myfile << years[year].year << "\t"
                << magicRound(years[year].interest) << "\t\t"
                << magicRound(years[year].grace) << "\t\t"
                << magicRound(years[year].restDebt) << endl;
    }
    myfile.close();
}

void writeInFileRoundInt(Input input, Year *years) { // will Round the Output to an Int
    
    writeInFileHead(input);
    
    ofstream myfile(OUTPUT_FILE, std::ofstream::app);

    for (int year = 0; year < input.runTime; year++){
        
        if (!myfile.is_open())
                myfile.open(OUTPUT_FILE, std::ofstream::app);
        
        myfile << years[year].year << "\t"
                << magicRoundInt(years[year].interest) << "\t\t"
                << magicRoundInt(years[year].grace) << "\t\t"
                << magicRoundInt(years[year].restDebt) << endl;
    }
    myfile.close();
}

int main() {

    struct Input input;
    
    getInput(&input);

    struct Year years[input.runTime];

    calculateYears(input, years);

    coutYears(input, years);
    
    writeInFileRoundInt(input, years);
    
    return 0;
}