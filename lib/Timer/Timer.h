#ifndef __TIMER_TIMER__
#define __TIMER_TIMER__

#include <Arduino.h>

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000

class Timer {
  unsigned long begin, time;
  bool timing;

  public:
  bool refresh;

  unsigned long getTime();
  unsigned long getLastTime();
  void reset();
  void start();
  unsigned long stop();
  bool isTiming();
  String toString();
};

#endif