#include <iostream>
#include <fstream>
#include <cstdlib>
#include <stdexcept>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>
#include <sstream>


#ifndef SIM_H
#define SIM_H

#include "OutputLog.h"
#include "Timer.h"

//Global log object defined in main
extern OutputLog global_log;


  
//makes to_string function work
namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

//Descriptor tags for meta data operations
enum descriptor {END, HARD_DRIVE, KEYBOARD, PRINTER, MONITOR, RUN, START, ALLOCATE, MOUSE, SPEAKER, BLOCK};

//Possible choices for scheduling algorithm
enum scheduling_algorithm {FIFO, SJF, PS};

//PCB state
enum state {NEW, READY, RUNNING, WAITING, EXIT};

//Meta data operation struct
struct Operation {
  char code;
  int cycles;
  descriptor tag;

  Operation(char c, int t, descriptor d) : code(c), cycles(t), tag(d) {};
}; 

//Process struct
struct Process {
  int proc_num;
  bool semaphore;
  state proc_state;
  std::vector<Operation> operations_vector;
  std::queue<Operation> operations_queue;
  int num_operations;
  int num_IO;

Process(int n, state s) : proc_num(n), proc_state(s) {};

};

struct Resources {
  pthread_mutex_t* printers;
  pthread_mutex_t* hard_drives; 
};

//Threading struct to pass data to thread function
struct Thread {
  int num_cycles;
  int cycle_time;
  
Thread(int n, int t) : num_cycles(n), cycle_time(t) {};
};


class Simulator {
 public:
  //Constructor/Destructor
  Simulator(std::string);
  ~Simulator();

  //Functions to run the simulator
  void simulate();
  void FIFO_scheduling();
  void SJF_scheduling();
  void PS_scheduling();

  ///Parsing functions, queue building functions, init functions
  bool parse_config(const std::string&);
  bool parse_metadata(const std::string&);
  void initialize_resources();
  void build_op_queue();
  void build_proc_vector();
  void get_process_info();

  //Process handling functions
  void execute(Operation);
  static void* execute_thread(void*);
  inline void S_op(Operation);
  inline void A_op(Operation, std::string);
  inline void M_op(Operation, std::string);
  inline void P_op(Operation, std::string);
  inline void IO_op(Operation, std::string);
  unsigned int allocate_memory();
  void allocate_resource(int, descriptor);
  void deallocate_resource(int, descriptor);


  //Helper functions
  bool check_extension(const std::string&, const std::string&);
  bool is_code(char);
  bool is_digit(char);
  bool is_descriptor(const std::string);
  void remove_whitespace(std::string&);
  void to_lower(std::string&);
  int descriptor_to_cycles(descriptor);
  std::string descriptor_to_str(descriptor);
  std::string int_to_hex(int);
  Operation extract_operation(const std::string&);

 private:
  int processor, monitor, hard_drive, printer, keyboard, memory, mouse, speaker;
  int system_memory, block_size;
  int printer_quantity, hd_quantity;
  std::string config_file;
  std::string meta_file;
  std::string log_file;
  bool print_to_screen;
  bool print_to_file;
  std::queue<std::string> meta_data;
  std::queue<Operation> operation_queue;
  std::vector<Process> process_vector; 
  std::queue<Process> process_queue;
  Timer clock;
  scheduling_algorithm scheduler; 
  Resources system_resources;
};

#endif
