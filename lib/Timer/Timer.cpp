#include "Timer.h"
#include <Arduino.h>
#include <Devices.h>
#include <LiquidCrystal_I2C.h>
#include <utils.h>

unsigned long Timer::getTime() {
  return isTiming() ? millis() - begin : 0;
}

unsigned long Timer::getLastTime() {
  return time;
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
  time = millis() - begin;
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

  result = (hour ? (String(hour) + ":") : String())
      + (minute || hour ? ((minute >= 10 || !hour ? "" : "0") + String(minute) + ":") : String())
      + (second >= 10 || (!hour && !minute) ? "" : "0") + String(second) + "."
      + (duration % SECOND_MS >= 100 ? "" : "0") + (duration % SECOND_MS >= 10 ? "" : "0") + String(duration % SECOND_MS);

  return result;
}

void TimerUI::touchHandler() {
  int leftState = devices::leftTouch.getState();
  int rightState = devices::rightTouch.getState();
  if (!touch_pressed) {
    if (leftState != rightState) { return; }
    if (leftState == HIGH) { touch_pressed = millis(); }
  } else {
    if ((leftState == LOW || rightState == LOW)) {
      if (t.isTiming()) {
        touch_pressed = 0;
        t.stop();
        devices::timingData.save(t.getTime());
        devices::ble.setTiming(0);
        devices::ble.setTime(t.getTime());
      } else if (millis() - touch_pressed >= TRIGGER_THRESHOLD) {
        touch_pressed = 0;
        t.start();
        devices::ble.setTiming(1);
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
      do_refresh = true;
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

  do_refresh = false;

  String time = t.toString();
  dis->lcd.clear();
  dis->lcd.setCursor(5, 0);
  dis->lcd.print("Timer");
  dis->lcd.setCursor(LCD_WIDTH - 1 - time.length(), LCD_HEIGHT - 1);
  dis->lcd.print(time);

  devices::reset.attachEvent(CHANGE, resetHandlerIntf, this);
  devices::leftTouch.attachEvent(CHANGE, touchHandlerIntf, this);
  devices::rightTouch.attachEvent(CHANGE, touchHandlerIntf, this);
}

void TimerUI::refresh() {
  if (t.isTiming() || do_refresh) {
    do_refresh = false;
    String time = t.toString();
    dis->lcd.setCursor(LCD_WIDTH - 1 - time.length(), LCD_HEIGHT - 1);
    dis->lcd.print(time);
    if (TimerBLEServer::BLEConnected) { devices::ble.setTime(t.isTiming() ? t.getTime() : 0); }
  }
}

void TimerUI::exit() {
  devices::reset.detachEvent(CHANGE);
  devices::leftTouch.detachEvent(CHANGE);
  devices::rightTouch.detachEvent(CHANGE);
  dis->show(parent_ui);
}