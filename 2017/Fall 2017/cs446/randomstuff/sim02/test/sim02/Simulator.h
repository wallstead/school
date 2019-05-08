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
#include "Process.h"
#include "Timer.h"

extern OutputLog global_log;
  
class Simulator {
 public:
  //Constructor/Destructor
  Simulator(std::string);
  ~Simulator();

  ///Parsing functions
  bool parse_config(const std::string&);
  bool parse_metadata(const std::string&);
  void build_op_queue();
  void build_proc_queue();
  void simulate();

  //Helper functions
  bool check_extension(const std::string&, const std::string&);
  Operation extract_operation(const std::string&);
  bool is_code(char);
  bool is_digit(char);
  bool is_descriptor(const std::string);
  void remove_whitespace(std::string&);
  void to_lower(std::string&);

 private:
  int processor, monitor, hard_drive, printer, keyboard, memory, mouse, speaker;
  std::string config_file;
  std::string meta_file;
  std::string log_file;
  bool print_to_screen;
  bool print_to_file;
  std::queue<std::string> meta_data;
  std::queue<Operation> operation_queue;
  std::queue<Process> process_queue;
 
};

#endif
