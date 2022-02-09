#ifndef __TIMER_MEMORY__
#define __TIMER_MEMORY__

#include "Preservable.h"
#include <Arduino.h>

class Memory {
  int addr, len;

  public:
  Memory() = default;
  Memory(int _addr)
      : addr(_addr) {};
  Memory(int _begin, int _end)
      : addr(_begin)
      , len(_end - _begin) {};

  Preservable operator[](int);

  int length() const { return len; }
  void erase(int);
  int append(const Preservable&);
  Preservable* toArray() const;
  int begin();
  int end();
};

#endif