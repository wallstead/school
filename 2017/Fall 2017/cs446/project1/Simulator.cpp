#include "Simulator.h"

// Default constructor
Simulator::Simulator() {}

// Parameterized constructor
Simulator::Simulator(string config) {
  configFileName = config;

  // Parse config file
  if (parseConfig(configFileName)) {
    // Parse meta data file
    if (parseMetadata(metaFileName)) {
      simulate();
    } else {
      cout << "Error: Could not parse metadata file" << endl;
    }
  } else {
    cout << "Error: Could not parse config file" << endl;
  }
}

// Destructor
Simulator::~Simulator() {}

// Parses through configuration file and sets up object to run simulation
bool Simulator::parseConfig(const string& fileName) {
  // Checking file extension
  if (!this->checkExtension(fileName, ".conf")) {
    throw invalid_argument("Error: Invalid config file extension");
    return false;
  }

  // Opening file
  configFileContents.open(fileName);
  string line;

  // Checking if file is empty
  if (configFileContents.peek() == ifstream::traits_type::eof()) { // for reference: https://stackoverflow.com/q/26228424
    throw invalid_argument("Error: Empty config file");
  }

  // parsing each line of config file
  while (getline(configFileContents, line)) {
    string delimiter = ":";
    if (line.find(delimiter) == string::npos) { // for reference: https://stackoverflow.com/a/3827946
    } else {
      string configKey = line.substr(0, line.find(delimiter)); // info before :
      string configValue = line.substr(line.find(delimiter) + 1); // info after :

      // removing whitespace
      cleanString(configKey);
      cleanString(configValue);
      // converting to lowercase
      dropCase(configKey);

      /* NOTE: ignoring version/phase number until later projects */

      // Check & process key-value pairs
      if (configKey == "filepath") {
        metaFileName = configValue; // don't drop case incase the filename has caps
      } else if (configKey == "log") { // if we log to file or monitor + file
        dropCase(configValue);

        if (configValue == "logtoboth") {
          // logging to monitor and file
          printToScreen = true;
          printToFile = true;
        } else if (configValue == "logtomonitor") {
          // logging to just screen
          printToScreen = true;
          printToFile = false;
        } else if (configValue == "logtofile") {
          // logging to just file
          printToScreen = false;
          printToFile = true;
        }
      } else if (configKey == "logfilepath") {
        // file path for log file
        logFileName = configValue;
      } else if (configKey.find("processor") != string::npos) {
        this->addData("Processor", configValue);
      } else if (configKey.find("monitor") != string::npos) {
        this->addData("Monitor", configValue);
      } else if ((configKey.find("hard") != string::npos) && (configKey.find("drive") != string::npos)) {
        this->addData("Hard Drive", configValue);
      } else if (configKey.find("printer") != string::npos) {
        this->addData("Printer", configValue);
      } else if (configKey.find("keyboard") != string::npos) {
        this->addData("Keyboard", configValue);
      } else if (configKey.find("memory") != string::npos) {
        this->addData("Memory", configValue);
      } else if (configKey.find("mouse") != string::npos) {
        this->addData("Mouse", configValue);
      } else if (configKey.find("speaker") != string::npos) {
        this->addData("Speaker", configValue);
      }
    }
  }

  // Checking if config file had all information needed
  if (simulationData.size() < 8) {
    throw invalid_argument(
        "Error: Missing configuration data, expected data for 8 Operations");
  }

  // closing file and return true
  configFileContents.close();
  return true;
}

// Parses through metadata file
bool Simulator::parseMetadata(const string& fileName) {
  // Checking file extension
  if (!this->checkExtension(fileName, ".mdf")) {
    throw invalid_argument("Error: Invalid metadata file extension");
    return false;
  }

  // Opening file
  metaFileContents.open(fileName);
  string line;

  // Checking if file is empty
  if (metaFileContents.peek() == ifstream::traits_type::eof()) {
    throw invalid_argument("Error: Empty metadata file");
  }

  // flags for when full command has been parsed
  bool startFound = false;
  bool endFound = false;
  // indexes to keep track of command
  int startPosition;
  int endPosition;

  // parsing each line
  while (getline(metaFileContents, line)) {
    // remove whitespace
    cleanString(line);

    // loop through each character of the line
    for (int i = 0; i < line.length(); i++) {
      if (line[i] == '(') {
        // if char is (, then char immediately before is META DATA CODE
        int position = i - 1;

        // save position of meta data code and set flag to true
        startPosition = position;
        startFound = true;
      } else if (line[i] == ')') {
        // if char is ), then next couple are the # of cycles
        int position = i + 1;

        // iterate until character is not a digit
        while (isDigit(line[position])) {
          position++;
        }

        // set endPosition to index of character after the # of cycles.
        endPosition = position;
        endFound = true;
      }

      // if we find both the start and end of some single metadata in form <META DATA CODE>(<META DATA DESCRIPTOR>)<NUMBER OF CYCLES>
      if (startFound && endFound) {
        string singleMetaData = line.substr(startPosition, endPosition - startPosition);
        metaData.enqueue(singleMetaData);
        startFound = false;
        endFound = false;
      }
    }
  }

  // close file
  metaFileContents.close();
  return true;
}

// To begin the O/S simulation
void Simulator::simulate() {
  string descriptor;
  string front;
  int time;

  ofstream logFileContents;
  logFileContents.open(logFileName);

  // if printing configuration data to file
  if (printToFile) {
    logFileContents << "Configuration File Data" << endl;

    for (vector<Operation>::const_iterator index = simulationData.begin(); index != simulationData.end(); ++index) {
      logFileContents << index->type << " = " << index->cycleTime << " ms/cycle" << endl;
    }

    if (printToScreen) {
      logFileContents << "Logged to: monitor and " << logFileName << endl;
    } else {
      logFileContents << "Logged to: " << logFileName << endl;
    }

    logFileContents << endl << "Meta-Data Metrics:" << endl;
  }

  //  if printing configuration data to screen
  if (printToScreen) {
    cout << "Configuration File Data" << endl;
    for (vector<Operation>::const_iterator index = simulationData.begin(); index != simulationData.end(); ++index) {
      cout << index->type << " = " << index->cycleTime << " ms/cycle" << endl;
    }

    if (printToFile) {
      cout << "Logged to: monitor and " << logFileName << endl;
    } else {
      cout << "Logged to: monitor" << endl;
    }
    cout << endl << "Meta-Data Metrics:" << endl;
  }

  // for each element in queue
  while (!metaData.empty()) {
    // Check for errors in metadata
    front = metaData.getFront();
    Metadata data = checkMeta(front);
    descriptor = data.descriptor;

    // Calculating cycle time * # of cycles
    if (descriptor == "harddrive") {
      time = getCycletime("Hard Drive") * data.cycles;
    } else if (descriptor == "keyboard") {
      time = getCycletime("Keyboard") * data.cycles;
    } else if (descriptor == "printer") {
      time = getCycletime("Printer") * data.cycles;
    } else if (descriptor == "monitor") {
      time = getCycletime("Monitor") * data.cycles;
    } else if (descriptor == "allocate" || descriptor == "block") {
      time = getCycletime("Memory") * data.cycles;
    } else if (descriptor == "mouse") {
      time = getCycletime("Mouse") * data.cycles;
    } else if (descriptor == "speaker") {
      time = getCycletime("Speaker") * data.cycles;
    } else if (descriptor == "run") {
      time = getCycletime("Processor") * data.cycles;
    }

    if (time == -1) {
      cout << "Error: Invalid cycle time" << endl;
    }

    // A and S are not printed
    if ((data.code != 'A') && (data.code != 'S')) {
      if (printToScreen) {
        cout << front << " - ";
        cout << time << " ms" << endl;
      }
      if (printToFile) {
        logFileContents << front << " - ";
        logFileContents << time << " ms" << endl;
      }
    }

    // dequeue front instruction from queue
    string dequeued; // unused besides for this call
    metaData.dequeue(dequeued);
  }

  // close log file
  logFileContents.close();
}

// Checks if a given file contains a certain file extension
bool Simulator::checkExtension(const string& str, const string& extension) {
  int delimiter = str.find_last_of(".");
  string extensionName = str.substr(delimiter);
  if (extensionName == extension) {
    return true;
  } else {
    return false;
  }
}

// Checks the string for the metadata and returns Metadata struct if all is well
Metadata Simulator::checkMeta(const string& input) {
  string descriptor;
  string cycleString;
  char code = input[0];
  int cycles;
  int descriptorStart;
  int descriptorEnd;

  if (!isCode(code)) {
    throw invalid_argument("Error: Invalid metadata code value");
  }

  // Get descriptor
  for (int i = 0; i < input.length(); i++) {
    if (input[i] == '(') {
      descriptorStart = i + 1;
    } else if (input[i] == ')') {
      descriptorEnd = i;
    }
  }

  // check if descriptor is okay
  descriptor = input.substr(descriptorStart, descriptorEnd - descriptorStart);
  if (isDescriptor(descriptor) == false) {
    throw invalid_argument("Error: Invalid metadata operation descriptor");
  }

  // Get number of cycles from string
  if (descriptorEnd == input.length() - 1) {
    throw invalid_argument("Error: Missing cycle value");
  } else {
    cycleString = input.substr(descriptorEnd + 1);
  }

  cycles = stoi(cycleString); // Getting int from cycles string

  // Create struct from data
  Metadata data(code, cycles, descriptor);
  return data;
}

// Checks if a character is a valid meta code
bool Simulator::isCode(char code) {
  if ((code == 'S') || (code == 'A') || (code == 'P') || (code == 'I') || (code == 'O') || (code == 'M')) {
    return true;
  } else {
    return false;
  }
}

// Checks if a character is a digit
bool Simulator::isDigit(char c) {
  if ((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') ||
      (c == '5') || (c == '6') || (c == '7') || (c == '8') || (c == '9')) {
    return true;
  } else {
    return false;
  }
}

// Checks if a string matches any of the possible meta data descriptor tags
bool Simulator::isDescriptor(const string str) {
  if ((str == "end") || (str == "harddrive") || (str == "keyboard") ||
      (str == "printer") || (str == "monitor") || (str == "block") ||
      (str == "run") || (str == "start") || (str == "allocate") ||
      (str == "mouse") || (str == "speaker")) {
    return true;
  } else {
    return false;
  }
}

// Removes whitespace from string
void Simulator::cleanString(string& input) {
  for (int i=0; i<input.length(); i++) {
    if (input[i] == ' '){
      input.erase(i,1);
    }
  }
}

// Creates a Operation struct and adds it to simulationData vector
void Simulator::addData(const string comp, const string cycleString) {
  int time = stoi(cycleString);
  Operation operation(comp, time);
  simulationData.push_back(operation);
}

// Converts input to lowercase
void Simulator::dropCase(string& input) {
   for (int i=0; i<input.length(); i++){
      if (input[i] >= 'A' && input[i] <= 'Z'){
         input[i] = input[i] + 32;
      }
   }
}

// Returns the cycle time of a specified Operation
int Simulator::getCycletime(string str) {
  for (int i = 0; i < simulationData.size(); i++) {
    if (simulationData[i].type == str) {
      return simulationData[i].cycleTime;
    }
  }

  return -1; // to signify error
}
