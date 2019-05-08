#include <iostream>
#include "String.h"

using namespace std;

void String::initialize(char *str) {
    char *strHome = str;

    /* Get Length */
    int length = 0;
    while (*str != '\0') {
        length++;
        str++;
    }
    str = strHome;
    wordLength = length;

    /* Create String */
    buffer = new char[wordLength+1];
    char *bufferHome = buffer;
    while (*str != '\0') {
        *buffer = *str;
        buffer++;
        str++;
    }
    *buffer = '\0';
    str = strHome;
    buffer = bufferHome;
}

void String::deallocate() {
    delete [] buffer;
    buffer = NULL;
}

void String::copy(const String &str) {
    deallocate();
    char *strPtr = str.buffer;
    initialize(strPtr);
}

void String::concat(const String &str) {
    int newLength = str.wordLength + wordLength;
    char *tempStr = new char[newLength+1];
    char *tempStrHome = tempStr;
    char *strPtr = str.buffer;
    char *strPtrHome = strPtr;
    char *bufferHome = buffer;

    while (*buffer != '\0') {
        *tempStr = *buffer;
        buffer++;
        tempStr++;
    }
    while (*strPtr != '\0') {
        *tempStr = *strPtr;
        tempStr++;
        strPtr++;
    }

    strPtr = strPtrHome;
    *tempStr = '\0';
    tempStr = tempStrHome;
    buffer = bufferHome;

    deallocate();
    initialize(tempStr);

    delete [] tempStr;
    tempStr = NULL;
}

int String::compare(const String &str) {
    char *strPtr = str.buffer;
    char *bufferHome = buffer;

    while (*strPtr == *buffer && *strPtr && *buffer) {
        strPtr++;
        buffer++;
    }
    buffer = bufferHome;

    if (*strPtr > *buffer) {
        return -1;
    } else if (*buffer > *strPtr) {
        return 1;
    } else {
        return 0;
    }
}

int String::length() {
    return wordLength;
}

void String::print() {
    cout << buffer << endl;
}
