#ifndef __TIMER_TIMER_UI__
#define __TIMER_TIMER_UI__

#define HOUR_MS 3600000
#define MINUTE_MS 60000
#define SECOND_MS 1000
#define TRIGGER_THRESHOLD (1 * SECOND_MS)
#define EXIT_THRESHOLD (3 * SECOND_MS)

#include <Display.h>
#include <MenuProvider.h>
#include <Timer.h>

class TimerUI : public MenuProvider {
  Timer* t;
  Display* dis;
  UIProvider* parentUI;
  unsigned long touchTime, resetTime;
  bool touchPressed, resetPressed;

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
  void startHandler();
  void stopHandler();
  void resetHandler();
  static void resetHandlerIntf(void*);
  static void startHandlerIntf(void*);
  static void stopHandlerIntf(void*);

  void save(unsigned long);

  void init(Display*, UIProvider*);
  void refresh();
  void exit();
};

#endif