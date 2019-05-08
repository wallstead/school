#include <iostream>
#include <iomanip>
#include "Agency.h"

using namespace std;

void readData(Agency *agency);
void estimateCost(Agency *agency);
void searchByMake(Agency *agency);

int main() {

    Agency agency = Agency();

    int selection = 0;
    do {

        /* Print Menu Title */
        cout << setfill('-') << setw(80) << "-" << endl
        << "Rent-A-Vehicle" << endl << setfill('-')
        << setw(80) << "-" << endl;

        /* Display Items */
        cout << "[1] Read data from file" << endl;
        cout << "[2] Print out all data for all cars" << endl;
        cout << "[3] Print out all data for available cars" << endl;
        cout << "[4] Print most expensive car" << endl;
        cout << "[5] Estimate price of renting a car" << endl;
        cout << "[6] Sort by make" << endl;
        cout << "[7] Sort by price" << endl;
        cout << "[8] Search by make" << endl;
        cout << "[9] Exit program" << endl;
        cout << setfill('-') << setw(80) << "-" << endl;

        /* Get Menu Selection */
        cout << "Selection: ";
        cin >> selection; // get user input and save it to selection variable
        cout << setfill('-') << setw(80) << "-" << endl;

        switch (selection) {
            case 1:
                readData(&agency);
                break;
            case 2:
                agency.print();
                break;
            case 3:
                agency.printAvailableCars();
                break;
            case 4:
                agency.findMostExpensive();
                break;
            case 5:
                estimateCost(&agency);
                break;
            case 6:
                agency.sortByMake();
                break;
            case 7:
                agency.sortByPrice();
                break;
            case 8:
                searchByMake(&agency);
                break;
            case 9:
                break;
            default:
                cout << "Incorrect input" << endl;
        }

    } while (selection != 9);
    return 0;
}

void readData(Agency *agency) {
    char *ifileName = new char[20];
    cout << "Enter file name: ";
    cin >> ifileName;

    agency->readInData(ifileName);

    delete [] ifileName;
    ifileName = NULL;
}

void estimateCost(Agency *agency) {
    int carNum, dayCount;
    cout << "Enter car number (1-15): ";
    cin >> carNum;
    cout << "Enter number of days you want to rent: ";
    cin >> dayCount;

    cout << "Estimated total cost: $" << agency->estimateCost(carNum, dayCount) << endl;
}

void searchByMake(Agency *agency) {
    char *make = new char[20];
    cout << "Enter car make: ";
    cin >> make;

    agency->searchByMake(make);

    delete [] make;
    make = NULL;
}
