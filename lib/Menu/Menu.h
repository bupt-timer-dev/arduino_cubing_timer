#ifndef __TIMER_MENU__
#define __TIMER_MENU__

#include <Display.h>

class MenuUI : public UIProvider {
  public:
  void init(const LiquidCrystal_I2C& dis);
  void refresh(const LiquidCrystal_I2C& dis);
};

#endif