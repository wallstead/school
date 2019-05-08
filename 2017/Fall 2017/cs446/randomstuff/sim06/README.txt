Author: Josh Pike
Compiles using 'make' command
Compiles on Virtual Box Ubuntu VM

Included Files:
Sim05.cpp - contains main function
Simulator.h / Simulator.cpp - class to read config/metadata, and run simulation
OutputLog.h / OutputLog.cpp - class that handles logging all data
Timer.h / Timer.cpp - class that handles all timing operations 

Project 5 Specifics:
Process scheduling is handled by 3 functions: FIFO_scheduling, SJF_scheduling, and PS_scheduling. 
Initially, meta data commands are parsed and compiled into individual processes, and stored in a
vector (which is a data member in the simulator class) called process_vector. Then, depending on the
scheduling code provided in the configuration file, the simulate() function will call one the 3 functions
mentioned above. These functions take the processes in process_vector and place them into another
data member called process_queue according to order dictated by that particular scheduling algorithm. Then,
simulate() works through each process in process_queue, so the processes will be run in the correct order. 

Resource management is handled by 3 different functions as well: initialize_resources, allocate_resource, and
deallocate_resource. The initialize_resources function initializes the system_resources data member in the 
simulator class by dynamically allocating an array of mutexes for both printers and hard drives (the size of the
arrays is determined by the specified quanties of each resource in the config file). allocate_resource handles 
mutex locking of a resource being used, while deallocate_resource unlocks a mutex after the resource is no longer
being used. allocate_resource and deallocate_resource are called from the function IO_op. 

Memory allocation is handled by the allocate_memory function.  

