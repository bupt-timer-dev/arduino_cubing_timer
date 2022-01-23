#include "pins.h"
#include "utils.h"
#include <Arduino.h>
#include <Devices.h>
#include <Display.h>
#include <LiquidCrystal_I2C.h>
#include <Menu.h>
#include <Timer.h>

MenuUI menu;
TimerUI timer;
Display display(timer, LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  Serial.begin(9600);
  putd(POWER, HIGH);
  display.init();
  // display.show(timer);
}

void loop() {
  devices::check();
  display.refresh();
}