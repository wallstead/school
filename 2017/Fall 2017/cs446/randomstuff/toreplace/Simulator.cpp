#include "Simulator.h"

pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

// Default constructor
Simulator::Simulator(string config)
{
    configFileName = config;

    // Parse config file

    if (parseConfig(configFileName)) {
        logger.loadFromConfig(printToFile, printToScreen, logFileName);

        // Parse meta data file
        if (parseMetadata(metaFileName)) {
            addOperations();
            addProcesses();
            simulate();
        }
        else {
            cout << "Error: Could not parse metadata file" << endl;
        }
    }
    else {
        cout << "Error: Could not parse config file" << endl;
    }
}

// Destructor
Simulator::~Simulator() {}

// Simulate
void Simulator::simulate()
{
    clock.start();

    // Looping through process queue
    while (!processes.empty()) {
        // Get process at front of queue
        Process proc = processes.front();

        // Set process state to ready and semaphore to true
        proc.state = READY;
        string proc_name = "Process " + to_string(proc.number);

        // Looping through operations for current process
        while (!proc.operations.empty()) {
            Operation current = proc.operations.front();
            proc.state = RUNNING;

            if (current.code == 'S') {
                proc.state = WAITING;
                if (current.tag == START) {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("Simulator program starting");
                }
                else {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("Simulator program ending");
                }
                proc.state = READY;
            }
            else if (current.code == 'A') {
                proc.state = WAITING;
                if (current.tag == START) {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("OS: preparing " + proc_name);
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("OS: starting " + proc_name);
                }
                else {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("OS: removing " + proc_name);
                }
                proc.state = READY;
            }
            else if (current.code == 'P') {
                proc.state = WAITING;
                logger.timeStamp(clock.elapsedTime());
                logger.log(proc_name + ": start processing action");
                execute(current);
                logger.timeStamp(clock.elapsedTime());
                logger.log(proc_name + ": end processing action");
                proc.state = READY;
            }
            else if (current.code == 'M') {
                proc.state = WAITING;
                if (current.tag == ALLOCATE) {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(proc_name + ": allocating memory");
                    string mem_loc = hexString(
                        allocate_memory(system_memory)); // just printing it for now
                    execute(current);
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(proc_name + ": memory allocated at " + mem_loc);
                }
                else if (current.tag == BLOCK) {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(proc_name + ": start memory blocking");
                    execute(current);
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(proc_name + ": end memory blocking");
                }
                proc.state = READY;
            }
            else if (current.code == 'I') {
                proc.state = WAITING;
                logger.timeStamp(clock.elapsedTime());
                logger.log(proc_name + ": start " + descriptorToString(current.tag) + " input");

                Thread data(current.cycles, descriptorToCycles(current.tag));
                pthread_t t1;
                pthread_create(&t1, NULL, &executeThread, &data); // for reference:https://computing.llnl.gov/tutorials/pthreads/
                pthread_join(t1, NULL);

                logger.timeStamp(clock.elapsedTime());
                logger.log(proc_name + ": end " + descriptorToString(current.tag) + " input");

                proc.state = READY;
            }
            else if (current.code == 'O') {
                proc.state = WAITING;
                logger.timeStamp(clock.elapsedTime());
                logger.log(proc_name + ": start " + descriptorToString(current.tag) + " output");
                proc.state = WAITING;

                Thread data(current.cycles, descriptorToCycles(current.tag));
                pthread_t t1;
                pthread_create(&t1, NULL, &executeThread, &data); // for reference:\https://computing.llnl.gov/tutorials/pthreads/
                pthread_join(t1, NULL);

                logger.timeStamp(clock.elapsedTime());
                logger.log(proc_name + ": end " + descriptorToString(current.tag) + " output");
                proc.state = READY;
            }
            // Remove operation from queue once it executes
            proc.operations.pop();
        }
        // Remove process from queue once it is finished executing
        processes.pop();
    }
}

// Parses through configuration file and sets up object to run simulation
bool Simulator::parseConfig(const string& fileName)
{
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

    int componentCount = 0;

    // parsing the config file line by line
    while (getline(configFileContents, line)) {
        string delimiter = ":";
        if (line.find(delimiter) == string::npos) { // for reference: https://stackoverflow.com/a/3827946
        }
        else {
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
            }
            else if (configKey == "log") { // if we log to file or monitor + file
                dropCase(configValue);

                if (configValue == "logtoboth") {
                    // logging to monitor and file
                    printToScreen = true;
                    printToFile = true;
                }
                else if (configValue == "logtomonitor") {
                    // logging to just screen
                    printToScreen = true;
                    printToFile = false;
                }
                else if (configValue == "logtofile") {
                    // logging to just file
                    printToScreen = false;
                    printToFile = true;
                }
            }
            else if (configKey == "logfilepath") {
                // file path for log file
                logFileName = configValue;
            }

            int value = atoi(configValue.c_str());

            if (configKey.find("processor") != string::npos) {
                processor = value;
                componentCount++;
            }
            else if (configKey.find("monitor") != string::npos) {
                monitor = value;
                componentCount++;
            }
            else if ((configKey.find("hard") != string::npos) && (configKey.find("drive") != string::npos)) {
                hard_drive = value;
                componentCount++;
            }
            else if (configKey.find("printer") != string::npos) {
                printer = value;
                componentCount++;
            }
            else if (configKey.find("keyboard") != string::npos) {
                keyboard = value;
                componentCount++;
            }
            else if (configKey.find("memory") != string::npos) {
                if (configKey.find("system") != string::npos) {
                  if (configKey.find("kbytes") != string::npos) {
                      system_memory = value;
                  } else if (configKey.find("Mbytes") != string::npos) {
                      system_memory = value*1000;
                  } else if (configKey.find("Gbytes") != string::npos) {
                      system_memory = value*1000000;
                  } 
                }
                else {
                    memory = value;
                    componentCount++;
                }
            }
            else if (configKey.find("mouse") != string::npos) {
                mouse = value;
                componentCount++;
            }
            else if (configKey.find("speaker") != string::npos) {
                speaker = value;
                componentCount++;
            }
        }
    }

    // Checking if config file had all information needed
    if (componentCount < 8) {
        throw invalid_argument(
            "Error: missing configuration data - expected data for 8 components");
    }

    // closing file and return true
    configFileContents.close();

    return true;
}

// Parses through metadata file
bool Simulator::parseMetadata(const string& fileName)
{
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
            }
            else if (line[i] == ')') {
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

            // if we find both the start and end of some single metadata in form <META
            // DATA CODE>(<META DATA DESCRIPTOR>)<NUMBER OF CYCLES>
            if (startFound && endFound) {
                string singleMetaData = line.substr(startPosition, endPosition - startPosition);
                metaData.push(singleMetaData);
                startFound = false;
                endFound = false;
            }
        }
    }

    // close file and return true
    metaFileContents.close();
    return true;
}

// Builds a queue of operations
void Simulator::addOperations()
{
    string current;
    bool s_flag = false;

    // Looping through queue
    while (!metaData.empty()) {
        current = metaData.front();

        Operation new_op = operationFromString(current);

        if (new_op.code == 'S' && new_op.tag == START) {
            if (s_flag == false)
                s_flag = true;
            else
                throw invalid_argument(
                    "Error: Illegal S(start) command - no more than 1 per meta file");
        }
        operations.push(new_op);

        metaData.pop();
    }
}

// Builds a queue of processes
void Simulator::addProcesses()
{
    Process* new_proc;
    bool create_new = true;

    while (!operations.empty()) {
        if (create_new) {
            new_proc = new Process(processes.size() + 1, NEW);
            create_new = false;
        }

        Operation current = operations.front();
        new_proc->operations.push(current);

        if (current.code == 'A' && current.tag == END) {
            processes.push(*new_proc);
            new_proc = NULL;
            create_new = true;
        }

        operations.pop();
    }

    Process last(processes.size() + 1, NEW);
    Operation end('S', 0, END);
    last.operations.push(end);
    processes.push(last);
}

// Executes operation without threading
void Simulator::execute(Operation op)
{
    Timer clock;

    for (int i = 0; i < op.cycles; i++) {
        clock.start();
        while (clock.elapsedTimeMilliseconds() < descriptorToCycles(op.tag))
            ;
    }
}

// Executes operation using threading
void* Simulator::executeThread(void* p)
{
    // Mutex lock
    pthread_mutex_lock(&mutexsum);

    // Executing thread
    Thread* op = (Thread*)p;
    Timer clock;
    for (int i = 0; i < op->numberOfCycles; i++) {
        clock.start();
        while (clock.elapsedTimeMilliseconds() < op->cycleTime)
            ;
    }

    // Mutex unlock
    pthread_mutex_unlock(&mutexsum);
}

// from Vineeth

unsigned int Simulator::allocate_memory(int totMem)
{
    unsigned int address;

    srand(time(NULL));

    if (totMem > 0) {
        address = rand() % totMem;
    }
    return address;
}

// Checks if a given file contains a certain file extension
bool Simulator::checkExtension(const string& str, const string& extension)
{
    int delimiter = str.find_last_of(".");
    string extensionName = str.substr(delimiter);
    if (extensionName == extension) {
        return true;
    }
    else {
        return false;
    }
}

// Checks if a character is a valid meta code
bool Simulator::isCode(char code)
{
    if ((code == 'S') || (code == 'A') || (code == 'P') || (code == 'I') || (code == 'O') || (code == 'M')) {
        return true;
    }
    else {
        return false;
    }
}

// Checks if a character is a digit
bool Simulator::isDigit(char d)
{
    if ((d == '0') || (d == '1') || (d == '2') || (d == '3') || (d == '4') || (d == '5') || (d == '6') || (d == '7') || (d == '8') || (d == '9')) {
        return true;
    }
    else {
        return false;
    }
}

// Checks if a string matches any of the possible meta data descriptor tags
bool Simulator::isDescriptor(const string str)
{
    if ((str == "end") || (str == "harddrive") || (str == "keyboard") || (str == "printer") || (str == "monitor") || (str == "block") || (str == "run") || (str == "start") || (str == "allocate") || (str == "mouse") || (str == "speaker")) {
        return true;
    }
    else {
        return false;
    }
}
// Removes whitespace from string
void Simulator::cleanString(string& input)
{
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == ' ') {
            input.erase(i, 1);
        }
    }
}

// Converts input to lowercase
void Simulator::dropCase(string& input)
{
    for (int i = 0; i < input.length(); i++) {
        if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] + 32;
        }
    }
}

// Takes a descriptor tag and returns the cycle time associated with that tag
int Simulator::descriptorToCycles(descriptor tag)
{
    switch (tag) {
    case HARD_DRIVE:
        return hard_drive;
        break;
    case KEYBOARD:
        return keyboard;
        break;
    case PRINTER:
        return printer;
        break;
    case MONITOR:
        return monitor;
        break;
    case RUN:
        return processor;
        break;
    case ALLOCATE:
        return memory;
        break;
    case MOUSE:
        return mouse;
        break;
    case SPEAKER:
        return speaker;
        break;
    case BLOCK:
        return memory;
        break;
    }
}

// Takes a descriptor tag and returns a corresponding string
string Simulator::descriptorToString(descriptor tag)
{
    string result;

    switch (tag) {
    case HARD_DRIVE:
        result = "hard drive";
        break;
    case KEYBOARD:
        result = "keyboard";
        break;
    case PRINTER:
        result = "printer";
        break;
    case MONITOR:
        result = "monitor";
        break;
    case RUN:
        result = "processor";
        break;
    case ALLOCATE:
        result = "memory";
        break;
    case MOUSE:
        result = "mouse";
        break;
    case SPEAKER:
        result = "speaker";
        break;
    case BLOCK:
        result = "memory";
        break;
    }

    return result;
}

// Takes an integer value and returns the corresponding hexadecimal string
string Simulator::hexString(int i)
{
    stringstream stream;

    stream << "0x" << setfill('0') << setw(sizeof(i) * 2) << hex << i;
    return stream.str();
}

// Creates and returns an operation struct from a string
Operation Simulator::operationFromString(const string& str)
{
    string desc_str;
    string cycle_str;
    descriptor tag;

    char code = str[0];
    int cycles;
    int tag_start;
    int tag_end;

    // If is_code returns false then given code is invalid
    if (isCode(code) == false) {
        throw invalid_argument("Error: Invalid metadata code value");
    }

    // Getting descriptor tag from string
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            tag_start = i + 1;
        }
        else if (str[i] == ')') {
            tag_end = i;
        }
    }
    desc_str = str.substr(tag_start, tag_end - tag_start);

    if (isDescriptor(desc_str) == false) {
        throw invalid_argument("Error: Invalid metadata descriptor tag");
    }
    else {
        if (desc_str == "harddrive") {
            tag = HARD_DRIVE;
        }
        else if (desc_str == "keyboard") {
            tag = KEYBOARD;
        }
        else if (desc_str == "printer") {
            tag = PRINTER;
        }
        else if (desc_str == "monitor") {
            tag = MONITOR;
        }
        else if (desc_str == "allocate") {
            tag = ALLOCATE;
        }
        else if (desc_str == "mouse") {
            tag = MOUSE;
        }
        else if (desc_str == "speaker") {
            tag = SPEAKER;
        }
        else if (desc_str == "run") {
            tag = RUN;
        }
        else if (desc_str == "start") {
            tag = START;
        }
        else if (desc_str == "end") {
            tag = END;
        }
        else if (desc_str == "block") {
            tag = BLOCK;
        }
    }

    // Getting number of cycles from string, throwing error if missing
    if (tag_end == str.length() - 1) {
        throw invalid_argument("Error: Missing or negative cycle value");
    }
    else {
        cycle_str = str.substr(tag_end + 1);
    }

    // Getting int from cycles string
    cycles = atoi(cycle_str.c_str());

    // returning data in struct
    Operation data(code, cycles, tag);
    return data;
}
