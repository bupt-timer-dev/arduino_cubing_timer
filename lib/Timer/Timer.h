#ifndef __TIMER_TIMER__
#define __TIMER_TIMER__

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000

#include <Arduino.h>
#include <Devices.h>
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
  Timer t;
  Display* dis;
  UIProvider* parent_ui;

  public:
  void eventHandler();
  static void resetIntf(void*);
  static void eventHandlerIntf(void*);
  void init(Display* _dis, UIProvider* _parent_ui);
  void refresh();
  void exit();
};

#endif