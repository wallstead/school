#include <iostream>
#include <stdexcept>
#include <fstream>
#include <string>
#include <vector>
#include "Queue.h"

#ifndef SimulatorHeader // to stop this file from being included more than once
#define SimulatorHeader

#include "Logger.h"
#include "Timer.h"

using namespace std;

// Descriptor tags for meta data operations
enum descriptor {
    END,
    HARD_DRIVE,
    KEYBOARD,
    PRINTER,
    MONITOR,
    RUN,
    START,
    ALLOCATE,
    MOUSE,
    SPEAKER,
    BLOCK
};

// Scheduling algorithms
enum schedulingAlgorithm {
    FIFO,
    SJF,
    PS };

// PCB states
enum pcbstate {
    NEW,
    READY,
    RUNNING,
    WAITING,
    EXIT };

// Meta data operation struct
struct Operation {
    char code;
    int cycles;
    descriptor tag;

    Operation(char code, int cycles, descriptor tag)
        : code(code)
        , cycles(cycles)
        , tag(tag){};
};

// Process struct
struct Process {
    int number;
    pcbstate state;
    bool semaphore; // only two
    vector<Operation> operationsVect;
    Queue<Operation> operationsQueue;
    int operationsCount;
    int ioCount;

    Process(int number, pcbstate currentState)
        : number(number)
        , state(currentState){};
};

struct Resources {
    pthread_mutex_t* printers;
    pthread_mutex_t* speakers;
    pthread_mutex_t* harddrives;
};

// Threading struct
struct Thread {
    int numberOfCycles;
    int cycleTime;

    Thread(int numberOfCycles, int cycleTime)
        : numberOfCycles(numberOfCycles)
        , cycleTime(cycleTime){};
};

class Simulator {
public:
    // Constructor
    Simulator(string);
    // Destructor
    ~Simulator();

    // To run simulation
    void simulate();
    void ioOperation(Operation, string);
    void schedulingFIFO();
    void schedulingSJF();
    void schedulingPS();

    // Parsing functions
    bool parseConfig(const string&);
    bool parseMetadata(const string&);
    void initResources();
    void addOperations();
    void addProcesses();
    void getProcessInfo();
    Operation operationFromString(const string&);

    // Process functions
    void execute(Operation);
    static void* executeThread(void*);
    unsigned int allocateMemory(int);
    void allocResource(int, descriptor);
    void deallocResource(int, descriptor);

    // Other functions
    bool checkExtension(const string&, const string&);
    bool isCode(char);
    bool isDigit(char);
    bool isDescriptor(const string);
    void cleanString(string&);
    void dropCase(string&);
    int descriptorToCycles(descriptor);
    string descriptorToString(descriptor);
    string hexString(int);

private:
    int processor, monitor, harddrive, printer, keyboard, memory, mouse, speaker,
        systemMemory, blockSize, printerQuantity, harddriveQuantity, speakerQuantity;
    string configFileName;
    ifstream configFileContents;
    string metaFileName;
    ifstream metaFileContents;
    string logFileName;
    bool printToFile;
    bool printToScreen;
    Queue<string> metaData;
    Queue<Operation> operations;
    vector<Process> processes;
    Queue<Process> scheduledProcesses;
    Timer clock;
    schedulingAlgorithm scheduler;
    Logger logger;
    Resources systemResources;
};

#endif
