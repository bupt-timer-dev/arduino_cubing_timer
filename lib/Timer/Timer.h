#ifndef __TIMER_TIMER__
#define __TIMER_TIMER__

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000
#define TRIGGER_THRESHOLD (1 * SECOND_MS)
#define EXIT_THRESHOLD (5 * SECOND_MS)

#include <Arduino.h>

class Timer {
  unsigned long begin, time;
  bool timing;

  public:
  unsigned long getTime();
  void reset();
  void start();
  unsigned long stop();
  bool isTiming();
  String toString();
};

#endif