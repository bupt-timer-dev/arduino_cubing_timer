#ifndef __TIMER_DISPLAY__
#define __TIMER_DISPLAY__

#define LCD_ADDRESS 0x3f
#define LCD_WIDTH 16
#define LCD_HIGHT 2

#include <LiquidCrystal_I2C.h>

class UIProvider;

class Display {
  UIProvider& ui;

  public:
  LiquidCrystal_I2C lcd;

  Display(UIProvider& _ui, uint8_t addr, uint8_t width, uint8_t hight)
      : ui(_ui)
      , lcd(addr, width, hight) { }

  void init();
  void show(const UIProvider&);
  void refresh();
};

class UIProvider {
  Display* dis;

  virtual void init(Display*, UIProvider*) = 0;
  virtual void refresh() = 0;
  virtual void exit() = 0;
};

#endif