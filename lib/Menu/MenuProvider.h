#ifndef __TIMER_MENU_PROVIDER__
#define __TIMER_MENU_PROVIDER__

#include <Arduino.h>
#include <Display.h>

class MenuProvider : public UIProvider {
  public:
  String title;
};

#endif