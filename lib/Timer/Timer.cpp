#include "Timer.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <utils.h>

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

void TimerUI::touchHandler() {
  int left_state = devices::left_touch.getState();
  int right_state = devices::right_touch.getState();
  if (left_state != right_state) { return; }
  if (left_state == HIGH) {
    putd(LED, HIGH);
    touchPressed = millis();
  }
  if (left_state == LOW) {
    putd(LED, LOW);
    if (touchPressed && millis() - touchPressed >= START_THRESHOLD) { t.start(); }
    touchPressed = 0;
  }
}

void TimerUI::resetHandler() {
  int state = devices::reset.getState();
  if (state == HIGH) { resetPressed = millis(); }
  if (state == LOW) {
    if (touchPressed && millis() - touchPressed < EXIT_THRESHOLD) { t.reset(); }
    if (touchPressed && millis() - touchPressed >= EXIT_THRESHOLD) { exit(); }
  }
}

void TimerUI::resetHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->resetHandler();
}

void TimerUI::touchHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->touchHandler();
}

void TimerUI::init(Display* _dis, UIProvider* _parent_ui) {
  dis = _dis;
  parent_ui = _parent_ui;
  String time = t.toString();
  dis->lcd.setCursor(0, 0);
  dis->lcd.print("Timer");
  dis->lcd.setCursor(LCD_HEIGHT - 1, LCD_WIDTH - 1 - time.length());
  dis->lcd.print(time);
  devices::reset.attachEvent(CHANGE, resetHandlerIntf, &t);
  devices::left_touch.attachEvent(CHANGE, touchHandlerIntf, this);
  devices::right_touch.attachEvent(CHANGE, touchHandlerIntf, this);
}

void TimerUI::refresh() {
  String time = t.toString();
  dis->lcd.setCursor(LCD_HEIGHT - 1, LCD_WIDTH - 1 - time.length());
  dis->lcd.print(time);
}

void TimerUI::exit() {
  dis->show(*parent_ui);
}