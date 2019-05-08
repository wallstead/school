#include <iostream>
#include <string>
#include "Simulator.h"

int main(int argc, char* argv[]) {
  // Check argument count
  if (argc != 2) {
    cout << "Error: Expected config as argument" << endl;
    return EXIT_FAILURE;
  } else {
    string configFileName = argv[1];
    Simulator sim01(configFileName);
  }

  return 0; // No errors
}
