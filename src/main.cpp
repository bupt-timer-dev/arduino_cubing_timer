#include "pins.h"
#include "utils.h"
#include <Arduino.h>
#include <Devices.h>
#include <Display.h>
#include <Menu.h>

MenuUI menu;
Display display(menu, LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  putd(POWER, HIGH);
  display.init();
  display.show(menu);
}

void loop() {
  devices::check();
  display.refresh();
}