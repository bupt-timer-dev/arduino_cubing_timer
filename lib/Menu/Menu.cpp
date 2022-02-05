#include "Menu.h"
#include <Arduino.h>
#include <Devices.h>

void MenuUI::enter() {
  Serial.println("MenuUI::enter");
  if (selection_count) {
    devices::reset.deattachEvent(FALLING);
    devices::left_touch.deattachEvent(FALLING);
    devices::right_touch.deattachEvent(FALLING);
    dis->show(selections[now]);
  }
}

void MenuUI::previous() {
  if (selection_count) {
    now = (now - 1 + selection_count) % selection_count;
    do_refresh = true;
  }
}

void MenuUI::next() {
  if (selection_count) {
    now = (now + 1) % selection_count;
    do_refresh = true;
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

void MenuUI::init(Display* _dis, UIProvider* _parent_ui) {
  Serial.println("MenuUI::init");
  dis = _dis;
  parent_ui = _parent_ui;
  now = 0;
  do_refresh = false;

  dis->lcd.clear();
  dis->lcd.setCursor(6, 0);
  dis->lcd.print("Menu");
  dis->lcd.setCursor(0, LCD_HEIGHT - 1);
  if (selection_count) {
    dis->lcd.print("<");
    dis->lcd.setCursor((LCD_WIDTH - selections[now]->title.length()) / 2, LCD_HEIGHT - 1);
    dis->lcd.print(selections[now]->title); // TODO Use scrolling words to display long titles
    dis->lcd.setCursor(LCD_WIDTH - 1, LCD_HEIGHT - 1);
    dis->lcd.print(">");
  } else {
    dis->lcd.print("No selection");
  }

  devices::reset.attachEvent(FALLING, enterIntf, this);
  devices::left_touch.attachEvent(FALLING, previousIntf, this);
  devices::right_touch.attachEvent(FALLING, nextIntf, this);
}

void MenuUI::refresh() {
  if (do_refresh) {
    do_refresh = false;
    dis->lcd.clear();
    dis->lcd.setCursor(6, 0);
    dis->lcd.print("Menu");
    dis->lcd.setCursor(0, LCD_HEIGHT - 1);
    if (selection_count) {
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
  devices::reset.deattachEvent(FALLING);
  devices::left_touch.deattachEvent(FALLING);
  devices::right_touch.deattachEvent(FALLING);
  dis->show(parent_ui);
}

void MenuUI::attachSelection(MenuProvider* _selection) {
  selections[selection_count++] = _selection;
}