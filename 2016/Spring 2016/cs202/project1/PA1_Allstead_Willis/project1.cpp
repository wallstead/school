/*
Name: Willis Allstead
Class: CS202

Program Name: Alphabetize
Program Purpose: To take a file of 10 names and alphabetize
								 them and output them into an output file.
*/

#include <iostream>
#include <fstream>

using namespace std;

int strCompare(char str1[], char str2[]);
void strCopy(char str1[], char str2[]);

int main () {

	char names[10][20]; // create names array with space for up to 19 character first names
	char inFileName[20]; // create the input file name variable
	char outFileName[20]; // create the output file name variable


	/* Ask user for names of input/output files */
	cout << "Input File Name: ";
	cin >> inFileName;
	cout << "Output File Name: ";
	cin >> outFileName;

	/* Create variable of type input filestream and open a file with file name provided */
  ifstream fin; 
  fin.open(inFileName); 

  if (fin.is_open()) { 

  	cout << "Unsorted: \n";

  	/* Insert contents of file into names array */
  	for (int i = 0; i < 10; i++) { 
  		fin >> names[i]; // add this name to name array
  		cout << "\t" << names[i] << "\n"; // print out this unsorted name
  	}

  	/* Alphabetize */ 
  	int flag = 0; // used to decide if we should continue or end the sorting
  	char tempName[20]; // to temporarily hold a name while swapping
  	do {
  		flag = 0;
  		for (int i = 0; i < 10; i++) {
  			if (strCompare(names[i], names[i+1]) < 0) {
  				/* we need to swap the names */
  				strCopy(tempName, names[i]); // move this name to a temp var
  				strCopy(names[i], names[i+1]); // move from right to left
  				strCopy(names[i+1], tempName); // move from left to right

  				flag = 1;
  			}
  		}
  	} while (flag > 0);

  	/* Output new alphabetized array */
  	cout << "Sorted: \n";
  	for (int i = 10; i > 0; i--) {
  		cout << "\t" << names[i-1] << "\n";
  	}

		fin.close(); // close file
	} else {
		cout << "Could not open input file";
	}

	/* Create variable of type output filestream and open a file with file name provided */
	ofstream fout;
  fout.open(outFileName);

  if (fout.is_open()) {
  	
  	/* Insert contents of names array into new file */
  	for (int i = 10; i > 0; i--) {
  		fout << names[i-1] << "\n";
  	}
  } else {
  	cout << "Could not open output file";
  }

	return 0;
}

int strCompare(char str1[], char str2[]) {

	int i = 0; // create index
	while (str1[i] == str2[i] && str1[i] != '\0') {
		i++; // increment index to go to next char in both strings
	} 
	if (str1[i] > str2[i]) {
      return 1;
	}
	else if (str1[i] < str2[i]) {
		return -1;
	}
	else {
		return 0;
	}
}

void strCopy(char str1[], char str2[]) {
    
    int i = 0;  // create index
    while (str2[i] != '\0') {
			str1[i] = str2[i];
			i++;
    }

    str1[i]='\0';
}
