#include "Timer.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

unsigned long Timer::getTime() {
  return millis() - begin;
}

void Timer::reset() {
  timing = false;
  begin = 0;
}

void Timer::start() {
  this->reset();
  timing = true;
  begin = millis();
}

unsigned long Timer::stop() {
  timing = false;
  return this->getTime();
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
  result = (hour >= 10 ? "" : "0") + String(hour) + ":"
      + (minute >= 10 ? "" : "0") + String(minute) + ":"
      + (second >= 10 ? "" : "0") + String(second) + ":"
      + (duration % SECOND_MS >= 100 ? "" : "0") + (duration % SECOND_MS >= 10 ? "" : "0") + String(duration % SECOND_MS);
  return result;
}

void TimerUI::init(const LiquidCrystal_I2C& dis) {
  reset->attachEvent(FALLING, this->t.reset);
}

void TimerUI::refresh(const LiquidCrystal_I2C& dis) {
}