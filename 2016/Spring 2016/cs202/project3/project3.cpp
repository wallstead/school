#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
const int AGENCY_COUNT = 3;
const int CAR_COUNT = 5;
const int ZIP_LENGTH = 5;

struct rentalCar {
  char make[20];
  char model[20];
  int year;
  float price;
  bool available;
};

struct agency {
    char name[20];
    int zipcode[ZIP_LENGTH];
    rentalCar inventory[5];
};

void select(int &selection);
int strCompare(char *str1, char *str2);
void readFile(agency *aptr);
void printData(bool availableOnly, agency *aptr);
void estimatePrice(agency *aptr);
void mostExpensive(agency *aptr);

int main() {

    agency agencies[AGENCY_COUNT]; //create array of agencies
    agency *aptr = agencies; //create pointer to first agency in agencies array

    int selection = 0;
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

      aptr = agencies; // reset pointer to first agency

      switch (selection) {
        case 1:
          readFile(aptr);
          break;
        case 2:
          printData(false, aptr); // false because we want all cars
          break;
        case 3:
          estimatePrice(aptr);
          break;
        case 4:
          mostExpensive(aptr);
          break;
        case 5:
          printData(true, aptr); // true because we want only available cars
          break;
        case 6:
          cout << "Exiting program" << endl;
          break;
        default:
          cout << "Incorrect input" << endl;
      }

    } while (selection != 6);

    return 0;
}

void select(int &selection) {
  cout << "Selection: ";
  cin >> selection; // get user input and save it to selection variable
  cout << setfill('-') << setw(80) << "-" << endl;
}

void readFile(agency *aptr) {
    ifstream fin;
    char ifileName[20];

    cout << "Enter input file name: ";
    cin >> ifileName;
    fin.open(ifileName);

    if (fin.is_open()) {
      for (int i = 0; i < AGENCY_COUNT; i++) {
        int *zptr = (*aptr).zipcode; //create pointer to first int in zip of agency

        /* Populate array of structs with values */
        fin >> (*aptr).name;
        for (int j = 0; j < ZIP_LENGTH; j++) { // to poplulate zipcode array
            char iZip;
            fin >> iZip; // take input as a char
            int iZipNum = (int)iZip - 48;
            *zptr = iZipNum; // set this int in zip to this int
            zptr++;
        }

        rentalCar *rptr = (*aptr).inventory; //create pointer to first rentalCar in inventory
        for (int k = 0; k < CAR_COUNT; k++) {
            fin >> (*rptr).year >> (*rptr).make >> (*rptr).model
                >> (*rptr).price >> (*rptr).available;
            rptr++;
        }

        aptr++;
      }
      cout << "Data from " << ifileName << " read successfully" << endl;
    } else { cout << "Failed to open file named " << ifileName; }
}

void printData(bool availableOnly, agency *aptr) {
    for (int i = 0; i < AGENCY_COUNT; i++) {
        int *zptr = (*aptr).zipcode; //create pointer to first integer in zip array

        /* Populate array of structs with values */
        cout << "Location: " << (*aptr).name << " ";

        for (int j = 0; j < ZIP_LENGTH; j++) { // print zipcode
            cout << *zptr;
            zptr++;
        }
        cout << endl;

        cout << setfill('~') << setw(51) << "~" << endl
             << setfill(' ') << left << setw(8) << "YEAR" << setw(10) << "MAKE"
             << setw(11) << "MODEL" << setw(13) << "PRICE/DAY" << "AVAILABLE" << endl
             << setfill('~') << setw(51) << "~" << endl;

        rentalCar *rptr = (*aptr).inventory; // create pointer to first rentalCar in inventory
        for (int k = 0; k < CAR_COUNT; k++) {
            /* Make sure to only print unavailable cars if availableOnly == false */
            if ((*rptr).available != false || availableOnly != true) {
                cout << setfill(' ') << left << setw(8) << (*rptr).year << setw(10)
                     << (*rptr).make << setw(11) << (*rptr).model << setw(13)
                     << (*rptr).price << setw(7) << boolalpha << (*rptr).available
                     << endl;
            }
            rptr++;
        }
        cout << setfill('~') << setw(51) << "~" << endl;

        aptr++;
    }
}

void estimatePrice(agency *aptr) {
    char agencyName[20];
    int carNumber;
    int dayCount;
    cout << "Enter Agency Name (e.g. Hertz): ";
    cin >> agencyName; // get user input and save to carNumber
    cout << "Enter car number (1-5): ";
    cin >> carNumber; // get user input and save to carNumber
    cout << "Enter number of days you want to rent: ";
    cin >> dayCount;// get user input and save to dayCount

    for (int i = 0; i < AGENCY_COUNT; i++) { // find agency chosen
        if (strCompare((*aptr).name, agencyName)) {
            i = AGENCY_COUNT; // break out of the loop
            rentalCar *rptr = (*aptr).inventory;
            rptr += (carNumber-1); // offset this by 1 because cars are numbered 1-5, not 0-4
            float cost = (*rptr).price*dayCount;
            cout << "Your estimated total cost is: $" << cost << endl;
        } else {
            aptr++;
        }
    }
}

void mostExpensive(agency *aptr) {
    float topPrice = 0.0f;
    rentalCar *topptr; // this will point to the most expensive car

    for (int i = 0; i < AGENCY_COUNT; i++) {
        rentalCar *rptr = (*aptr).inventory;
        for (int j = 0; j < CAR_COUNT; j++) {
            if ((*rptr).price > topPrice) { // if this is the most expensive car
                topPrice = (*rptr).price;
                topptr = rptr;
            }
            rptr++;
        }
        aptr++;
    }

    cout << "The " << (*topptr).make << " " << (*topptr).model
         << " is the most expensive car at $" << (*topptr).price << endl;
}

int strCompare(char *str1, char *str2){
    while ((*str1 != '\0') && (*str2 != '\0')) { // while netheir are null
        if (*str1 != *str2) { // if this char is different
            return 0;
        } else {
            str1++;
            str2++;
        }
    }
    return 1; // the same
}
