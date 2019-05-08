#include <iostream>
#include <fstream>

using namespace std;

struct Pieces {
    char *word;
    int jump;
};

void readFile(ifstream *fin, Pieces *pptr, int *kptr, int pieceCount, int keyCount);
void decrypt(char *decrypted, Pieces *pptr, int *kptr, int pieceCount, int keyCount);
int stringLength(char *str);
void strConcat(char *str1, char *str2);
void stringCopy(char *str1, char *str2);

int main() {
    char *ifileName = new char[20];
    cout << "Please enter file name: ";
    cin >> ifileName;

    ifstream fin;
    fin.open(ifileName); // open the file
    delete []ifileName; // Done with file
    ifileName = NULL;

    int pieceCount, keyCount;

    if(fin.good()) {
        cout << "File opened. Decoding..." << endl;
        /* Get pieceCount and keyCount */
        fin >> pieceCount >> keyCount;
    } else {
        cout << "Error opening file." << endl;
    }

    /* Allocate arrays */
    Pieces *pptr = new Pieces[pieceCount];
    Pieces *pptrHome = pptr; // Don't move this!
    int *kptr = new int[keyCount];
    char *decrypted = new char[100]; // temporarily allocate room for 100 chars

    /* Read in data */
    readFile(&fin, pptr, kptr, pieceCount, keyCount);

    /* Decrypt data */
    decrypt(decrypted, pptr, kptr, pieceCount, keyCount);

    /* delete allocated memory for each word in pieces */
    for (int i = 0; i < pieceCount; i++) {
        delete [](*pptr).word;
        (*pptr).word = NULL;
        pptr++;
    }

    /* delete allocated memory for pieces */
    pptr = pptrHome;
    delete []pptr;
    pptr = NULL;

    /* delete allocated memory for keys  */
    delete []kptr;
    kptr = NULL;

    /* resize decrypted string */

    char *decrypted_final = new char[stringLength(decrypted)+1]; // Create exact amount of memory needed for word.
    stringCopy(decrypted_final, decrypted);
    delete []decrypted;
    decrypted = NULL;

    cout << "FINISHED: " << decrypted_final << endl;

    /* delete allocated memory for decrypted string.  */
    delete []decrypted_final;
    decrypted_final = NULL;

    return 0;
}

void readFile(ifstream *fin, Pieces *pptr, int *kptr, int pieceCount, int keyCount) {
    Pieces *pptrHome = pptr; // Don't move this home pointer
    int *kptrHome = kptr; // Don't move this home pointer

    for (int i = 0; i < pieceCount; i++) {
        char *tempWord = new char[20]; // create pointer to first char in char array.
        *fin >> tempWord >> (*pptr).jump; // Get the word and the jump
        (*pptr).word = new char[stringLength(tempWord)+1]; // Create exact amount of memory needed for word.
        stringCopy((*pptr).word, tempWord);
        delete []tempWord; // Done with tempWord
        tempWord = NULL;
        pptr++;
    }

    for (int j = 0; j < keyCount; j++) {
        *fin >> *kptr; // get the key
        kptr++;
    }

    pptr = pptrHome; // reset to home
    kptr = kptrHome; // reset to home
    (*fin).close();
}

void decrypt(char *decrypted, Pieces *pptr, int *kptr, int pieceCount, int keyCount) {
    Pieces *pptrHome = pptr;
    int *kptrHome = kptr;

    int pieceIndex; // to keep track of current position

    for (int i = 0; i < keyCount; i++) { //For each key
        pptr += *kptr; // set the pointer to the key count
        pieceIndex = *kptr; // keep track with index
        while((*pptr).jump != 0) { // stop only if jump is 0
            if ((pieceIndex + (*pptr).jump) < pieceCount) { // if it doesnt wrap
                pptr += (*pptr).jump; // jump the needed length
                pieceIndex += (*pptr).jump; // keep track
            } else { //wrap
                /* Calulate the new Index for the pptr */
                int difference = pieceCount - pieceIndex;
                int newIndex = difference - (*pptr).jump;
                pptr = pptrHome + newIndex;
                pieceIndex = newIndex;
            }
        }
        strConcat(decrypted, (*pptr).word);
        kptr++;
        pptr = pptrHome; //reset to home
    }
}
void strConcat(char *str1, char *str2) {
    /* Add str2 to the end of str1 */

    while(*str1 != '\0') {
        str1++;
    }

    while(*str2 != '\0') {
        *str1 = *str2;
        str1++;
        str2++;
    }

    *str1 = ' ';
}

int stringLength(char *str) {
    int length = 0;
    while (*str != '\0') {
        str++;
        length++;
    }
    return length;
}

void stringCopy(char *str1, char *str2) {
    while (*str2 != '\0') {
         *str1 = *str2;

         str1++;
         str2++;
    }
    *str1 = '\0';
}
