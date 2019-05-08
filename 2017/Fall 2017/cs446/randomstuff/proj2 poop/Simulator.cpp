#include "Simulator.h"

//Parameterized constructor
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
	  hard_drive = time;	 
	  err_count++;
	}
	else if(config_token.find("printer") != std::string::npos) {
	  printer = time;
	  err_count++;
	}
	else if(config_token.find("keyboard") != std::string::npos) {
	  keyboard = time;
	  err_count++;
	}
	else if(config_token.find("memory") != std::string::npos) {
	  memory = time;
	  err_count++;
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
  int proc_num = process_queue.size() + 1;
  Process new_proc(operation_queue, proc_num, processor, monitor, hard_drive, printer, keyboard, memory, mouse, speaker);
  process_queue.push(new_proc);
}

//Runs simulation
void Simulator::simulate()
{
  while( !process_queue.empty() ) {
    Process current = process_queue.front();
    current.run();
    process_queue.pop();
  }
}


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


