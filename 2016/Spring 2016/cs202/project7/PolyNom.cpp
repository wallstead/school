#include "PolyNom.h"
#include <cmath> //Eric said this is okay to use on discussion board

PolyNom::PolyNom() {
    this->maxDegree = 3; // Given by project description
    this->coefficients = new int[4];
}

PolyNom::PolyNom(int maxDegree, int *coefficients) {
    this->maxDegree = maxDegree;
    this->coefficients = new int[maxDegree+1]();
    for (int i = 0; i < maxDegree+1; i++) {
        this->coefficients[i] = coefficients[i];
    }
}

PolyNom::PolyNom(const PolyNom &toCopy) {
    this->maxDegree = toCopy.maxDegree;
    this->coefficients = new int[toCopy.maxDegree+1]();
    for (int i = 0; i < toCopy.maxDegree+1; i++) {
        this->coefficients[i] = toCopy.coefficients[i];
    }
}

PolyNom::~PolyNom(){
    this->maxDegree = 0;
    delete [] this->coefficients;
    this->coefficients = NULL;
}

int PolyNom::solve(int scalar) {
    int total = 0;
    for (int i = 0; i < this->maxDegree+1; i++) {
        total += this->coefficients[i] * pow(scalar, (this->maxDegree)-i); // in <cmath>
    }
    return total;
}

PolyNom &PolyNom::operator=(const PolyNom &toCopy) {
    if (this != &toCopy) {
        delete [] this->coefficients;
        this->maxDegree = toCopy.maxDegree;
        this->coefficients = new int[toCopy.maxDegree+1]();
        for (int i = 0; i < toCopy.maxDegree+1; i++) {
            this->coefficients[i] = toCopy.coefficients[i];
        }
    } else {
        cout << "Error in copying" << endl;
    }
    return *this;
}

bool PolyNom::operator==(const PolyNom &toCompare) {
    bool isEqual = true;
    if (this->maxDegree != toCompare.maxDegree){
        isEqual = false;
    }
    for (int i = 0; i < this->maxDegree+1; i++) {
        if (this->coefficients[i] != toCompare.coefficients[i]) {
            isEqual = false;
        }
    }
    return isEqual;
}

bool PolyNom::operator!=(const PolyNom &toCompare) {
    if (*this == toCompare) {
        return false;
    } else {
        return true;
    }
}

PolyNom PolyNom::operator*(const PolyNom &multiplier) {
    int newMaxDegree = this->maxDegree + multiplier.maxDegree;
    int *newCoefficients = new int[newMaxDegree+1](); // using () to initialize all to 0

    for (int i = 0; i < this->maxDegree+1; i++) {
        for (int j = 0; j < multiplier.maxDegree+1; j++) {
            newCoefficients[i+j] += this->coefficients[i] * multiplier.coefficients[j]; // i+j gives the index of each degree.
        }
    }
    PolyNom newPoly = PolyNom(newMaxDegree, newCoefficients);

    delete [] newCoefficients;
    newCoefficients = NULL;

    return newPoly;
}

PolyNom PolyNom::operator*(int multiplier) {
    int newMaxDegree = this->maxDegree;
    int *newCoefficients = new int[newMaxDegree+1]();
    for (int i = 0; i < this->maxDegree+1; i++) {
        newCoefficients[i] *= multiplier;
    }
    PolyNom newPoly = PolyNom(newMaxDegree, newCoefficients);

    return newPoly;
}

ostream &operator<<(ostream &output, const PolyNom &poly) {
    for (int i = 0; i < poly.maxDegree+1; i++) {
        if (poly.coefficients[i] != 0) { //only print if coefficient is not 0
            /* decide the sign */
            if (poly.coefficients[i] < 0) {
                output << "- ";
            } else if (i != 0) { // never print + if it is first
                output << "+ ";
            }
            if (abs(poly.coefficients[i]) != 1 || poly.maxDegree-i == 0) { // only print the coefficient if it isnt 1 or -1 or if the exponent is 0
                output << abs(poly.coefficients[i]); }
            if (poly.maxDegree-i > 0) { output << "x"; } // print x only if the exponent of the monomial is > 0
            if (poly.maxDegree-i > 1) { output << "^" << poly.maxDegree-i; } // print the ^ only if the exponent of the monomial is > 1
            output << " "; // Give space for the next one
        }
    }
    return output;
}

istream &operator>>(istream &input, PolyNom &poly) {
    delete [] poly.coefficients; // just incase there is something here already
    input >> poly.maxDegree;
    poly.coefficients = new int[poly.maxDegree+1](); //() to initialize all to 0
    for (int i = 0; i < poly.maxDegree+1; i++) {
        input >> poly.coefficients[i];
    }
    return input;
}

PolyNom operator+(const PolyNom &first, const PolyNom &second) {
    int newMaxDegree;
    if (first.maxDegree > second.maxDegree) {
        newMaxDegree = first.maxDegree;
    } else if (second.maxDegree > first.maxDegree){
        newMaxDegree = second.maxDegree;
    } else {
        newMaxDegree = first.maxDegree;
    }
    int *newCoefficients = new int[newMaxDegree+1]();

    for (int i = 0; i < first.maxDegree+1; i++) {
        int diff = newMaxDegree-first.maxDegree;
        newCoefficients[diff+i] += first.coefficients[i];
    }
    for (int j = 0; j < second.maxDegree+1; j++) {
        int diff = newMaxDegree-second.maxDegree;
        newCoefficients[diff+j] += second.coefficients[j];
    }
    PolyNom newPoly = PolyNom(newMaxDegree, newCoefficients);

    delete [] newCoefficients;
    newCoefficients = NULL;

    return newPoly;
}

PolyNom operator-(const PolyNom &first, const PolyNom &second) {
    int newMaxDegree;
    if (first.maxDegree > second.maxDegree) {
        newMaxDegree = first.maxDegree;
    } else if (second.maxDegree > first.maxDegree){
        newMaxDegree = second.maxDegree;
    } else {
        newMaxDegree = first.maxDegree;
    }

    int *subtractedCoefficients = new int[newMaxDegree+1]();

    for (int i = 0; i < first.maxDegree+1; i++) {
        int diff = newMaxDegree-first.maxDegree;
        subtractedCoefficients[diff+i] += first.coefficients[i];
    }
    for (int j = 0; j < second.maxDegree+1; j++) {
        int diff = newMaxDegree-second.maxDegree;
        subtractedCoefficients[diff+j] -= second.coefficients[j];
    }
    PolyNom newPoly = PolyNom(newMaxDegree, subtractedCoefficients);

    delete [] subtractedCoefficients;
    subtractedCoefficients = NULL;

    return newPoly;
}
