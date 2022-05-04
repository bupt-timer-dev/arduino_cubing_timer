#ifndef __TIMER_TIMER_UI__
#define __TIMER_TIMER_UI__

#include <Display.h>
#include <MenuProvider.h>
#include <Timer.h>

class TimerUI : public MenuProvider {
  Timer* t;
  Display* dis;
  UIProvider* parent_ui;
  unsigned long touch_pressed, reset_pressed;
  bool do_refresh;

  public:
  TimerUI() {
    title = "Timer";
    t = new Timer();
  }
  TimerUI(Timer* _t) {
    title = "Timer";
    t = _t;
  }

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