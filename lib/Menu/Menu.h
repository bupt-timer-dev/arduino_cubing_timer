#ifndef __TIMER_MENU__
#define __TIMER_MENU__

#include <Display.h>

class MenuProvider : public UIProvider {
};

class MenuUI : public UIProvider {
  void init(Display* _dis, UIProvider* _parent_ui);
  void refresh();
  void exit();
};

#endif