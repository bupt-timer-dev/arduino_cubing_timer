#include "Button.h"
#include <Arduino.h>
#include <Tools.h>

Button::Button() {
  //
}

Button::Button(int _pin) {
  pinMode(_pin, INPUT);
  pin = _pin;
}

void Button::attach(int _pin) {
  pinMode(_pin, INPUT);
  pin = _pin;
  state = getd(_pin);
}

void Button::attachEvent(int MODE, void (*_event)(void*), void* _obj = 0) {
  attached[MODE] = true;
  events[MODE] = _event;
  objs[MODE] = _obj;
}

void Button::deattachEvent(int MODE) {
  attached[MODE] = false;
}

void Button::check() {
  int _state = getd(pin), event = 0;
  if (_state != state) {
    event = state == HIGH ? FALLING : RISING;
    state = _state;
    if (attached[CHANGE]) { (*events[CHANGE])(objs[CHANGE]); }
  } else {
    event = state == HIGH ? ONHIGH : ONLOW;
  }
  if (attached[event]) { (*events[event])(objs[event]); }
}

int Button::getState() {
  return state;
}