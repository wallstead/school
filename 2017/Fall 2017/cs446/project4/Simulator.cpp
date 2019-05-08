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
            addOperations(); // yes
            addProcesses(); // yes
            getProcessInfo();
            initResources();
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
    //Call scheduling functions to organize processes accordingly
    switch (scheduler) {
    case FIFO:
        schedulingFIFO();
        break;
    case SJF:
        schedulingSJF();
        break;
    case PS:
        schedulingPS();
        break;
    }

    clock.start();

    // Looping through process queue
    while (!scheduledProcesses.empty()) {
        // Get process at front of queue
        Process proc = scheduledProcesses.front();

        // Set process state to ready and semaphore to true
        proc.state = READY;
        proc.semaphore = true;
        string processName = "Process " + to_string(proc.number);

        // Looping through operations for current process
        while (!proc.operationsQueue.empty()) {
            Operation current = proc.operationsQueue.front();
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
                    logger.log("OS: preparing " + processName);
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("OS: starting " + processName);
                }
                else {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log("OS: removing " + processName);
                }
                proc.state = READY;
            }
            else if (current.code == 'P') {
                proc.state = WAITING;
                logger.timeStamp(clock.elapsedTime());
                logger.log(processName + ": start processing action");
                execute(current);
                logger.timeStamp(clock.elapsedTime());
                logger.log(processName + ": end processing action");
                proc.state = READY;
            }
            else if (current.code == 'M') {
                proc.state = WAITING;
                if (current.tag == ALLOCATE) {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(processName + ": allocating memory");
                    string memoryLocation = hexString(allocateMemory(systemMemory)); // just printing it for now
                    execute(current);
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(processName + ": memory allocated at " + memoryLocation);
                }
                else if (current.tag == BLOCK) {
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(processName + ": start memory blocking");
                    execute(current);
                    logger.timeStamp(clock.elapsedTime());
                    logger.log(processName + ": end memory blocking");
                }
                proc.state = READY;
            }
            else if (current.code == 'I' || current.code == 'O') {
                proc.semaphore = false;
                proc.state = WAITING;
                ioOperation(current, processName);
                proc.semaphore = true;
                proc.state = READY;
            }
            // Remove operation from queue once it executes
            proc.operationsQueue.pop();
        }
        // Remove process from queue once it is finished executing

        scheduledProcesses.pop();
    }

    //Log ending time of simulator
    logger.timeStamp(clock.elapsedTime());
    logger.log("Simulator program ending");
}

void Simulator::ioOperation(Operation current, string processName)
{
    // Static variables to keep track of current printer and hd
    static int currentPrinter = 0;
    static int currentHarddrive = 0;
    static int currentSpeaker = 0;

    // Used to allocate / deallocate resources
    int p_index = currentPrinter;
    int hd_index = currentHarddrive;
    int s_index = currentSpeaker;

    if (current.code == 'I') {
        // Input Operation

        logger.timeStamp(clock.elapsedTime());
        if (current.tag == PRINTER) {
            string p_num = to_string(currentPrinter);
            allocResource(p_index, PRINTER);
            logger.log(processName + ": start " + descriptorToString(current.tag) + " input on PRNTR " + p_num);
            currentPrinter++;
            if (currentPrinter == printerQuantity) {
                currentPrinter = 0;
            }
        }
        else if (current.tag == HARD_DRIVE) {
            string hd_num = to_string(currentHarddrive);
            allocResource(hd_index, HARD_DRIVE);
            logger.log(processName + ": start " + descriptorToString(current.tag) + " input on HDD " + hd_num);
            currentHarddrive++;
            if (currentHarddrive == harddriveQuantity) {
                currentHarddrive = 0;
            }
        }
        else if (current.tag == SPEAKER) {
            string s_num = to_string(currentSpeaker);
            allocResource(s_index, SPEAKER);
            logger.log(processName + ": start " + descriptorToString(current.tag) + " input on HDD " + s_num);
            currentSpeaker++;
            if (currentSpeaker == speakerQuantity) {
                currentSpeaker = 0;
            }
        }
        else {
            logger.log(processName + ": start " + descriptorToString(current.tag) + " input");
        }
        //Threading
        Thread data(current.cycles, descriptorToCycles(current.tag));
        pthread_t t1;
        pthread_create(&t1, NULL, &executeThread, &data);
        pthread_join(t1, NULL);
        logger.timeStamp(clock.elapsedTime());
        logger.log(processName + ": end " + descriptorToString(current.tag) + " input");

        /* now deallocate if necessary */
        if (current.tag == PRINTER)
            deallocResource(p_index, PRINTER);
        else if (current.tag == HARD_DRIVE)
            deallocResource(hd_index, HARD_DRIVE);
        else if (current.tag == SPEAKER)
            deallocResource(s_index, SPEAKER);
    }
    else { // Output operation

        logger.timeStamp(clock.elapsedTime());
        if (current.tag == PRINTER) {
            string p_num = to_string(currentPrinter);
            allocResource(p_index, PRINTER);
            logger.log(processName + ": start " + descriptorToString(current.tag) + " output on PRNTR " + p_num);
            currentPrinter++;
            if (currentPrinter == printerQuantity)
                currentPrinter = 0;
        }
        else if (current.tag == HARD_DRIVE) {
            string hd_num = to_string(currentHarddrive);
            allocResource(hd_index, HARD_DRIVE);
            logger.log(processName + ": start " + descriptorToString(current.tag) + " output on HDD " + hd_num);
            currentHarddrive++;
            if (currentHarddrive == harddriveQuantity)
                currentHarddrive = 0;
        }
        else if (current.tag == SPEAKER) {
            string s_num = to_string(currentSpeaker);
            allocResource(s_index, SPEAKER);
            logger.log(processName + ": start " + descriptorToString(current.tag) + " output on SPKR " + s_num);
            currentSpeaker++;
            if (currentSpeaker == speakerQuantity)
                currentSpeaker = 0;
        }
        else {
            logger.log(processName + ": start " + descriptorToString(current.tag) + " output");
        }
        //Threading
        Thread data(current.cycles, descriptorToCycles(current.tag));
        pthread_t t1;
        pthread_create(&t1, NULL, &executeThread, &data);
        pthread_join(t1, NULL);
        logger.timeStamp(clock.elapsedTime());
        logger.log(processName + ": end " + descriptorToString(current.tag) + " output");

        /* now deallocate if necessary */
        if (current.tag == PRINTER)
            deallocResource(p_index, PRINTER);
        else if (current.tag == HARD_DRIVE)
            deallocResource(hd_index, HARD_DRIVE);
        else if (current.tag == SPEAKER)
            deallocResource(s_index, SPEAKER);
    }
}

// FIFO scheduling
void Simulator::schedulingFIFO()
{

    for (Process& proc : processes) {

        scheduledProcesses.push(proc);
    }
}

// SJF scheduling
void Simulator::schedulingSJF()
{
    //Sorting processes by number of operations (from smallest to largest)
    while (!processes.empty()) {
        int index_of_smallest;
        //set smallest_num_jobs to arbitrarily large #
        int smallest_num_jobs = 10000000;
        //find the shortest process currently in the unsorted queue
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].operationsCount < smallest_num_jobs) {
                index_of_smallest = i;
                smallest_num_jobs = processes[i].operationsCount;
            }
        }

        //Push shortest process to queue
        scheduledProcesses.push(processes[index_of_smallest]);

        //Remove shortest from vector so next shortest can be identified
        std::swap(processes[index_of_smallest], processes.back());
        processes.pop_back();
    }
}

// Priority scheduling
void Simulator::schedulingPS()
{
    while (!processes.empty()) {
        int index_of_largest;
        int largest_ioCount = -1;

        //find the process with the largest number of I/O operations
        for (int i = 0; i < processes.size(); i++) {
            if (processes[i].ioCount > largest_ioCount) {
                index_of_largest = i;
                largest_ioCount = processes[i].ioCount;
            }
        }

        //Push process with highest number of IO operations to queue
        scheduledProcesses.push(processes[index_of_largest]);

        //Remove process with highest number of IO operations so next highest can be identified
        std::swap(processes[index_of_largest], processes.back());
        processes.pop_back();
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
            else if (configKey == "cpuschedulingcode") {
                dropCase(configValue);
                if (configValue == "fifo") {
                    scheduler = FIFO;
                }
                else if (configValue == "ps") {
                    scheduler = PS;
                }
                else if (configValue == "sjf") {
                    scheduler = SJF;
                }
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
                if (configKey.find("quantity") != string::npos) {
                    harddriveQuantity = value;
                }
                else {
                    harddrive = value;
                    componentCount++;
                }
            }
            else if (configKey.find("printer") != string::npos) {
                if (configKey.find("quantity") != string::npos) {
                    printerQuantity = value;
                }
                else {
                    printer = value;
                    componentCount++;
                }
            }
            else if (configKey.find("keyboard") != string::npos) {
                keyboard = value;
                componentCount++;
            }
            else if (configKey.find("memory") != string::npos) {
                if (configKey.find("system") != string::npos) {
                    if (configKey.find("kbytes") != string::npos) {
                        systemMemory = value;
                    }
                    else if (configKey.find("mbytes") != string::npos) {
                        systemMemory = value * 1000;
                    }
                    else if (configKey.find("gbytes") != string::npos) {
                        systemMemory = value * 1000000;
                    }
                }
                else if (configKey.find("block") != string::npos) {
                    blockSize = value;
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
                if (configKey.find("quantity") != string::npos) {
                    speaker = value;
                }
                else {
                    speaker = value;
                    componentCount++;
                }
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

// initialize resources (printer and speaker will be used as per Vineeth)
void Simulator::initResources()
{
    //Dynamically allocate array of mutexes for printers and hard drives
    systemResources.printers = new pthread_mutex_t[printerQuantity];
    systemResources.speakers = new pthread_mutex_t[speakerQuantity];

    //Initialize printer mutexes
    for (int i = 0; i < printerQuantity; i++)
        systemResources.printers[i] = PTHREAD_MUTEX_INITIALIZER;

    //Initialize hd mutexes
    for (int i = 0; i < speakerQuantity; i++)
        systemResources.speakers[i] = PTHREAD_MUTEX_INITIALIZER;
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

// To build a queue of processes
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
        new_proc->operationsVect.push_back(current);

        if (current.code == 'A' && current.tag == END) {
            processes.push_back(*new_proc);
            new_proc = NULL;
            create_new = true;
        }

        operations.pop();
    }
}

// getting/setting info of the process
void Simulator::getProcessInfo()
{

    for (Process& current_process : processes) {
        //initialize number of operations and number of IO operations to 0
        current_process.operationsCount = 0;
        current_process.ioCount = 0;

        for (Operation& current_op : current_process.operationsVect) {
            //Increment number of operations in process and push operation into queue
            current_process.operationsCount++;
            current_process.operationsQueue.push(current_op);

            if (current_op.code == 'I' || current_op.code == 'O')
                current_process.ioCount++;
        }
    }
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

// to allocate the memory
unsigned int Simulator::allocateMemory(int totMem)
{
    static unsigned int address = 0; // as stated in instructions
    unsigned int current = address;

    if (address + blockSize > systemMemory) {
        address = 0; // wrap
    }
    else {
        address = address + blockSize;
    }

    return current;
}

//Allocates a resource to a process by locking that resources mutex
void Simulator::allocResource(int resourceNumber, descriptor type)
{
    switch (type) {
    case PRINTER:
        pthread_mutex_lock(&systemResources.printers[resourceNumber]);
        break;

    case HARD_DRIVE:
        pthread_mutex_lock(&systemResources.harddrives[resourceNumber]);
        break;

    case SPEAKER:
        pthread_mutex_lock(&systemResources.speakers[resourceNumber]);
        break;
    }
}

//Deallocates a resource from a process by unlocking that resources mutex
void Simulator::deallocResource(int resourceNumber, descriptor type)
{
    switch (type) {
    case PRINTER:
        pthread_mutex_unlock(&systemResources.printers[resourceNumber]);
        break;

    case HARD_DRIVE:
        pthread_mutex_unlock(&systemResources.harddrives[resourceNumber]);
        break;

    case SPEAKER:
        pthread_mutex_unlock(&systemResources.speakers[resourceNumber]);
        break;
    }
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
        return harddrive;
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
    string description;
    string cycleString;
    descriptor tag;

    char code = str[0];
    int cycles;
    int tagStart;
    int tagEnd;

    // If is_code returns false then given code is invalid
    if (isCode(code) == false) {
        throw invalid_argument("Error: Invalid metadata code value");
    }

    // Getting descriptor tag from string
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') {
            tagStart = i + 1;
        }
        else if (str[i] == ')') {
            tagEnd = i;
        }
    }
    description = str.substr(tagStart, tagEnd - tagStart);

    if (isDescriptor(description) == false) {
        throw invalid_argument("Error: Invalid metadata descriptor tag");
    }
    else {
        if (description == "harddrive") {
            tag = HARD_DRIVE;
        }
        else if (description == "keyboard") {
            tag = KEYBOARD;
        }
        else if (description == "printer") {
            tag = PRINTER;
        }
        else if (description == "monitor") {
            tag = MONITOR;
        }
        else if (description == "allocate") {
            tag = ALLOCATE;
        }
        else if (description == "mouse") {
            tag = MOUSE;
        }
        else if (description == "speaker") {
            tag = SPEAKER;
        }
        else if (description == "run") {
            tag = RUN;
        }
        else if (description == "start") {
            tag = START;
        }
        else if (description == "end") {
            tag = END;
        }
        else if (description == "block") {
            tag = BLOCK;
        }
    }

    // Getting number of cycles from string, throwing error if missing
    if (tagEnd == str.length() - 1) {
        throw invalid_argument("Error: Missing or negative cycle value");
    }
    else {
        cycleString = str.substr(tagEnd + 1);
    }

    // Getting int from cycles string
    cycles = atoi(cycleString.c_str());

    // returning data in struct
    Operation data(code, cycles, tag);
    return data;
}
