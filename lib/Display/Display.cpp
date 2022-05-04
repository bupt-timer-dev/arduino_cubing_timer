#include "Display.h"
#include <Arduino.h>

void Display::init(UIProvider* _ui) {
  ui = _ui;
  lcd.init();
  lcd.backlight();
  ui->init(this, ui);
}

void Display::show(UIProvider* _ui) {
  UIProvider* parentUI = ui;
  ui = _ui;
  ui->init(this, parentUI);
}

void Display::refresh() {
  ui->refresh();
}