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
  if (!touchPressed) {
    if (leftState != rightState) { return; }
    if (leftState == HIGH) {
      touchTime = millis();
      touchPressed = true;
    }
  } else {
    if (leftState == LOW || rightState == LOW) {
      if (t->isTiming()) {
        t->stop();
        // devices::timingData.save(t->getTime());
        if (TimerBLEServer::BLEConnected) {
          TimerBLEServer::setTiming(0);
          TimerBLEServer::setTime(t->getTime());
        }
      } else if (millis() - touchTime >= TRIGGER_THRESHOLD) {
        t->start();
        if (TimerBLEServer::BLEConnected) { TimerBLEServer::setTiming(1); }
      }
    }
    touchPressed = false;
  }
}

void TimerUI::resetHandler() {
  int state = devices::reset.getState();
  if (state == HIGH) {
    putd(LED, HIGH);
    resetTime = millis();
    resetPressed = true;
  }
  if (state == LOW) {
    putd(LED, LOW);
    if (t->isTiming()) { return; }
    if (resetPressed) {
      if (millis() - resetTime >= TRIGGER_THRESHOLD && millis() - resetTime < EXIT_THRESHOLD) { t->reset(); }
      if (millis() - resetTime >= EXIT_THRESHOLD) {
        t->reset();
        exit();
      }
      resetPressed = false;
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

void TimerUI::init(Display* _dis, UIProvider* _parentUI) {
  dis = _dis;
  parentUI = _parentUI;

  touchPressed = false;
  resetPressed = false;

  String time = t->toString();
  dis->lcd.clear();
  dis->lcd.setCursor(5, 0);
  dis->lcd.print("Timer");
  dis->lcd.setCursor(LCD_WIDTH - time.length(), LCD_HEIGHT - 1);
  dis->lcd.print(time);

  devices::reset.attachEvent(CHANGE, resetHandlerIntf, this);
  devices::leftTouch.attachEvent(CHANGE, touchHandlerIntf, this);
  devices::rightTouch.attachEvent(CHANGE, touchHandlerIntf, this);
}

void TimerUI::refresh() {
  if (t->refresh) {
    dis->lcd.setCursor(0, LCD_HEIGHT - 1);
    dis->lcd.print("                ");
  }
  if (t->isTiming() || t->refresh) {
    t->refresh = false;
    String time = t->toString();
    dis->lcd.setCursor(LCD_WIDTH - time.length(), LCD_HEIGHT - 1);
    dis->lcd.print(time);
    if (TimerBLEServer::BLEConnected && t->isTiming()) { TimerBLEServer::setTime(t->getTime()); }
  }
}

void TimerUI::exit() {
  devices::reset.detachEvent(CHANGE);
  devices::leftTouch.detachEvent(CHANGE);
  devices::rightTouch.detachEvent(CHANGE);
  dis->show(parentUI);
}