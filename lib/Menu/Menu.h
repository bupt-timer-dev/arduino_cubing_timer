#ifndef __TIMER_MENU__
#define __TIMER_MENU__

#include "MenuProvider.h"
#include <Display.h>

class MenuUI : public UIProvider {
  Display* dis;
  UIProvider* parent_ui;
  MenuProvider* selections[50];
  int selection_count, now;
  bool do_refresh;

  static void enterIntf(void*);
  static void previousIntf(void*);
  static void nextIntf(void*);
  void enter();
  void previous();
  void next();

  void init(Display*, UIProvider*);
  void refresh();
  void exit();

  public:
  void attachSelection(MenuProvider*);
};

#endif