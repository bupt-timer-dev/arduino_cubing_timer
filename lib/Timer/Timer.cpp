#include "Timer.h"
#include "consts.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

unsigned long Timer::getTime() {
  return millis() - begin;
}

void Timer::reset() {
  timing = false;
  begin = 0;
}

void Timer::start() {
  this->reset();
  timing = true;
  begin = millis();
}

unsigned long Timer::stop() {
  timing = false;
  return getTime();
}

bool Timer::isTiming() {
  return timing;
}

String Timer::toString() {
  unsigned long duration = this->getTime(), hour, minute, second;
  String result;
  hour = duration / HOUR_MS;
  minute = (duration % HOUR_MS) / MINUTE_MS;
  second = (duration % MINUTE_MS) / SECOND_MS;
  result = (hour >= 10 ? "" : "0") + String(hour) + ":"
      + (minute >= 10 ? "" : "0") + String(minute) + ":"
      + (second >= 10 ? "" : "0") + String(second) + ":"
      + (duration % SECOND_MS >= 100 ? "" : "0") + (duration % SECOND_MS >= 10 ? "" : "0") + String(duration % SECOND_MS);
  return result;
}

void TimerUI::eventHandler() {
}

void TimerUI::resetIntf(void* _obj) {
  Timer* obj = (Timer*)_obj;
  obj->reset();
}

void TimerUI::eventHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->eventHandler();
}

void TimerUI::init(Display* _dis, UIProvider* _parent_ui) {
  dis = _dis;
  parent_ui = _parent_ui;
  String time = t.toString();
  dis->lcd.setCursor(0, 0);
  dis->lcd.print("Timer");
  dis->lcd.setCursor(1, LCD_WIDTH - 1 - time.length());
  dis->lcd.print(time);
  devices::reset.attachEvent(FALLING, resetIntf, &t);
  devices::left_touch.attachEvent(CHANGE, eventHandlerIntf, this);
  devices::right_touch.attachEvent(CHANGE, eventHandlerIntf, this);
}

void TimerUI::refresh() {
  String time = t.toString();
  dis->lcd.setCursor(1, LCD_WIDTH - 1 - time.length());
  dis->lcd.print(time);
}

void TimerUI::exit() {
  dis->show(*parent_ui);
}