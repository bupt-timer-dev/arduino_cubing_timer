#ifndef __TIMER_TIMER__
#define __TIMER_TIMER__

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000
#define TRIGGER_THRESHOLD (1 * SECOND_MS)
#define EXIT_THRESHOLD (5 * SECOND_MS)

#include <Arduino.h>
#include <Display.h>
#include <Menu.h>

class Timer {
  unsigned long begin, time;
  bool timing;

  public:
  unsigned long getTime();
  unsigned long getLastTime();
  void reset();
  void start();
  unsigned long stop();
  bool isTiming();
  String toString();
};

class TimerUI : public MenuProvider {
  Timer t;
  Display* dis;
  UIProvider* parent_ui;
  unsigned long touch_pressed, reset_pressed;
  bool do_refresh;

  public:
  TimerUI() { title = "Timer"; }

  private:
  void touchHandler();
  void resetHandler();
  static void resetHandlerIntf(void*);
  static void touchHandlerIntf(void*);

  void save(unsigned long);

  void init(Display*, UIProvider*);
  void refresh();
  void exit();
};

#endif