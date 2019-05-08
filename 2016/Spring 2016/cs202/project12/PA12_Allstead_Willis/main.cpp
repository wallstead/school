#include <iostream>
#include <string>
#include <fstream>
#include "inheritance.h"

using namespace std;

int main() {
    string fileName;
    cout << "Please enter data file name: ";
    cin >> fileName;

    ifstream fin;
    fin.open(fileName.c_str());
    if (fin.good()) {
        int shapeCount;
        fin >> shapeCount;
        Shape **shapes = new Shape *[shapeCount];

        /* 1 = rectangle, 2 = rectangular prism, 3 = circle, 4 = cylinder */
        int type;
        float length, width, height, radius;
        for (int i = 0; i < shapeCount; i++) {
            fin >> type;
            if (type == 1) {
                fin >> length >> width;
                shapes[i] = new Rectangle(length, width);
            } else if (type == 2) {
                fin >> length >> width >> height;
                shapes[i] = new RectangularPrism(length, width, height);
            } else if (type == 3) {
                fin >> radius;
                shapes[i] = new Circle(radius);
            } else if (type == 4) {
                fin >> radius >> height;
                shapes[i] = new Cylinder(radius, height);
            } else {
                cout << "Unexpected shape." << endl;
            }
        }

        fin.close();

        for (int j = 0; j < shapeCount; j++) {
            if (shapes[j]->is3D()) {
                cout << "The Surface Area of a ";
            } else {
                cout << "The Perimeter of a ";
            }
            shapes[j]->print();
            cout << "is: " << shapes[j]->calculatePerimeterOrSurfaceArea() << endl;
        }

        cout << endl;

        for (int k = 0; k < shapeCount; k++) {
            if (shapes[k]->is3D()) {
                cout << "The Volume of a ";
            } else {
                cout << "The Area of a ";
            }
            shapes[k]->print();
            cout << "is: " << shapes[k]->calculateAreaOrVolume() << endl;
        }

        for (int l = 0; l < shapeCount; l++) {
            delete shapes[l];
        }
        delete [] shapes;


    } else {
        cout << "Error opening file." << endl;
    }

    

    return 0;
}
