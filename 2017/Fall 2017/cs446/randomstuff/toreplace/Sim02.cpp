#include <iostream>
#include "Simulator.h"

using namespace std;

int main(int argc, char* argv[]) {
  // Check argument count
  if (argc != 2) {
    cout << "Error: incorrect input - expected 1 CL arg" << endl;
    return EXIT_FAILURE;
  } else {
    string config_file = argv[1];
    Simulator sim(config_file);
  }

  return 0; // No errors
}
