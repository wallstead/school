#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "Queue.cpp"

using namespace std;

#ifndef SimulatorHeader  // to stop this file from being included more than once
#define SimulatorHeader

struct Operation {
  string type;
  int cycleTime;

  Operation(string comp, int time) : type(comp), cycleTime(time){};
};

struct Metadata {
  char code;
  int cycles;
  string descriptor;

  Metadata(char code, int cycles, string descriptor) : code(code), cycles(cycles), descriptor(descriptor){};
};

class Simulator {
 public:
  // Constructors
  Simulator();
  Simulator(string);
  // Destructor
  ~Simulator();

 private:
  // Data members
  string configFileName;
  ifstream configFileContents;
  string metaFileName;
  ifstream metaFileContents;
  string logFileName;
  vector<Operation> simulationData;
  Queue<string> metaData;
  bool printToScreen;
  bool printToFile;

  // Parsing functions
  bool parseConfig(const string&);
  bool parseMetadata(const string&);
  void simulate();

  // Other functions
  bool checkExtension(const string&, const string&);
  Metadata checkMeta(const string&);
  bool isCode(char);
  bool isDigit(char);
  bool isDescriptor(const string);
  void cleanString(string&);
  void addData(const string, const string);
  void dropCase(string&);
  int getCycletime(string);
};

#endif
