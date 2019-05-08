#include "inheritance.h"
#include <iostream>

using namespace std;

const float pi = 3.14159;

Rectangle::Rectangle(float length, float width) {
    this->length = length;
    this->width = width;
    this->isThreeDimensional = false;
    cout << "Creating Rectangle" << endl;
}

float Rectangle::calculateAreaOrVolume() {
    return length*width;
}

float Rectangle::calculatePerimeterOrSurfaceArea() {
    return 2*(length+width);
}

void Rectangle::print() {
    cout << "Rectangle with length: " << length
    << " and width: " << width << " ";
}

RectangularPrism::RectangularPrism(float length,float width,float height) {
    this->length = length;
    this->width = width;
    this->height = height;
    this->isThreeDimensional = true;
    cout << "Creating RectangularPrism" << endl;
}

float RectangularPrism::calculateAreaOrVolume() {
    return length*width*height;
}

float RectangularPrism::calculatePerimeterOrSurfaceArea() {
    return 2*(width*length+height*length+height*width);
}

void RectangularPrism::print() {
    cout << "Rectangular Prism with length: " << length
    << ", width: " << width << ", and height: " << height << " ";
}

Circle::Circle(float radius) {
    this->radius = radius;
    this->isThreeDimensional = false;
    cout << "Creating Circle" << endl;
}

float Circle::calculateAreaOrVolume() {
    return pi*(radius*radius);
}

float Circle::calculatePerimeterOrSurfaceArea() {
    return 2*pi*radius;
}

void Circle::print() {
    cout << "Circle with radius: " << radius << " ";
}

Cylinder::Cylinder(float radius, float height) {
    this->radius = radius;
    this->height = height;
    this->isThreeDimensional = true;
    cout << "Creating Cylinder" << endl;
}

float Cylinder::calculateAreaOrVolume() {
    return pi*(radius*radius)*height;
}

float Cylinder::calculatePerimeterOrSurfaceArea() {
    return 2*pi*(radius*radius)+2*pi*radius*height;
}

void Cylinder::print() {
    cout << "Cylinder with radius: " << radius
    << " and height: " << height << " ";
}
