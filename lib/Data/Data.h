#ifndef __TIMER_DATA__
#define __TIMER_DATA__

#include <AT24Cxx.h>
#include <Arduino.h>

class Data {
  AT24Cxx* eep;
  unsigned long eep_addr, eep_len, len;

  public:
  Data() = default;
  Data(AT24Cxx* _eep, int eep_start) {
    eep = _eep;
    eep_addr = eep_start;
  }

  const unsigned long operator[](const int);

  unsigned long save(unsigned long);
  void load();
};

#endif