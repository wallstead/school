#include "Process.h"

//Parameterized Constructor
Process::Process(std::queue<Operation> op_data, int p_num, int proc, int mon, int hd, int prnt, int key, int mem, int ms, int spk)
{
  operations = op_data;
  processor = proc;
  monitor = mon;
  hard_drive = hd;
  printer = prnt;
  keyboard = key;
  memory = mem;
  mouse = ms;
  speaker = spk;
  proc_num = p_num;
  proc_state = NEW;
}

//Destructor
Process::~Process()
{

}

//Executes all operations for the process
void Process::run()
{
  Timer clock;
  std::string num =  patch::to_string(proc_num);
  std::string proc_name = "Process " + num;
  clock.start();


  while( !operations.empty() ) {
    Operation current = operations.front();

    //If S code
    if(current.code == 'S') {
      if(current.tag == START) {
	global_log.time_stamp(clock.elapsed_time());
	global_log.log("Simulator program starting");
      }
      else {
	global_log.time_stamp(clock.elapsed_time());
	global_log.log("Simulator program ending");
      }
    }

    //If A code
    if(current.code == 'A') {
      if(current.tag == START) {
	global_log.time_stamp(clock.elapsed_time());
	global_log.log("OS: preparing " + proc_name);
	global_log.time_stamp(clock.elapsed_time());
	global_log.log("OS: starting process " + proc_name);
	proc_state = READY;
      }
      else {
	global_log.time_stamp(clock.elapsed_time());
	global_log.log("OS: removing " + proc_name);
	proc_state = EXIT;
      }
    }

    //If P code
    if(current.code == 'P') {
      global_log.time_stamp(clock.elapsed_time());
      	global_log.log(proc_name + ": start processing action");
	proc_state = WAITING;
	execute(current);
	global_log.time_stamp(clock.elapsed_time());
      	global_log.log(proc_name + ": end processing action");
	proc_state = READY;
    }

    //If M code
    if(current.code == 'M') {
      if(current.tag == ALLOCATE) {
	global_log.time_stamp(clock.elapsed_time());
  	global_log.log(proc_name + ": allocating memory");
	std::string mem_loc = patch::to_string( allocate_memory(100000) );
	proc_state = WAITING;
	execute(current);
	global_log.time_stamp(clock.elapsed_time());
	global_log.log(proc_name + ": memory allocated at 0x" + mem_loc);
	proc_state = READY;
      }
      else if(current.tag == BLOCK) {
	global_log.time_stamp(clock.elapsed_time());
	global_log.log(proc_name + ": start memory blocking");
	proc_state = WAITING;
	execute(current);
	global_log.time_stamp(clock.elapsed_time());
	global_log.log(proc_name + ": end memory blocking");
	proc_state = READY;
							  
      }
    }


    //If I code - threading done here
    if(current.code == 'I') {
      global_log.time_stamp(clock.elapsed_time());
      global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " input");
      proc_state = WAITING;
      //Threading
      Thread data(current.cycles, descriptor_to_cycles(current.tag));
      pthread_t t1;
      pthread_create(&t1, NULL, &execute_thread, &data);

      pthread_join(t1, NULL);
      global_log.time_stamp(clock.elapsed_time());
      global_log.log(proc_name + ": end " + descriptor_to_str(current.tag) + " input");
      proc_state = READY;
    }

    //If O code - Threading done here
    if(current.code == 'O') {
      global_log.time_stamp(clock.elapsed_time());
      global_log.log(proc_name + ": start " + descriptor_to_str(current.tag) + " output");
      proc_state = WAITING;
      //Threading
      Thread data(current.cycles, descriptor_to_cycles(current.tag));
      pthread_t t1;
      pthread_create(&t1, NULL, &execute_thread, &data);
     
      global_log.time_stamp(clock.elapsed_time());
      global_log.log(proc_name + ": end " + descriptor_to_str(current.tag) + " output");
      proc_state = READY;
    }
        
    operations.pop();
  }
}

//Executes an individual operation
void Process::execute(Operation op)
{
  Timer clock; 
  
  for(int i = 0; i < op.cycles; i++) {
    clock.start();
    while(clock.elapsed_milli() < descriptor_to_cycles(op.tag));
  }

}

//Executes an operation using threads
void* Process::execute_thread(void* p) 
{
  Thread* op = (Thread*) p;
  Timer clock; 
  for(int i = 0; i < op->num_cycles; i++) {
    clock.start();
    while(clock.elapsed_milli() < op->cycle_time);
  }
}

//Gets cycle time for a given descriptor tag
int Process::descriptor_to_cycles(descriptor tag)
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
  
 return 0;
}

//Returns a string for a given descriptor
std::string Process::descriptor_to_str(descriptor tag) 
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

//Allocates memory 
unsigned int Process:: allocate_memory(int totMem)
{
	unsigned int address;
	
	srand(time(NULL));
	
	if( totMem > 0 )
	{
		address = rand() % totMem;
	}
	return address;
}


