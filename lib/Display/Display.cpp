#include "Display.h"
#include <Arduino.h>

void Display::init() {
}

void Display::show(const UIProvider& _ui) {
  UIProvider* parent_ui = &ui;
  ui = _ui;
  ui.init(this, parent_ui);
}

void Display::refresh() {
  ui.refresh();
}