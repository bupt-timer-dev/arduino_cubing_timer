#include "Display.h"
#include <Arduino.h>

void Display::init(UIProvider* _ui) {
  ui = _ui;
  lcd.init();
  lcd.backlight();
  ui->init(this, ui);
}

void Display::show(UIProvider* _ui) {
  UIProvider* parent_ui = ui;
  ui = _ui;
  ui->init(this, parent_ui);
}

void Display::refresh() {
  ui->refresh();
}