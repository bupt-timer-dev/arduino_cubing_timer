#include <Arduino.h>
#include <BLE.h>
#include <Devices.h>
#include <Display.h>
#include <MenuUI.h>
#include <Shutdown.h>
#include <TimerUI.h>
#include <utils.h>

MenuUI menu;
TimerUI timer(&devices::t);

void setup() {
  if (getd(POWER) == HIGH) { putd(POWER, HIGH); }
  Serial.begin(9600);
  Serial.println();
  menu.attachSelection(&timer);
  menu.attachSelection(Shutdown::getInstance());
  devices::display.init(&menu);
  TimerBLEServer::init("Arduino Cubing Timer");
}

void loop() {
  devices::check();
  devices::display.refresh();
}