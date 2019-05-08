#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

void checkArgumentCount(int);
void openFile(string filename);
int main(int argc, char *argv[]) {

    try {
        checkArgumentCount(argc);
        openFile(argv[1]);
    }
    catch(const exception &msg) {
        cerr << msg.what() << endl;
    }

    return 0;
}

void checkArgumentCount(int count) {
    if (count-1 != 1) {
        throw runtime_error("ERROR: Invalid number of arguments");
    }
}

void openFile(string filename) {
    ifstream fin;
    fin.open(filename);
    if (fin) {
        string word;
        while(fin >> word) {
            cout << word << " ";
        }
        cout << endl;
    } else {
        throw runtime_error("ERROR: Could not open file");
    }
    fin.close();
}
