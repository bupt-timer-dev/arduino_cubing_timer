#ifndef __TIMER_DISPLAY__
#define __TIMER_DISPLAY__

#include <LiquidCrystal_I2C.h>

class UIProvider {
  virtual void init(const LiquidCrystal_I2C&) = 0;
  virtual void refresh(const LiquidCrystal_I2C&) = 0;
};

class Display {
  UIProvider& ui;
  LiquidCrystal_I2C lcd;

  public:
  Display(UIProvider& _ui, uint8_t addr, uint8_t width, uint8_t hight)
      : ui(_ui)
      , lcd(addr, width, hight) { }

  void init();
  void show(const UIProvider&);
  void refresh();
};

#endif