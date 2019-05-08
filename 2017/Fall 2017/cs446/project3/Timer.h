#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <sys/time.h>  // using this instead of ctime, let me know if not ok

class Timer {
 public:
  Timer();
  ~Timer();

  void start();
  long double elapsedTime();
  long double elapsedTimeMilliseconds();

 private:
  struct timeval time;
  double long start_time;
};

#endif
