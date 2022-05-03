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
Display display(&menu, LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);

void setup() {
  if (getd(POWER) == HIGH) { putd(POWER, HIGH); }
  Serial.begin(9600);
  Serial.println();
  menu.attachSelection(&timer);
  menu.attachSelection(Shutdown::getInstance());
  devices::ble.init("Arduino Cubing Timer");
  display.init();
}

void loop() {
  devices::check();
  display.refresh();
}