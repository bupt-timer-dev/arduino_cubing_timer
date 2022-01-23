#include "Timer.h"
#include <Arduino.h>
#include <Devices.h>
#include <LiquidCrystal_I2C.h>
#include <utils.h>

unsigned long Timer::getTime() {
  return isTiming() ? millis() - begin : 0;
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
  if (!touch_pressed) {
    if (left_state != right_state) { return; }
    if (left_state == HIGH) { touch_pressed = millis(); }
  } else {
    if ((left_state == LOW || right_state == LOW) && millis() - touch_pressed >= TRIGGER_THRESHOLD) {
      if (t.isTiming()) {
        touch_pressed = 0;
        t.stop();
      } else {
        touch_pressed = 0;
        t.start();
      }
    }
  }
}

void TimerUI::resetHandler() {
  int state = devices::reset.getState();
  if (state == HIGH) {
    putd(LED, HIGH);
    reset_pressed = millis();
  }
  if (state == LOW) {
    if (t.isTiming()) { return; }
    if (reset_pressed && millis() - reset_pressed >= TRIGGER_THRESHOLD && millis() - reset_pressed < EXIT_THRESHOLD) {
      putd(LED, LOW);
      reset_pressed = 0;
      t.reset();
    }
    if (reset_pressed && millis() - reset_pressed >= EXIT_THRESHOLD) {
      putd(LED, LOW);
      reset_pressed = 0;
      exit();
    }
  }
}

void TimerUI::touchHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->touchHandler();
}

void TimerUI::resetHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->resetHandler();
}

void TimerUI::init(Display* _dis, UIProvider* _parent_ui) {
  dis = _dis;
  parent_ui = _parent_ui;
  String time = t.toString();
  dis->lcd.setCursor(0, 0);
  dis->lcd.print("Timer");
  dis->lcd.setCursor(LCD_HEIGHT - 1, LCD_WIDTH - 1 - time.length());
  dis->lcd.print(time);
  devices::reset.attachEvent(CHANGE, resetHandlerIntf, this);
  devices::left_touch.attachEvent(CHANGE, touchHandlerIntf, this);
  devices::right_touch.attachEvent(CHANGE, touchHandlerIntf, this);
}

void TimerUI::refresh() {
  if (t.isTiming()) {
    String time = t.toString();
    dis->lcd.setCursor(LCD_HEIGHT - 1, LCD_WIDTH - 1 - time.length());
    dis->lcd.print(time);
  }
}

void TimerUI::exit() {
  dis->show(*parent_ui);
}