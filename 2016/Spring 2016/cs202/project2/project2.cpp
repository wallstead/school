#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
const int CAR_COUNT = 10;

struct rentalCar {
  char make[20];
  char model[20];
  int year;
  float price;
  bool available;
};

void select(int &selection);
void readFile(rentalCar cars[]);
void printCars(bool availableOnly, rentalCar cars[]);
void estimatePrice(rentalCar cars[]);
void mostExpensive(rentalCar cars[]);

main() {
  /* Display Menu */
  int selection = 0; // holds selection number
  do {
    /* Print Menu Title */
    cout << setfill('-') << setw(80) << "-" << endl
         << "Rent-A-Vehicle" << endl << setfill('-')
         << setw(80) << "-" << endl;

    /* Display Items */
    cout << "[1] Read data from file" << endl;
    cout << "[2] Print out all data for all cars" << endl;
    cout << "[3] Estimate car rental cost" << endl;
    cout << "[4] Find most expensive car" << endl;
    cout << "[5] Print out all available cars" << endl;
    cout << "[6] Exit program" << endl;
    cout << setfill('-') << setw(80) << "-" << endl;

    /* Get Menu Selection */
    select(selection);

    rentalCar cars[CAR_COUNT]; // create array of cars

    switch (selection) {
      case 1:
        readFile(cars); // run readFile function and supply the cars array
        break;
      case 2:
        printCars(false, cars); // run printCars function, supplying availableOnly bool as false and giving reference to cars array
        break;
      case 3:
        estimatePrice(cars); // run estimatePrice function and supply the cars array
        break;
      case 4:
        mostExpensive(cars); // run mostExpensive function and supply the cars array
        break;
      case 5:
        printCars(true, cars); // run printCars function, supplying availableOnly bool as true and giving reference to cars array
        break;
      case 6:
        cout << "Exiting program" << endl; // notify user that the program is exiting
        break;
      default:
        cout << "Incorrect input" << endl; // notify user that the input is wrong
    }

  } while (selection != 6); // continue loop as long as user did not choose to exit

  return 0;
}

void select(int &selection) {
  cout << "Selection: ";
  cin >> selection; // get user input and save it to selection variable
  cout << setfill('-') << setw(80) << "-" << endl;
}

void readFile(rentalCar cars[]) {
  ifstream fin; // Create input stream variable
  char ifileName[20]; // Create var to hold input file name
  cout << "Enter input file name: ";
  cin >> ifileName; // Save user input to file name
  fin.open(ifileName); // open user-definied file
  if (fin.is_open()) // Check if file opened correctly
  {
    for (int i = 0; i < CAR_COUNT; i++) { // loop through each car in cars array
      /* Populate cars array with data from user-defined file */
      fin >> cars[i].year >> cars[i].make >> cars[i].model
          >> cars[i].price >> cars[i].available;
    }
    cout << "Data from " << ifileName << " read successfully" << endl;

  } else { cout << "Failed to open file named " << ifileName; }
}

void printCars(bool availableOnly, rentalCar cars[]) {
  if (availableOnly != true) { // check availableOnly flag
    cout << "All data for all cars:" << endl;
  } else {
    cout << "All data for available cars:" << endl;
  }

  /* Print out table labels */
  cout << setfill('~') << setw(51) << "~" << endl
       << setfill(' ') << left << setw(8) << "YEAR" << setw(10) << "MAKE"
       << setw(11) << "MODEL" << setw(13) << "PRICE/DAY" << "AVAILABLE" << endl
       << setfill('~') << setw(51) << "~" << endl;

  for (int i = 0; i < CAR_COUNT; i++) { // loop through each car in cars array
    /* If availableOnly is true, make sure to only print cars with available set to true */
    if (cars[i].available != false || availableOnly != true) {
      /* Print and style each car's data */
      cout << setfill(' ') << left << setw(8) << cars[i].year
           << setw(10) << cars[i].make << setw(11) << cars[i].model
           << '$' << setw(12) << cars[i].price << setw(7)
           << boolalpha << cars[i].available << endl;
    }
  }
}

void estimatePrice(rentalCar cars[]) {
  int carNumber; // create var to hold car number choice
  int dayCount; // create var to hold day count choice
  cout << "Enter car number (1-10): ";
  cin >> carNumber; // get user input and save to carNumber
  cout << "Enter number of days you want to rent: ";
  cin >> dayCount;// get user input and save to dayCount

  float cost = cars[carNumber-1].price*dayCount; // calculate final cost
  cout << "Your estimated total cost is: $" << cost << endl;
}

void mostExpensive(rentalCar cars[]) {
  int mostExpensiveIndex = 0; // Index of the most expensive car
  for (int i = 0; i < CAR_COUNT; i++) { // loop through each car in cars array
    if (cars[i].price > cars[mostExpensiveIndex].price) { // if this price is bigger than the biggest..
      mostExpensiveIndex = i; // set the biggest to this
    }
  }

  cout << "Most expensive car: "
       << cars[mostExpensiveIndex].year << " "
       << cars[mostExpensiveIndex].make << " "
       << cars[mostExpensiveIndex].model << endl;
}
