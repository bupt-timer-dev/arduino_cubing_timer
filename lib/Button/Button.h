#ifndef __TIMER_BUTTONS__
#define __TIMER_BUTTONS__

#include <Arduino.h>

#define MODE_SIZE 6

class Button {
  int pin, state, MODE;
  void (*events[MODE_SIZE])();
  bool attached[MODE_SIZE];

  public:
  Button();

  Button(int _pin);

  void attach(int _pin); //attach Buttons object to pin
  void attachEvent(int MODE, void (*_event)()); //attach function to specific event
      //see also: states.h
  void check(); //check pin state
};

#endif