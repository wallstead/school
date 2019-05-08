#include "Simulator.h"

//Default constructor - not used
Simulator::Simulator()
{
}

//Parameterized constructor
Simulator::Simulator(std::string config)
{
  config_file = config;

  //Parse config file
  if(parse_config(config_file)) {
    //Parse meta data file
    if(parse_metadata(meta_file)) {
      //Run simulation if both parsing functions return true
      simulate();
    }
    else {
      std::cout << "meta data error" << std::endl;
    }
  }
  else {
    std::cout << "error parsing config file" << std::endl;
  }
}

//Destructor
Simulator::~Simulator() {}

//Parses through configuration file and sets up object to run simulation
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
	else if(config_token.find("processor") != std::string::npos) {
	  this->add_data("Processor", token_val);
	}
	else if(config_token.find("monitor") != std::string::npos) {
	  this->add_data("Monitor", token_val);
	}
	else if((config_token.find("hard") != std::string::npos) && (config_token.find("drive") != std::string::npos)) {
	  this->add_data("Hard Drive", token_val);
	}
	else if(config_token.find("printer") != std::string::npos) {
	  this->add_data("Printer", token_val);
	}
	else if(config_token.find("keyboard") != std::string::npos) {
	  this->add_data("Keyboard", token_val);
	}
	else if(config_token.find("memory") != std::string::npos) {
	  this->add_data("Memory", token_val);
	}
	else if(config_token.find("mouse") != std::string::npos) {
	  this->add_data("Mouse", token_val);
	}
	else if(config_token.find("speaker") != std::string::npos) {
	  this->add_data("Speaker", token_val);
	}
      } 
  }  

  //Checking if config file had all information needed
  if(sim_data.size() < 8) {
    throw std::invalid_argument("Error: missing configuration data - expected data for 8 components");
  }
  
  //closing file and return true
  config_file.close();
  return true;
}

//Parses through meta data file and extracts relevant information
bool Simulator::parse_metadata(const std::string& file)
{
  //Checking for valid file extension
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

void Simulator::simulate()
{
  std::string descriptor;
  std::string current;
  int time;
  std::ofstream log(log_file.c_str());

  //Printing configuration data to file, if needed
  if(print_to_file) {
    log << "Configuration File Data" << std::endl;

    for(std::vector<Component>::const_iterator index = sim_data.begin(); index != sim_data.end(); ++index) {
      log << index->type << " = " << index->cycle_time << " ms/cycle" << std::endl;
    }

    if(print_to_screen) {
      log << "Logged to: monitor and " << log_file << std::endl;
    }
    else {
      log << "Logged to: " << log_file << std::endl;
    }

    log << std::endl << "Metadata Metrics:" << std::endl;
  }
  
  //Printing configuration data to screen, if needed
  if(print_to_screen) {
    std::cout << "Configuration File Data" << std::endl;
    for (std::vector<Component>::const_iterator index = sim_data.begin(); index != sim_data.end(); ++index) {
      std::cout << index->type << " = " << index->cycle_time << " ms/cycle" << std::endl;
    }

    if(print_to_file) {
      std::cout << "Logged to: monitor and " << log_file << std::endl;
    }
    else {
      std::cout << "Logged to: monitor" << std::endl;
    }
    std::cout << std::endl << "Metadata Metrics:" << std::endl;
  }

  //Looping through queue
  while(!meta_data.empty()) {
    //Check each entry for errors - if error_check does not throw excpetion then returned Meta struct contains valid metadata info
    current = meta_data.front();
    Meta data = error_check(current);
    descriptor = data.descriptor;

    //Getting appropriate cycle time and calculating cycle time * # of cycles
    if(descriptor == "harddrive") {
      time = get_cycletime("Hard Drive") * data.cycles;
    }
    else if(descriptor == "keyboard"){
      time = get_cycletime("Keyboard") * data.cycles;

    }
    else if(descriptor == "printer"){
      time = get_cycletime("Printer") * data.cycles;

    }
    else if(descriptor == "monitor") {
      time = get_cycletime("Monitor") * data.cycles;

    }
    else if(descriptor == "allocate" || descriptor == "block") {
      time = get_cycletime("Memory") * data.cycles;

    }
    else if(descriptor == "mouse") {
      time = get_cycletime("Mouse") * data.cycles;

    }
    else if(descriptor == "speaker") {
      time = get_cycletime("Speaker") * data.cycles;

    }
    else if(descriptor == "run") {
      time = get_cycletime("Processor") * data.cycles;
    }
    
    //If instruction code is NOT A/S, then it will be printed to log / file as specified by config file
    if((data.code != 'A') && (data.code != 'S')) {
      
      if(print_to_screen && print_to_file) {
	  std::cout << current << " - ";
	  std::cout << time << " ms" << std::endl;

	  log << current << " - ";
	  log << time << " ms" << std::endl;
      }
      else if(print_to_screen && !print_to_file) {
	  std::cout << current << " - ";
	  std::cout << time << " ms" << std::endl;
      }
      else if(!print_to_screen && print_to_file) {
	log << current << " - ";
	log << time << " ms" << std::endl;
      }
    }

    //Pop current instruction from queue
    meta_data.pop();

  }

  //close log file
  log.close();
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

Meta Simulator::error_check(const std::string& str)
{
  std::string descriptor;
  std::string cycle_str;
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

  //Getting descriptor string and checking if it is valid
  descriptor = str.substr(tag_start, tag_end - tag_start);
  if(is_descriptor(descriptor) == false) {
    throw std::invalid_argument("Error: Invalid metadata descriptor tag");
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
  Meta data(code, cycles, descriptor);
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

//Creates a component struct and adds it to sim_data vector
void Simulator::add_data(const std::string comp, const std::string cycle_str)
{
  int time = std::atoi(cycle_str.c_str());
  Component comp_info(comp, time);
  sim_data.push_back(comp_info);
}

//Converts a string to all lowercase letters
void Simulator::to_lower(std::string& str)
{ 
  std::transform(str.begin(), str.end(), str.begin(), :: tolower);
}


//Returns the cycle time of a specified component
int Simulator::get_cycletime(std::string str)
{
  for(int i = 0; i < sim_data.size(); i++) {
    if(sim_data[i].type == str) {
      return sim_data[i].cycle_time;
    }
  }
}
