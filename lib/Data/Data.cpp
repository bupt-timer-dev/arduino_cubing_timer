#include "Data.h"
#include <Arduino.h>

const unsigned long Data::operator[](const int idx) {
  byte b = (*eep)[eep_addr + idx * 4];
}

unsigned long Data::save(unsigned long d) { }

void Data::load() { }