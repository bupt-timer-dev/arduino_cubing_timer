#include "TimerUI.h"
#include <Arduino.h>
#include <BLE.h>
#include <Devices.h>
#include <MenuProvider.h>
#include <Timer.h>
#include <utils.h>

void TimerUI::touchHandler() {
  int leftState = devices::leftTouch.getState();
  int rightState = devices::rightTouch.getState();
  if (!touch_pressed) {
    if (leftState != rightState) { return; }
    if (leftState == HIGH) { touch_pressed = millis(); }
  } else {
    if ((leftState == LOW || rightState == LOW)) {
      if (t->isTiming()) {
        touch_pressed = 0;
        t->stop();
        devices::timingData.save(t->getTime());
        TimerBLEServer::setTiming(0);
        TimerBLEServer::setTime(t->getTime());
      } else if (millis() - touch_pressed >= TRIGGER_THRESHOLD) {
        touch_pressed = 0;
        t->start();
        TimerBLEServer::setTiming(1);
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
    if (t->isTiming()) { return; }
    if (reset_pressed && millis() - reset_pressed >= TRIGGER_THRESHOLD && millis() - reset_pressed < EXIT_THRESHOLD) {
      putd(LED, LOW);
      reset_pressed = 0;
      do_refresh = true;
      t->reset();
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

  String time = t->toString();
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
  if (t->isTiming() || do_refresh) {
    do_refresh = false;
    String time = t->toString();
    dis->lcd.setCursor(LCD_WIDTH - 1 - time.length(), LCD_HEIGHT - 1);
    dis->lcd.print(time);
    if (TimerBLEServer::BLEConnected) { TimerBLEServer::setTime(t->getTime()); }
  }
}

void TimerUI::exit() {
  devices::reset.detachEvent(CHANGE);
  devices::leftTouch.detachEvent(CHANGE);
  devices::rightTouch.detachEvent(CHANGE);
  dis->show(parent_ui);
}