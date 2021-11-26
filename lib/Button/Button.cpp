#include "Button.h"
#include "consts.h"
#include "utils.h"
#include <Arduino.h>

Button::Button() {
  //
}

Button::Button(int _pin) {
  pinMode(_pin, INPUT);
  this->pin = _pin;
}

void Button::attach(int _pin) {
  pinMode(_pin, INPUT);
  this->pin = _pin;
  state = getd(_pin);
}

void Button::attachEvent(int MODE, void (*_event)(void)) {
  this->attached[MODE] = true;
  this->events[MODE] = _event;
}

void Button::check() {
  int _state = getd(this->pin), event;
  if (_state != state) {
    delay(20);
    if (_state != state) {
      attachEvent(CHANGE, *events);
      MODE = state == HIGH ? FALLING : RISING;
    }
  } else if (_state == state) {
    delay(20);
    MODE = state == HIGH ? ONHIGH : ONLOW;
  }

  if (_state != state) {
    state = _state;
  }
  (*events[MODE])();
}