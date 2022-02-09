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


//负责计时
class Timer {
  unsigned long begin;
  bool timing;

  public:
  unsigned long getTime();
  void reset();
  void start();
  unsigned long stop();
  bool isTiming();
  String toString();//时间转显示字符串
};

//显示界面，处理怎么显示和按钮
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
  static void resetHandlerIntf(void*);//按下的时候对应的动作
  static void touchHandlerIntf(void*);

  void init(Display*, UIProvider*);
  void refresh();
  void exit();
};

#endif