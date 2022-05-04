#include "MenuUI.h"
#include <Arduino.h>
#include <Devices.h>

void MenuUI::enter() {
  if (selectionCount) {
    devices::reset.detachEvent(FALLING);
    devices::leftTouch.detachEvent(FALLING);
    devices::rightTouch.detachEvent(FALLING);
    dis->show(selections[now]);
  }
}

void MenuUI::previous() {
  if (selectionCount) {
    now = (now - 1 + selectionCount) % selectionCount;
    doRefresh = true;
  }
}

void MenuUI::next() {
  if (selectionCount) {
    now = (now + 1) % selectionCount;
    doRefresh = true;
  }
}

void MenuUI::enterIntf(void* _obj) {
  MenuUI* obj = (MenuUI*)_obj;
  obj->enter();
}

void MenuUI::previousIntf(void* _obj) {
  MenuUI* obj = (MenuUI*)_obj;
  obj->previous();
}

void MenuUI::nextIntf(void* _obj) {
  MenuUI* obj = (MenuUI*)_obj;
  obj->next();
}

void MenuUI::init(Display* _dis, UIProvider* _parentUI) {
  dis = _dis;
  parentUI = _parentUI;
  now = 0;
  doRefresh = false;

  dis->lcd.clear();
  dis->lcd.setCursor(6, 0);
  dis->lcd.print("Menu");
  dis->lcd.setCursor(0, LCD_HEIGHT - 1);
  if (selectionCount) {
    dis->lcd.print("<");
    dis->lcd.setCursor((LCD_WIDTH - selections[now]->title.length()) / 2, LCD_HEIGHT - 1);
    dis->lcd.print(selections[now]->title); // TODO Use scrolling words to display long titles
    dis->lcd.setCursor(LCD_WIDTH - 1, LCD_HEIGHT - 1);
    dis->lcd.print(">");
  } else {
    dis->lcd.print("No selection");
  }

  devices::reset.attachEvent(FALLING, enterIntf, this);
  devices::leftTouch.attachEvent(FALLING, previousIntf, this);
  devices::rightTouch.attachEvent(FALLING, nextIntf, this);
}

void MenuUI::refresh() {
  if (doRefresh) {
    doRefresh = false;
    dis->lcd.clear();
    dis->lcd.setCursor(6, 0);
    dis->lcd.print("Menu");
    dis->lcd.setCursor(0, LCD_HEIGHT - 1);
    if (selectionCount) {
      dis->lcd.print("<");
      dis->lcd.setCursor((LCD_WIDTH - selections[now]->title.length()) / 2, LCD_HEIGHT - 1);
      dis->lcd.print(selections[now]->title); // TODO Use scrolling words to display long titles
      dis->lcd.setCursor(LCD_WIDTH - 1, LCD_HEIGHT - 1);
      dis->lcd.print(">");
    } else {
      dis->lcd.print("No selection");
    }
  }
}

void MenuUI::exit() {
  devices::reset.detachEvent(FALLING);
  devices::leftTouch.detachEvent(FALLING);
  devices::rightTouch.detachEvent(FALLING);
  dis->show(parentUI);
}

void MenuUI::attachSelection(MenuProvider* _selection) {
  selections[selectionCount++] = _selection;
}