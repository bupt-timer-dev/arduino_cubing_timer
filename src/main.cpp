#include "pins.h"
#include "utils.h"
#include <Arduino.h>
#include <Button.h>
#include <Devices.h>
#include <Display.h>
#include <LiquidCrystal_I2C.h>
#include <Menu.h>

MenuUI menu;
Display display(menu, LCD_ADDRESS, LCD_WIDTH, LCD_HIGHT);
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_WIDTH, LCD_HIGHT);

void setup() {
  putd(POWER, HIGH);
  display.init();
  display.show(menu);
}

void loop() {
  devices::check();
  display.refresh();
}