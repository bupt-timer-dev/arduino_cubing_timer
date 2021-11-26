#ifndef __TIMER_TIMER__
#define __TIMER_TIMER__

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000

#include <Arduino.h>
#include <Button.h>
#include <Display.h>

class Timer {
  unsigned long begin;
  bool timing;

  public:
  unsigned long getTime();
  void reset();
  void start();
  unsigned long stop();
  bool isTiming();
  String toString();
};

class TimerUI : public UIProvider {
  Button *left_touch, *right_touch, *reset;
  Timer t;

  public:
  void init(const LiquidCrystal_I2C& dis);
  void refresh(const LiquidCrystal_I2C& dis);
};

#endif