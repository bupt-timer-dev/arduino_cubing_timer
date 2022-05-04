#include "Timer.h"
#include <Arduino.h>

unsigned long Timer::getTime() {
  return isTiming() ? millis() - begin : 0;
}

unsigned long Timer::getLastTime() {
  return time;
}

void Timer::reset() {
  timing = false;
  begin = 0;
  refresh = true;
}

void Timer::start() {
  this->reset();
  timing = true;
  begin = millis();
}

unsigned long Timer::stop() {
  timing = false;
  time = millis() - begin;
  return getTime();
}

bool Timer::isTiming() {
  return timing;
}

String Timer::toString() {
  unsigned long duration = this->getTime(), hour, minute, second;
  String result;
  hour = duration / HOUR_MS;
  minute = (duration % HOUR_MS) / MINUTE_MS;
  second = (duration % MINUTE_MS) / SECOND_MS;

  result = (hour ? (String(hour) + ":") : String())
      + (minute || hour ? ((minute >= 10 || !hour ? "" : "0") + String(minute) + ":") : String())
      + (second >= 10 || (!hour && !minute) ? "" : "0") + String(second) + "."
      + (duration % SECOND_MS >= 100 ? "" : "0") + (duration % SECOND_MS >= 10 ? "" : "0") + String(duration % SECOND_MS);

  return result;
}