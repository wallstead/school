#include "Simulator.h"

//Mutex Lock that will be used
pthread_mutex_t mutex_count = PTHREAD_MUTEX_INITIALIZER;

/* 
***************************************************************CONSTRUCTOR AND DESTRUCTOR***************************************************************
*/

//Constructor
Simulator::Simulator(std::string cf)
{
  config_file = cf;
  if( parse_config(config_file) ) {
    
    global_log.load_config(print_to_file, print_to_screen, log_file);

    if( parse_metadata(meta_file) ) {
      build_op_queue();
      build_proc_queue();
      simulate();
    }
  }
}

//Destructor
Simulator::~Simulator()
{

}



/* 
***************************************************************SIMULATOR FUNCTION***************************************************************
*/
//Runs simulation
void Simulator::simulate()
{
  clock.start();

  //Looping through process queue
  while( !process_queue.empty() ) {
    //Get process at front of queue
    Process proc = process_queue.front();

    //Set process state to ready and semaphore to true
    proc.proc_state = READY;
    proc.semaphore = true;
    std::string num =  patch::to_string(proc.proc_num);
    std::string proc_name = "Process " + num;

    //Looping through operations for current process
    while( !proc.operations.empty() ) {
      Operation current = proc.operations.front();
      proc.proc_state = RUNNING;

      if(current.code == 'S') {
	//Start code
	proc.proc_state = WAITING;
	S_op(current);
	proc.proc_state = READY;
      }
      else if(current.code == 'A') {
	//Application code
	proc.proc_state = WAITING;
	A_op(current, proc_name);
	proc.proc_state = READY;
      }
      else if(current.code == 'P') {
	//Process code
	proc.proc_state = WAITING;
	P_op(current, proc_name);
	proc.proc_state = READY;
      }
      else if(current.code == 'M') {
	//Memory code
	proc.proc_state = WAITING;
	M_op(current, proc_name);
	proc.proc_state = READY;
      }
      else if(current.code == 'I' || current.code == 'O') {
	//Input or output code
	proc.semaphore = false;
	proc.proc_state = WAITING;
	IO_op(current, proc_name);
	proc.semaphore = true;
	proc.proc_state = READY;
      }
      //Remove operation from queue once it executes
      proc.operations.pop();
    }
    //Remove process from queue once it is finished executing
    process_queue.pop();
  }
}

/* 
***************************************************************PARSING FUNCTIONS***********************************************************************
**********************************************************AND QUEUE BUILDING FUNCTIONS*****************************************************************
*/

//Parses config file
bool Simulator::parse_config(const std::string& file)
{
  //Checking for valid file extension
  if(!this->check_extension(file, ".conf")) {
    throw std::invalid_argument("Error: invalid config file extension");
    return false;
  }

  //Opening file   
  std::ifstream config_file(file.c_str());
  std::string line;

  //Checking if file is empty
  if(config_file.peek() == std::ifstream::traits_type::eof()) {
    throw std::invalid_argument("Error: Empty config file");
  }
 
  int err_count = 0;

  //parsing the config file line by line
  while(std::getline(config_file, line)) {
    std::string delimiter = ":";
    if(line.find(delimiter) == std::string::npos) {

      }
      else {
	//config_token = info before :, token_val = info after :
	std::string config_token = line.substr(0, line.find(delimiter));
	std::string token_val = line.substr(line.find(delimiter) + 1);

	//removing whitespace and converting lowercase
	remove_whitespace(config_token);
	remove_whitespace(token_val);
      	to_lower(config_token);

	//Checks tokens and processes them as needed
	if(config_token == "filepath") {
	  //metadata file path
	  meta_file = token_val;
	}
	else if(config_token == "log") {
	  //log information
	  to_lower(token_val);

	  if(token_val == "logtoboth") {
	    //logging to monitor and file
	    print_to_screen = true;
	    print_to_file = true;
	  }
	  else if(token_val == "logtomonitor ") {
	    //logging to just screen
	    print_to_screen = true;
	    print_to_file = false;
	  }
	  else if(token_val == "logtofile") {
	    //logging to just file
	    print_to_screen = false;
	    print_to_file = true;
	  }
	}
	else if(config_token == "logfilepath") {
	  //file path for log file
	  log_file = token_val;
	}
      
	int time = std::atoi(token_val.c_str());

	if(config_token.find("processor") != std::string::npos) {
	  processor = time;
	  err_count++;
	}
	else if(config_token.find("monitor") != std::string::npos) {
	  monitor = time;
	  err_count++;
	}
	else if((config_token.find("hard") != std::string::npos) && (config_token.find("drive") != std::string::npos)) {
	  if(config_token.find("quantity") != std::string::npos) {
	    hd_quantity = time;
	  }
	  else {
	    hard_drive = time;	 
	    err_count++;
	  }
	}
	else if(config_token.find("printer") != std::string::npos) {
	  if(config_token.find("quantity") != std::string::npos) {
	    printer_quantity = time;
	  }
	  else {
	    printer = time;
	    err_count++;
	  }
	}
	else if(config_token.find("keyboard") != std::string::npos) {
	  keyboard = time;
	  err_count++;
	}
	else if(config_token.find("memory") != std::string::npos) {
	  if(config_token.find("system") != std::string::npos) {
	    system_memory = time;
	  }
	  else if(config_token.find("block") != std::string::npos) {
	    block_size = time;
	  }
	  else {
	    memory = time;
	    err_count++;
	  }
	}
	else if(config_token.find("mouse") != std::string::npos) {
	  mouse = time;
	  err_count++;
	}
	else if(config_token.find("speaker") != std::string::npos) {
	  speaker = time;
	  err_count++;
	}
      } 
  }  

  //Checking if config file had all information needed
  if(err_count < 8) {
    throw std::invalid_argument("Error: missing configuration data - expected data for 8 components");
  }
  
  //closing file and return true
  config_file.close();

  return true;
}

//Parses through meta data file and extracts relevant information
bool Simulator::parse_metadata(const std::string& file)
{
  if(!this->check_extension(file, ".mdf")) {
    throw std::invalid_argument("Error: invalid metadata file extension");
    return false;
  }

  //Opening file   
  std::ifstream meta_file (file.c_str());
  std::string line;

  //Checking if file is empty
  if(meta_file.peek() == std::ifstream::traits_type::eof()) {
    throw std::invalid_argument("Error: Empty metadata file");
  }

  //bools - flags to identify when full command has been parsed. ints - indexes to keep track of command
  bool start_found  = false;
  bool end_found = false;
  int start_pos;
  int end_pos;

  //Looping through each line
  while(std::getline(meta_file, line)) {
    //remove whitespace from to make parsing simpler
    remove_whitespace(line);



    //Loop through each character of the line
    for(int i = 0; i < line.length(); i++) {
	if(line[i] == '(') {
	  //If current char is (, then char immediately before should be meta data code
	  int pos = i - 1;
	  
	  //Save position of meta data code and set flag to true
	  start_pos = pos;
	  start_found = true;
	}
	else if(line[i] == ')') {
	  //If current char is ), then next characters should be # of cycles
	  int pos = i + 1;
	 
	  //iterate until character is not a digit
	  while(is_digit(line[pos])) {
	    pos++;
	  }
	 
	  //Save first non-digit index as end position, set flag to true
	  end_pos = pos;
	  end_found = true;
	}
	
       
	if(start_found && end_found) {
	  //Extract command substring from line and push onto queue, reset flags
	  std::string token = line.substr(start_pos, end_pos-start_pos);
	  meta_data.push(token);
	  start_found = false;
	  end_found = false;
	  }
    }
  }

  //close file and return true
  meta_file.close();
  return true;
}

//Builds a queue of operations
void Simulator::build_op_queue()
{
  std::string current;
  bool s_flag = false;

  //Looping through queue
  while(!meta_data.empty()) {
    current = meta_data.front();

    Operation new_op = extract_operation(current);

   
    if (new_op.code == 'S' && new_op.tag == START) {
      if (s_flag == false)
	s_flag = true;
      else
	throw std::invalid_argument("Error: Illegal S(start) command - no more than 1 per meta file");
    }
    operation_queue.push(new_op);

    meta_data.pop();
  }
}

//Builds a queue of processes
void Simulator::build_proc_queue()
{
  Process *new_proc;
  bool create_new = true;
  
  while(!operation_queue.empty()) {
    if(create_new) {
      new_proc = new Process(process_queue.size() + 1, NEW);
      create_new = false;
    }

    Operation current = operation_queue.front();
    new_proc->operations.push(current);

    if(current.code == 'A' && current.tag == END) {
      process_queue.push(*new_proc);
      new_proc = NULL;
      create_new = true;
    }
    
    operation_queue.pop();

  }

  Process last(process_queue.size() + 1, NEW);
  Operation end('S', 0, END);
  last.operations.push(end);
  process_queue.push(last);  
}

/* 
***************************************************************PROCESS HANDLING FUNCTIONS***************************************************************
*/

//Executes operation without threading
void Simulator:: execute(Operation op)
{
  Timer clock; 
  
  for(int i = 0; i < op.cycles; i++) {
    clock.start();
    while(clock.elapsed_milli() < descriptor_to_cycles(op.tag));
  }

}

//Executes operation using threading and mutex locking
void* Simulator:: execute_thread(void* p)
{
  //Mutex lock
  pthread_mutex_lock( &mutex_count ); 

  //Executing thread
  Thread* op = (Thread*) p;
  Timer clock; 
  for(int i = 0; i < op->num_cycles; i++) {
    clock.start();
    while(clock.elapsed_milli() < op->cycle_time);
  }

  //Mutex unlock
  pthread_mutex_unlock( &mutex_count );
}

//Handles any operation with S code
void Simulator :: S_op(Operation current)
{
  if(current.tag == START) {
    global_log.time_stamp(clock.elapsed_time());
    global_log.log("Simulator program starting");
  }
  else {
    global_log.time_stamp(clock.elapsed_time());
    global_log.log("Simulator program ending");
  }
}

//Handles any operation with A code
inline void Simulator :: A_op(Operation current, std::string proc_name)
{
  if(current.tag == START) {
    global_log.time_stamp(clock.elapsed_time());
    global_log.log("OS: preparing " + proc_name);
    global_log.time_stamp(clock.elapsed_time());
    global_log.log("OS: starting process " + proc_name);
  }
  else {
    global_log.time_stamp(clock.elapsed_time());
    global_log.log("OS: removing " + proc_name);
  }
}

//Handles any operation with M code
inline void Simulator :: M_op(Operation current, std::string proc_name)
{
  if(current.tag == ALLOCATE) {
    global_log.time_stamp(clock.elapsed_time());
    global_log.log(proc_name + ": allocating memory");
    std::string mem_loc = int_to_hex(allocate_memory() );
    execute(current);
    global_log.time_stamp(clock.elapsed_time());
    global_log.log(proc_name + ": memory allocated at " + mem_loc);
  }
  else if(current.tag == BLOCK) {
    global_log.time_stamp(clock.elapsed_time());
    global_log.log(proc_name + ": start memory blocking");
    execute(current);
    global_log.time_stamp(clock.elapsed_time());
    global_log.log(proc_name + ": end memory blocking");
  }
}

//Handles any operation with P code
inline void Simulator :: P_op(Operation current, std::string proc_name)
{
  global_log.time_stamp(clock.elapsed_time());
  global_log.log(proc_name + ": start processing action");
  execute(current);
  global_log.time_stamp(clock.elapsed_time());
  global_log.log(proc_name + ": end processing action");
}

//Handles any operation with I/O code
inline void Simulator :: IO_op(Operation current, std::string proc_name)
{
  //Static variables to keep track of current printer and hd
  static int current_printer = 0;
  static int current_hd = 0;

  if(current.code == 'I') {
    //Input Operation

    global_log.time_stamp(clock.elapsed_time());
    if(current.tag == PRINTER) {
      std::string p_num = patch::to_string(current_printer);
      global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " input on PRNTR " + p_num);
      current_printer++;
      if(current_printer == printer_quantity)
	current_printer = 0;
    }
    else if(current.tag == HARD_DRIVE) {
      std::string hd_num = patch::to_string(current_hd);
      global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " input on HDD " + hd_num);
      current_hd++;
      if(current_hd == hd_quantity)
	current_hd = 0;
    }
    else {
       global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " input");
    }
    //Threading
    Thread data(current.cycles, descriptor_to_cycles(current.tag));
    pthread_t t1;
    pthread_create(&t1, NULL, &execute_thread, &data);
    pthread_join(t1, NULL);
    global_log.time_stamp(clock.elapsed_time());
    global_log.log(proc_name + ": end " + descriptor_to_str(current.tag) + " input");
  }
  else {
    //Output Operation

    global_log.time_stamp(clock.elapsed_time());
    if(current.tag == PRINTER) {
      std::string p_num = patch::to_string(current_printer);
      global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " output on PRNTR " + p_num);
      current_printer++;
      if(current_printer == printer_quantity)
	current_printer = 0;
    }
    else if(current.tag == HARD_DRIVE) {
      std::string hd_num = patch::to_string(current_hd);
      global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " output on HDD " + hd_num);
      current_hd++;
      if(current_hd == hd_quantity)
	current_hd = 0;
    }
    else {
	global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " output");
    }
    //Threading
    Thread data(current.cycles, descriptor_to_cycles(current.tag));
    pthread_t t1;
    pthread_create(&t1, NULL, &execute_thread, &data);
    pthread_join(t1, NULL);
    global_log.time_stamp(clock.elapsed_time());
    global_log.log(proc_name + ": end " + descriptor_to_str(current.tag) + " output");
  }
}


//Returns a memory address corresponding to the start of a block
unsigned int Simulator::allocate_memory()
{
  static unsigned int address = 0;
  unsigned int current = address;

  if(address + block_size > system_memory) {
    address = 0;
  }
  else {
    address = address + block_size;
  }

  return current;
}


/* 
***************************************************************HELPER FUNCTIONS***************************************************************
*/

//Checks if a given file contains a certain file extension
bool Simulator::check_extension(const std::string& str, const std::string& ext)
{
  int period = str.find_last_of(".");
  std::string ext_name = str.substr(period);
  if(ext_name == ext) {
      return true;
  }
  else {
    return false;
  } 
}

//Checks if a character is one of the specified meta data codes
bool Simulator::is_code(char c)
{
   if((c == 'S') || (c == 'A') || (c == 'P') || (c == 'I') || (c == 'O') || (c == 'M')) {
     return true;
   }
   else {
     return false;
   }
}

//Checks if a character represents a digit
bool Simulator::is_digit(char c)
{
  if((c == '0') || (c == '1') || (c == '2') || (c == '3') || (c == '4') || (c == '5')  || (c == '6')  || (c == '7') || (c == '8') || (c == '9') ) {
    return true;
  }
  else {
    return false;
  }
}

//Checks if a string matches any of the possible meta data descriptor tags
bool Simulator::is_descriptor(const std::string str)
{
  if((str == "end") || (str == "harddrive") || (str == "keyboard") || (str == "printer") || (str == "monitor") || (str == "block") ||
     (str == "run") || (str == "start") || (str == "allocate") || (str == "mouse") || (str == "speaker")) {
    return true;
  }
  else{
    return false;
  }
}

//Removes all whitespace from a string
void Simulator::remove_whitespace(std::string &str)
{
  std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
  str.erase(end_pos, str.end());
}

//Converts a string to all lowercase letters
void Simulator::to_lower(std::string& str)
{ 
  std::transform(str.begin(), str.end(), str.begin(), :: tolower);
}

//Takes a descriptor tag and returns the cycle time associated with that tag
int Simulator::descriptor_to_cycles(descriptor tag)
{
 switch(tag) {
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

//Takes a descriptor tag and returns a corresponding string
std::string Simulator::descriptor_to_str(descriptor tag)
{
 std::string result;

  switch(tag) {
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

//Takes an integer value and returns the corresponding hexadecimal string
std::string Simulator:: int_to_hex(int i)
{
  std::stringstream stream;
  stream << "0x" 
         << std::setfill ('0') << std::setw(sizeof(i)*2) 
         << std::hex << i;
  return stream.str();
}

//Builds an returns an operation struct from a string
Operation Simulator::extract_operation(const std::string& str)
{
  std::string desc_str;
  std::string cycle_str;
  descriptor tag;

  char code = str[0];
  int cycles;
  int tag_start;
  int tag_end;

  //If is_code returns false then given code is invalid
  if(is_code(code) == false) {
    throw std::invalid_argument("Error: Invalid metadata code value");
  }

  //Getting descriptor tag from string
  for(int i = 0; i < str.length(); i++) {
	if(str[i] == '(') {
	  tag_start = i + 1;
	}
	else if(str[i] == ')') {
	  tag_end = i;	 
	}
  }
  desc_str = str.substr(tag_start, tag_end - tag_start);

  if(is_descriptor(desc_str) == false) {
    throw std::invalid_argument("Error: Invalid metadata descriptor tag");
  }
  else {
    if(desc_str == "harddrive") {
      tag = HARD_DRIVE;
    }
    else if(desc_str == "keyboard"){
      tag = KEYBOARD;
    }
    else if(desc_str == "printer"){
      tag = PRINTER;
    }
    else if(desc_str == "monitor") {
      tag = MONITOR;
    }
    else if(desc_str == "allocate") {
      tag = ALLOCATE;
    }
    else if(desc_str == "mouse") {
      tag = MOUSE;
    }
    else if(desc_str == "speaker") {
      tag = SPEAKER;
    }
    else if(desc_str == "run") {
      tag = RUN;
    }
    else if(desc_str == "start") {
      tag = START;
    }
    else if(desc_str == "end") {
      tag = END;
    }
    else if(desc_str == "block") {
      tag = BLOCK;
    }
  }
 
  //Getting number of cycles from string, throwing error if missing
  if(tag_end == str.length() - 1) {
    throw std::invalid_argument("Error: Missing or negative cycle value");
  }
  else {
    cycle_str = str.substr(tag_end + 1);
  }

  //Getting int from cycles string
  cycles = std::atoi(cycle_str.c_str());

  //returning data in struct
  Operation data(code, cycles, tag);
  return data;
}



 
