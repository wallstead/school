/**
   Process Class - Handles PCB, threading, executing operations

 **/

#ifndef PROCESS_H
#define PROCESS_H

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <queue>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "Timer.h"
#include "OutputLog.h"

//This namespace fixes issues with to_string function
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//Global Output object
extern OutputLog global_log;

//Descriptor tags for meta data operations
enum descriptor {END, HARD_DRIVE, KEYBOARD, PRINTER, MONITOR, RUN, START, ALLOCATE, MOUSE, SPEAKER, BLOCK};

//PCB state
enum state {NEW, READY, RUNNING, WAITING, EXIT};

//Meta data operation struct
struct Operation {
  char code;
  int cycles;
  descriptor tag;

  Operation(char c, int t, descriptor d) : code(c), cycles(t), tag(d) {};
};

//Threading struct to pass data to thread function
struct Thread {
  int num_cycles;
  int cycle_time;
  
Thread(int n, int t) : num_cycles(n), cycle_time(t) {};
};


class Process {
 public:
  Process();
  Process(std::queue<Operation>, int, int, int, int, int, int, int, int, int);
  ~Process();

  void run();
  void execute(Operation);
  static void* execute_thread(void*);
  void change_state(state);
  int descriptor_to_cycles(descriptor);
  std::string descriptor_to_str(descriptor);
  unsigned int allocate_memory(int);


 private:
  int processor, monitor, hard_drive, printer, keyboard, memory, mouse, speaker;
  std::queue<Operation> operations;
  int proc_num;
  state proc_state;
};

#endif
