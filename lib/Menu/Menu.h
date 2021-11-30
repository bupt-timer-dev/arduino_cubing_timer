#ifndef __TIMER_MENU__
#define __TIMER_MENU__

#include <Display.h>

class MenuUI : public UIProvider {
  Display* dis;
  UIProvider* parent_ui;

  public:
  void init(Display* _dis, UIProvider* _parent_ui);
  void refresh();
  void exit();
};

#endif