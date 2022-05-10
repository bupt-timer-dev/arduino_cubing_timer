#include "TimerUI.h"
#include <Arduino.h>
#include <BLE.h>
#include <Devices.h>
#include <MenuProvider.h>
#include <Timer.h>
#include <utils.h>

void TimerUI::startHandler() {
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
      if (!t->isTiming() && millis() - touchTime >= TRIGGER_THRESHOLD) {
        t->start();
        if (TimerBLEServer::BLEConnected) { TimerBLEServer::setTiming(1); }
      }
    }
    touchPressed = false;
  }
}

void TimerUI::stopHandler() {
  if (t->isTiming()) {
    unsigned long tmp = t->getTime();
    t->stop();
    // devices::timingData.save(tmp);
    if (TimerBLEServer::BLEConnected) {
      TimerBLEServer::setTiming(0);
      TimerBLEServer::setTime(tmp);
    }
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

void TimerUI::startHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->startHandler();
}

void TimerUI::stopHandlerIntf(void* _obj) {
  TimerUI* obj = (TimerUI*)_obj;
  obj->stopHandler();
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
  devices::leftTouch.attachEvent(CHANGE, startHandlerIntf, this);
  devices::rightTouch.attachEvent(CHANGE, startHandlerIntf, this);
  devices::leftTouch.attachEvent(RISING, stopHandlerIntf, this);
  devices::rightTouch.attachEvent(RISING, stopHandlerIntf, this);
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