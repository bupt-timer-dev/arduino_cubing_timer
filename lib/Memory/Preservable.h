#ifndef __TIMER_PRESERVABLE__
#define __TIMER_PRESERVABLE__

#include <Arduino.h>

class Preservable {
  public:
  virtual void parse(byte*, int) = 0;
  virtual byte* toBytes() const = 0;
  virtual int lengthAsBytes() const = 0;
};

#endif