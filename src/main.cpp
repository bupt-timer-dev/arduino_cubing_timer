#include "consts.h"
#include "states.h"
#include "utils.h"
#include <Arduino.h>
#include <Button.h>
#include <Display.h>
#include <LiquidCrystal_I2C.h>
#include <Menu.h>

MenuUI menu;
Display display(menu, LCD_ADDRESS, LCD_WIDTH, LCD_HIGHT);
Button left_touch(LEFT_TOUCH), right_touch(RIGHT_TOUCH), reset(RESET);

void setup() {
  putd(POWER, HIGH);
  display.init();
  display.show(menu);
}

void loop() {
  left_touch.check();
  right_touch.check();
  reset.check();
  display.refresh();
}