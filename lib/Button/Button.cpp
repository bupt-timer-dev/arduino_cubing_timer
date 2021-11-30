#include "Button.h"
#include <Arduino.h>
#include <Tools.h>

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

void Button::attachEvent(int MODE, void (*_event)(void*), void* _obj = 0) {
  attached[MODE] = true;
  events[MODE] = _event;
  objs[MODE] = _obj;
}

void Button::check() {
  int _state = getd(this->pin), event;
  if (_state != state) {
    delay(20);
    if (_state != state) {
      MODE = state == HIGH ? FALLING : RISING;
    }
  } else if (_state == state) {
    delay(20);
    MODE = state == HIGH ? ONHIGH : ONLOW;
  }

  if (_state != state) {
    state = _state;
  }
  (*events[MODE])(objs[MODE]);
}

int Button::getState() { return state; }