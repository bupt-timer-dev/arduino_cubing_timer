#include <Arduino.h>
#include <Power.h>
#include <utils.h>

Shutdown* Shutdown::instance = NULL;

void Shutdown::init(Display* dis, UIProvider*) {
  dis->lcd.clear();
  putd(POWER, LOW);
}

void Shutdown::refresh() { }

void Shutdown::exit() { }