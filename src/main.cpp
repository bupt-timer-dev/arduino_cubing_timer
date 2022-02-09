#include <Arduino.h>
#include <Devices.h>
#include <Display.h>
#include <LiquidCrystal_I2C.h>
#include <Menu.h>
#include <Power.h>
#include <Timer.h>
#include <utils.h>

MenuUI menu;
TimerUI timer;
Shutdown shutdown;
Display display(&menu, LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  Serial.begin(9600);
  Serial.println();
  putd(POWER, HIGH);
  menu.attachSelection(&timer);
  menu.attachSelection(&shutdown);
  display.init();
}

void loop() {
  devices::check();
  display.refresh();
}