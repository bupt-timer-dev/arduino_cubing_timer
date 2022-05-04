#include "Shutdown.h"
#include <Arduino.h>
#include <utils.h>

Shutdown* Shutdown::instance = NULL;

void Shutdown::init(Display* dis, UIProvider*) {
  dis->lcd.clear();
  putd(POWER, LOW);
}

void Shutdown::refresh() { }

void Shutdown::exit() { }