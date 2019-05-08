#include <iostream>
#include <fstream>
#include "Agency.h"

using namespace std;

const int ZIP_LENGTH = 5;
const int CAR_COUNT = 15;

void copy_string(char *target, char *source);
int compare_string(char *first, char *second);
void copy_zip(int *target, int *source);

Car::Car() {
    // cout << "CREATING CAR FROM NOTHING" << endl;
    make = new char[20];
    *make = '\0';
    model = new char[20];
    *model = '\0';
    year = 0;
    price = 0.0;
    available = false;
}

Car::Car(char *tempMake, char *tempModel, int tempYear, float tempPrice, bool tempAvailable) {
    // cout << "CREATING AGENCY WITH PARAMETERS" << endl;
    make = new char[20];
    copy_string(make, tempMake);
    model = new char[20];
    copy_string(model, tempModel);
    year = tempYear;
    price = tempPrice;
    available = tempAvailable;
}

Car::Car(const Car &car) {
    // cout << "CREATING CAR FROM COPY CONSTRUCTOR" << endl;
    make = new char[20];
    copy_string(make, car.make);
    model = new char[20];
    copy_string(model, car.model);
    year = car.year;
    price = car.price;
    available = car.available;
}

Car::~Car() {
    // cout << "CAR DESTRUCTOR" << endl;
    delete [] make;
    make = NULL;
    delete [] model;
    model = NULL;
    year = 0;
    price = 0.0;
    available = false;
}

void Car::copy(Car car) {
    /* takes in a Car and copies the data into the calling object after it has been inited*/
    copy_string(make, car.make);
    copy_string(model, car.model);
    year = car.year;
    price = car.price;
    available = car.available;
}

void Car::print() const {
    cout << year << " " << make << " " << model << " $"
         << price << " " << boolalpha << available << endl;
}

void Car::setMake(char *tempMake) {
    char *tempMakeHome = tempMake;
    char *makeHome = make;
    while (*tempMake != '\0') {
        *make = *tempMake;

        make++;
        tempMake++;
    }
    make = makeHome;
    tempMake = tempMakeHome;
}

void Car::setModel(char *tempModel) {
    char *tempModelHome = tempModel;
    char *modelHome = model;
    while (*tempModel != '\0') {
        *model = *tempModel;

        model++;
        tempModel++;
    }
    tempModel = tempModelHome;
    model = modelHome;
}

void Car::setYear(int tempYear) {
    year = tempYear;
}

void Car::setPrice(float tempPrice) {
    price = tempPrice;
}

void Car::setAvailable(bool tempAvailable) {
    available = tempAvailable;
}

char * Car::getMake() const {
    return make;
}

char * Car::getModel() const {
    return model;
}

int Car::getYear() const {
    return year;
}

float Car::getPrice() const {
    return price;
}

bool Car::getAvailable() const {
    return available;
}



Agency::Agency() {
    // cout << "CREATING AGENCY FROM NOTHING" << endl;
    name = new char[20];
    zipcode = new int[5];
    inventory = new Car[CAR_COUNT];

    char *ifileName = new char[20];
    cout << "Enter file name: ";
    cin >> ifileName;

    readInData(ifileName);

    delete [] ifileName;
    ifileName = NULL;
}

Agency::Agency(const Agency &agency) {
    // cout << "CREATING AGENCY FROM COPY CONSTRUCTOR" << endl;
    name = new char[20];
    copy_string(name, agency.name);
    zipcode = new int[5];
    copy_zip(zipcode, agency.zipcode);
    inventory = new Car[CAR_COUNT];
}

Agency::~Agency() {
    // cout << "AGENCY DESTRUCTOR" << endl;
    delete [] inventory;
    inventory = NULL;
    delete [] name;
    name = NULL;
    delete [] zipcode;
    zipcode = NULL;
}

void Agency::readInData(char *ifileName) {
    ifstream fin;

    fin.open(ifileName);

    if (fin.is_open()) {
        /* READ IN AGENCY INFO */
        fin >> name;

        int *zptr = zipcode;
        int *zptrHome = zipcode;
        for (int j = 0; j < ZIP_LENGTH; j++) { // to poplulate zipcode array
            char iZip;
            fin >> iZip; // take input as a char
            int iZipNum = (int)iZip - 48;
            *zptr = iZipNum; // set this int in zip to this int
            zptr++;
        }
        zptr = zptrHome;


        Car *carPtr = inventory;
        Car *carPtrHome = inventory;
        /* READ IN INFO FOR EACH CAR */
        for (int i = 0; i < CAR_COUNT; i++) {
            char *tempMake = new char[20];
            char *tempModel = new char[20];
            int tempYear = 0;
            float tempPrice;
            bool tempAvailable = false;

            fin >> tempYear >> tempMake >> tempModel >> tempPrice
                >> tempAvailable;

            carPtr->setYear(tempYear);
            carPtr->setMake(tempMake);
            carPtr->setModel(tempModel);
            carPtr->setPrice(tempPrice);
            carPtr->setAvailable(tempAvailable);

            delete [] tempMake;
            tempMake = NULL;
            delete [] tempModel;
            tempModel = NULL;


            carPtr++;
        }
        carPtr = carPtrHome;

        cout << "Data from " << ifileName << " read successfully" << endl;
    } else { cout << "Error reading from " << ifileName << "." << endl; }
    fin.close();
}

void Agency::print() const {
    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    /* PRINT OUT INFO FOR EACH CAR */
    for (int i = 0; i < CAR_COUNT; i++) {
        carPtr->print();
        carPtr++;
    }
    carPtr = carPtrHome;
}

void Agency::printAvailableCars() const {
    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    /* PRINT OUT INFO FOR EACH CAR */
    for (int i = 0; i < CAR_COUNT; i++) {
        if (carPtr->getAvailable() == true) {
            carPtr->print();
        }
        carPtr++;
    }
    carPtr = carPtrHome;
}

void Agency::findMostExpensive() const {
    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    Car *mostExpensive = inventory;
    for (int i = 0; i < CAR_COUNT; i++) {
        if (carPtr->getPrice() > mostExpensive->getPrice()) {
            mostExpensive = carPtr;
        }
        carPtr++;
    }
    carPtr = carPtrHome;

    mostExpensive->print();
}

float Agency::estimateCost(int carNum, int numDays) const {
    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    for (int i = 0; i < carNum-1; i++) {
        carPtr++;
    }
    float estimatedPrice = carPtr->getPrice() * numDays;
    carPtr = carPtrHome;
    return estimatedPrice;
}

void Agency::sortByMake() {
    // alphabetical
    // cout << endl << compare_string("b", "a") << endl;

    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    //-1 means swap
    Car tempCar = Car();
    for(int i = 0; i <= CAR_COUNT-2; i++) {
        for(int j = 0; j <= CAR_COUNT-2; j++) {
            if(compare_string(carPtr->getMake(), (carPtr+1)->getMake()) == -1) {
                // cout << (carPtr)->getMake() << " <--> " << (carPtr+1)->getMake() <<endl;
                tempCar.copy(*carPtr);
                carPtr->copy(*(carPtr+1));
                (carPtr+1)->copy(tempCar);
            }
            carPtr++;
        }
        carPtr = carPtrHome;
    }
    cout << "Sorted by make." << endl;
}

void Agency::sortByPrice() {
    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    Car tempCar = Car();
    for(int i = 0; i <= CAR_COUNT-2; i++) {
        for(int j = 0; j <= CAR_COUNT-2; j++) {
            if(carPtr->getPrice() < (carPtr+1)->getPrice()) {
                tempCar.copy(*carPtr);
                carPtr->copy(*(carPtr+1));
                (carPtr+1)->copy(tempCar);
            }
            carPtr++;
        }
        carPtr = carPtrHome;
    }
    cout << "Sorted by price." << endl;
}

void Agency::searchByMake(char *make) const {
    Car *carPtr = inventory;
    Car *carPtrHome = inventory;

    for (int i = 0; i < CAR_COUNT; i++) {
        if (compare_string(carPtr->getMake(), make) == 0) {
            carPtr->print();
        }
        carPtr++;
    }
    carPtr = carPtrHome;
}

int compare_string(char *first, char *second) {
    char *firstHome = first;
    char *secondHome = second;

    while (*first == *second && *first && *second) {
        first++;
        second++;
    }


    if (*first > *second) {
        return -1;
    } else if (*second > *first) {
        return 1;
    } else {
        return 0;
    }
    first = firstHome;
    second = secondHome;
}

void copy_string(char *target, char *source) {
   while(*source) {
      *target = *source;
      source++;
      target++;
   }
   *target = '\0';
}

void copy_zip(int *target, int *source) {
   for (int i = 0; i < ZIP_LENGTH; i++) {
       *target = *source;
       source++;
       target++;
   }
}
