/**
 * @file PA05.cpp
 *
 * @brief Main driver for project 5
 *
 * @author Willis Allstead
 *
 * @version 1.0
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <ctime> // for CPU time
#include "Merge.h"
#include "ArrayQueue.h"
#include "PriorityQueue.h"

using namespace std;

struct Event {
    char type; // A: Arrival, D: Departure
    int startTime;
    int duration;
    int customerID;

    bool operator > (const Event &rhs ) const {
        if (startTime < rhs.startTime) {
            return true;
        } else {
            return false;
        }
    }

    bool operator < (const Event &rhs ) const {
        if (startTime > rhs.startTime) {
            return true;
        } else {
            return false;
        }
    }

    bool operator != (const Event &rhs ) const {
        if (startTime != rhs.startTime) {
            return true;
        } else {
            return false;
        }
    }


};

struct Teller {
    bool available;
};

struct ProcessData { // This will be used to get data from each simulation
    int cpuTime;
    int virtualTime;
    int maxWaitTime;
    int avgWaitTime;
    int maxLineLength;
    int avgLineLength;
};

void populateFile(int, string const&);
ProcessData simulate(PriorityQueue<Event> &, ArrayQueue<Event> bankLines[], int, int);
int processArrival(Event, PriorityQueue<Event> &, ArrayQueue<Event> &, Teller &, int);
int processDeparture(Event, PriorityQueue<Event> &, ArrayQueue<Event> &, Teller &, int);

int main() {

    const int numEvents = 9999;

    /* Prep rand-num generator */
    srand( time( NULL ) );

    /* Populate the file with start times */
    std::string hundredThousand("events");
    populateFile(numEvents, hundredThousand);

    /* Initialize two queues */
    ArrayQueue<Event> bankLine;
    PriorityQueue<Event> eventPriorityQueue;

    /* Read file into eventPriorityQueue */
    Event events[numEvents];
    ifstream hundredThousandFile("events");
    if (hundredThousandFile.is_open()) {
        int startTime;
        int duration;
        int counter = 0;
        while(hundredThousandFile >> startTime >> duration) {
            Event newEvent;
            newEvent.type = 'A';
            newEvent.startTime = startTime;
            newEvent.duration = duration;
            newEvent.customerID = counter;
            events[counter] = newEvent; // add it to array

            cout << newEvent.type << " | " << newEvent.startTime << " | " << newEvent.duration << " | " << newEvent.customerID <<  endl; // DEBUG ONLY

            eventPriorityQueue.enqueue(newEvent);

            counter++;
        }
        hundredThousandFile.close();
    } else {
        cout << "Cannot open hundred thousand integer file";
    }

    /* Single queue for one teller */


    ArrayQueue<Event> bankLines[1];
    bankLines[0] = bankLine;
    ProcessData data1 = simulate(eventPriorityQueue, bankLines, 1, 1);

    cout << "Elapsed CPU Time     : " << data1.cpuTime << endl;
    cout << "Elapsed Virtual Time : " << data1.virtualTime << endl;
    cout << "Max Wait Time        : " << data1.maxWaitTime << endl;
    cout << "Avg Wait Time        : " << data1.avgWaitTime << endl;
    cout << "Max Line Length      : " << data1.maxLineLength << endl;
    cout << "Avg Line Length      : " << data1.avgLineLength << endl;

    /* Three queues for three tellers (events take turn in the order of arrival or enter the shortest line) */

    ArrayQueue<Event> bankLinesThree[3];
    for (int k = 0; k < 3; k++) {  // add three queues to bankLines
        ArrayQueue<Event> bankLine_new;
        bankLinesThree[k] = bankLine_new;
    }

    // create new priority queue with same data as before
    PriorityQueue<Event> eventQueueThreeTeller;
    for (int i = 0; i < numEvents; i++) {
        Event event;
        event.type = events[i].type;
        event.startTime = events[i].startTime;
        event.duration = events[i].duration;
        eventQueueThreeTeller.enqueue(event);
    }

    ProcessData data2 = simulate(eventQueueThreeTeller, bankLinesThree, 3, 3);

    cout << "Elapsed CPU Time     : " << data2.cpuTime << endl;
    cout << "Elapsed Virtual Time : " << data2.virtualTime << endl;
    cout << "Max Wait Time        : " << data2.maxWaitTime << endl;
    cout << "Avg Wait Time        : " << data2.avgWaitTime << endl;
    cout << "Max Line Length      : " << data2.maxLineLength << endl;
    cout << "Avg Line Length      : " << data2.avgLineLength << endl;

    /* Single queue for three tellers */

    ArrayQueue<Event> bankLinesOne[1];
    ArrayQueue<Event> bankLine_single;
    bankLinesOne[0] = bankLine_single;

    // create new priority queue with same data as before
    PriorityQueue<Event> eventQueueThreeTellerSingleLine;
    for (int i = 0; i < numEvents; i++) {
        Event event;
        event.type = events[i].type;
        event.startTime = events[i].startTime;
        event.duration = events[i].duration;
        eventQueueThreeTellerSingleLine.enqueue(event);
    }

    ProcessData data3 = simulate(eventQueueThreeTellerSingleLine, bankLinesOne, 3, 1);

    cout << "Elapsed CPU Time     : " << data3.cpuTime << endl;
    cout << "Elapsed Virtual Time : " << data3.virtualTime << endl;
    cout << "Max Wait Time        : " << data3.maxWaitTime << endl;
    cout << "Avg Wait Time        : " << data3.avgWaitTime << endl;
    cout << "Max Line Length      : " << data3.maxLineLength << endl;
    cout << "Avg Line Length      : " << data3.avgLineLength << endl;

    cout << "Single queue with how many tellers? ";
    int tellerCount;
    cin >> tellerCount;

    ArrayQueue<Event> bankLinesSingle[1];
    ArrayQueue<Event> bankLine_onlyOne;
    bankLinesSingle[0] = bankLine_onlyOne;

    // create new priority queue with same data as before
    PriorityQueue<Event> eventQueueArbitraryTellerSingleLine;
    for (int i = 0; i < numEvents; i++) {
        Event event;
        event.type = events[i].type;
        event.startTime = events[i].startTime;
        event.duration = events[i].duration;
        eventQueueArbitraryTellerSingleLine.enqueue(event);
    }

    ProcessData data4 = simulate(eventQueueArbitraryTellerSingleLine, bankLinesSingle, tellerCount, 1);
    cout << "Elapsed CPU Time     : " << data4.cpuTime << endl;
    cout << "Elapsed Virtual Time : " << data4.virtualTime << endl;
    cout << "Max Wait Time        : " << data4.maxWaitTime << endl;
    cout << "Avg Wait Time        : " << data4.avgWaitTime << endl;
    cout << "Max Line Length      : " << data4.maxLineLength << endl;
    cout << "Avg Line Length      : " << data4.avgLineLength << endl;



    return 0;
}

void populateFile(int count, std::string const& file) {
    std::ofstream myfile(file);
    if (!myfile) {
       return;
    }

    /* Populate the array with random start times */
    int randArr[count];
    for(int index = 0; index < count; index++) {
        int random_start = (rand()%(count+1)); // from 0 to 100000
        randArr[index] = random_start;
    }

    /* Sort array by start time */
    Merge merge = Merge(randArr, count); // sort random array using merge sort
    merge.sort(0, count-1);

    /* Put values in file along with random durations for each */
    for(int index = 0; index < count; index++) {
        int random_duration = (rand()%100)+1; // from 1 to 100
        myfile << merge.data[index] << " " << random_duration << "\n";
    }
}

ProcessData simulate(PriorityQueue<Event> &eventPriorityQueue, ArrayQueue<Event> bankLines[], int tellerCount, int lineCount) {
    cout << "--Simulation with " << lineCount << " queues and " << tellerCount << " tellers--" << endl;

    ProcessData data;

    double elapsedCPUTime = 0;
    int totalVirtualTime = 0; // the "startTime" of the last departure event
    clock_t start = clock(); // start timer

    Teller tellers[tellerCount];
    for (int i = 0; i < tellerCount; i++) { // Add tellers to teller array
        Teller teller;
        teller.available = true;
        tellers[i] = teller;
    }

    int totalWaitTime = 0;
    int customerCount = 0;
    int maxWaitTime = 100;
    int maxLineLength = 0;
    int totalLineLength = 0;

    while (!eventPriorityQueue.isEmpty()) { // until event queue is empty
        customerCount++;
        Event newEvent = eventPriorityQueue.peek();
        int currentTime = newEvent.startTime;
        totalVirtualTime = newEvent.startTime;

        /* Find available teller if any */
        Teller *bestTeller = &tellers[0];
        for (int j = 0; j < tellerCount; j++) {
            if (tellers[j].available) {
                bestTeller = &tellers[j];
            }
        }


        for (int k = 0; k < lineCount; k++) {
            totalLineLength += bankLines[k].count;
            if (bankLines[k].count > maxLineLength) {
                maxLineLength = bankLines[k].count;
            }
        }

        // Event visitedCustomers[99999]; customer

        if (newEvent.type == 'A') { // Arrival
            /* Find shortest line */
            ArrayQueue<Event> *shortestLine = &bankLines[0];
            for (int j = 0; j < lineCount; j++) {
                if (bankLines[j].count < shortestLine->count) {
                    shortestLine = &bankLines[j];
                }
            }

            totalWaitTime += processArrival(newEvent, eventPriorityQueue, *shortestLine, *bestTeller, currentTime);
        } else { // Departure
            /* Find line with customer at highest priority */
            ArrayQueue<Event> *highestPriorityLine = &bankLines[0];
            for (int j = 0; j < lineCount; j++) {
                if (!bankLines[j].isEmpty() && !highestPriorityLine->isEmpty()) {
                    if (bankLines[j].peekFront() < highestPriorityLine->peekFront()) {
                        highestPriorityLine = &bankLines[j];
                    }
                } else {
                }
            }
            totalWaitTime += processDeparture(newEvent, eventPriorityQueue, *highestPriorityLine, *bestTeller, currentTime);
        }
    }


    clock_t finish = clock(); // end timer
    elapsedCPUTime = double(finish - start); // set elapsed CPU time

    data.cpuTime = elapsedCPUTime;
    data.virtualTime = totalVirtualTime;
    data.maxWaitTime = maxWaitTime;
    data.avgWaitTime = totalWaitTime/customerCount;
    data.maxLineLength = maxLineLength;
    data.avgLineLength = maxLineLength/customerCount;

    return data;
}

int processArrival(Event event, PriorityQueue<Event> &eventQueue
                               , ArrayQueue<Event> &bankLine
                               , Teller &bestTeller
                               , int currentTime) {
    int waitTime = 0; // initialize wait time

    eventQueue.dequeue(); // remove the event from the event queue
    if (bankLine.isEmpty() && bestTeller.available) {
        int endTime = currentTime + event.duration;
        waitTime = endTime-event.startTime;

        Event newDepartureEvent;
        newDepartureEvent.type = 'D';
        newDepartureEvent.startTime = endTime;
        eventQueue.enqueue(newDepartureEvent);

        bestTeller.available = false;
    } else {
        bankLine.enqueue(event); // add event of the customer to the line
    }

    return waitTime;
}

int processDeparture(Event event,PriorityQueue<Event> &eventQueue
                               , ArrayQueue<Event> &bankLine
                               , Teller &bestTeller
                               , int currentTime) {
    int waitTime = 0; // initialize wait time

    eventQueue.dequeue(); // remove the event from the event queue
    if (!bankLine.isEmpty()) {
        Event nextCustomer = bankLine.peekFront();
        bankLine.dequeue(); // remove the customer from the line
        int endTime = currentTime + nextCustomer.duration;
        waitTime = endTime-event.startTime;

        Event newDepartureEvent;
        newDepartureEvent.type = 'D';
        newDepartureEvent.startTime = endTime;
        eventQueue.enqueue(newDepartureEvent);
    } else {
        bestTeller.available = true;
    }

    return waitTime;
}
