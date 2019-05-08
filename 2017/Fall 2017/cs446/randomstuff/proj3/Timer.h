/**
   Timer Class - Handles time stamping for simulator

**/

#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>
#include <iostream>


class Timer {
 public:
  Timer();
  ~Timer();

  void start();
  long double elapsed_time();
  long double elapsed_milli();
  
 private:
  struct timeval time;
  double long start_time;
};

#endif
