#include <iostream>
#include <string>
#include <fstream>
#include "PolyNom.h"

using namespace std;

int main() {
    string filename;
    int scalar;
    cout << "Enter input file name: ";
    cin >> filename;
    cout << "Enter scalar integer to be multiplied by: ";
    cin >> scalar;

    ifstream fin;
    fin.open(filename);

    if (fin.good()) {
        int polyCount;
        fin >> polyCount;
        PolyNom *polyNomials = new PolyNom[polyCount];
        for (int i = 0; i < polyCount; i++) {
            fin >> polyNomials[i];
        }

        cout << "Polynomials: " << endl;

        for (int j = 0; j < polyCount; j++) {
            cout << "[" << j << "] " << polyNomials[j] << endl;
        }

        cout << endl << "Multiplication: ";

        cout << endl << "( " << polyNomials[2] << ") * ( " << polyNomials[3] << ")" << endl;
        PolyNom multiPolyResult = polyNomials[2]*polyNomials[3];
        cout << "= " << multiPolyResult << endl << endl;

        cout << "( " << polyNomials[5] << ") * ( " << scalar << " )" << endl;
        PolyNom multiplyResult = polyNomials[5]*scalar;
        cout << "= " << multiplyResult << endl << endl;

        cout << "Addition: ";

        cout << endl << "( " << polyNomials[1] << ") + ( " << polyNomials[2] << " )" << endl;
        PolyNom additionResult = polyNomials[1]+polyNomials[2];
        cout << "= " << additionResult << endl << endl;

        cout << "Subtraction: ";

        cout << endl << "( " << polyNomials[3] << ") - ( " << polyNomials[4] << " )" << endl;
        PolyNom subtractionResult = polyNomials[3]-polyNomials[4];
        cout << "= " << subtractionResult << endl << endl;

        cout << "Comparison: ";

        cout << endl << "does ( " << polyNomials[2] << ") == ( " << polyNomials[4] << " ) ?" << endl;
        if (polyNomials[2] == polyNomials[4]) {
            cout << "they are equal" << endl;
        } else {
            cout << "they are not equal" << endl;
        }

        cout << endl << "does ( " << polyNomials[0] << ") != ( " << polyNomials[5] << " ) ?" << endl;
        if (polyNomials[0] != polyNomials[5]) {
            cout << "they are not equal" << endl;
        } else {
            cout << "they are equal" << endl;
        }



        delete [] polyNomials;
        polyNomials = NULL;
    } else {
        cout << "Error opening specified file" << endl;
    }

    fin.close();
}
