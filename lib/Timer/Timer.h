#ifndef __TIMER_TIMER__
#define __TIMER_TIMER__

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000
#define TRIGGER_THRESHOLD (2 * SECOND_MS)
#define EXIT_THRESHOLD (5 * SECOND_MS)

#include <Arduino.h>
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
  unsigned long touch_pressed, reset_pressed;

  void touchHandler();
  void resetHandler();
  static void resetHandlerIntf(void*);
  static void touchHandlerIntf(void*);
  void init(Display* _dis, UIProvider* _parent_ui);
  void refresh();
  void exit();
};

#endif