#include <iostream>
#include <fstream>
#include "String.h"

using namespace std;

int main() {
    /* Get input file name from user */
    ifstream fin;
    char *iFileName = new char[20];

    cout << "Please enter file name: ";
    cin >> iFileName;


    char *iFileNameHome = iFileName;
    /* Get Length */
    int length = 0;
    while (*iFileName != '\0') {
        length++;
        iFileName++;
    }

    iFileName = iFileNameHome;

    /* Create correctly-sized char* */
    char *iFileNamev2 = new char[length+1];
    char *iFileNamev2Home = iFileNamev2;
    while (*iFileName != '\0') {
        *iFileNamev2 = *iFileName;
        iFileNamev2++;
        iFileName++;
    }
    iFileName = iFileNameHome;
    *iFileNamev2 = '\0';
    iFileNamev2 = iFileNamev2Home;

    delete [] iFileName;
    iFileName = NULL;


    fin.open(iFileNamev2);

    delete [] iFileNamev2;
    iFileNamev2 = NULL;

    if (fin.is_open()) {
        /* Single Instances Test Driver */
        String single1, single2;

        char *temp1 = new char[20];
        char *temp2 = new char[20];
        fin >> temp1 >> temp2;

        single1.initialize(temp1);
        single2.initialize(temp2);
        delete [] temp1;
        temp1 = NULL;
        delete [] temp2;
        temp2 = NULL;

        cout << "Buffer of both strings: " << endl;
        cout << "\tstring 1: ";
        single1.print();
        cout << "\tstring 2: ";
        single2.print();

        cout << "Length of both strings: " << endl;
        cout << "\tstring 1: " << single1.length() << endl;
        cout << "\tstring 2: " << single2.length() << endl;

        cout << "Comparing string 2 to string 1: " << endl;
        cout << "\t" <<single1.compare(single2) << endl;

        cout << "Comparing string 1 to string 2: " << endl;
        cout << "\t" <<single2.compare(single1) << endl;

        cout << "Concatenating string 1 to string 2: " << endl;
        single2.concat(single1);
        cout << "\tstring 1: ";
        single1.print();
        cout << "\tstring 2: ";
        single2.print();

        cout << "Concatenating string 2 to string 1: " << endl;
        single1.concat(single2);
        cout << "\tstring 1: ";
        single1.print();
        cout << "\tstring 2: ";
        single2.print();

        cout << "Copying string 2 to string 1: " << endl;
        single1.copy(single2);
        cout << "\tstring 1: ";
        single1.print();
        cout << "\tstring 2: ";
        single2.print();

        cout << "Deallocating memory for both strings." << endl;
        single1.deallocate();
        single2.deallocate();

        /* Array Test Driver */
        String *strings = new String[10];
        String *stringPtr = strings; // Used to jump through array

        for (int i = 0; i < 10; i++) {
            char *temp = new char[20];
            fin >> temp; // Get each string as a char* initialy
            (*stringPtr).initialize(temp); // Then convert
            delete [] temp; // Then delete the char*
            temp = NULL;
            stringPtr++;
        }
        stringPtr = strings; // reset pointer to base

        cout << "Buffers of strings in array:" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "\tstring " << i+1 << ": "; // some styling
            (*stringPtr).print();
            stringPtr++;
        }
        stringPtr = strings;

        cout << "Lengths of strings in array:" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "\tstring " << i+1 << ": " << (*stringPtr).length() << endl;
            stringPtr++;
        }
        stringPtr = strings;

        cout << "Comparing string 7 to string 6: " << endl;
        stringPtr += 5; // set to string 6
        String *str6 = stringPtr;
        stringPtr++;
        String *str7 = stringPtr;
        cout << "\t" << (*str6).compare(*str7) << endl;
        stringPtr = strings;

        cout << "Comparing string 1 to string 3: " << endl;
        String *str1 = stringPtr;
        stringPtr+=2;
        String *str3 = stringPtr;
        cout << "\t" << (*str3).compare(*str1) << endl;
        stringPtr = strings;

        cout << "Concatenating string 10 to string 9: " << endl;
        stringPtr += 8;
        String *str9 = stringPtr;
        stringPtr++;
        String *str10 = stringPtr;
        (*str9).concat(*str10);
        cout << "\tstring 9: ";
        (*str9).print();
        cout << "\tstring 10: ";
        (*str10).print();
        stringPtr = strings;

        cout << "Concatenating string 3 to string 7: " << endl;
        (*str7).concat(*str3); // These pointers are already defined above
        cout << "\tstring 3: ";
        (*str3).print();
        cout << "\tstring 7: ";
        (*str7).print();

        cout << "Copying string 8 to string 5: " << endl;
        stringPtr += 4;
        String *str5 = stringPtr;
        stringPtr += 3;
        String *str8 = stringPtr;
        (*str5).copy(*str8);
        cout << "\tstring 5: ";
        (*str5).print();
        cout << "\tstring 8: ";
        (*str8).print();
        stringPtr = strings;

        cout << "Buffers of strings in array after manipulations:" << endl;
        for (int i = 0; i < 10; i++) {
            cout << "\tstring " << i+1 << ": ";
            (*stringPtr).print();
            stringPtr++;
        }
        stringPtr = strings;

        cout << "Deallocating memory for each string in array." << endl;
        for (int i = 0; i < 10; i++) {
            (*stringPtr).deallocate(); // deallocate the memory for each string
            stringPtr++;
        }
        stringPtr = strings;

        cout << "Deallocating memory for array." << endl;
        delete [] strings;
        strings = NULL;

    } else {
        cout << "Could not open file: " << iFileNamev2 << endl;
    }

    fin.close();

    return 0;
}
