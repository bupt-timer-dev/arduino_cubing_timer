#ifndef __TIMER_BUTTON__
#define __TIMER_BUTTON__

#include <Arduino.h>

#define MODE_SIZE 6

/*
 *Attention: Do not attach both CHANGE and RISING/FALLING events at the same time.
 *           This may cause unexpected behavior.
 */

class Button {
  int pin, state, MODE;
  void (*events[MODE_SIZE])(void*);
  void* objs[MODE_SIZE];
  bool attached[MODE_SIZE];

  public:
  Button();

  Button(int _pin);

  void attach(int _pin); // attach Buttons object to pin
  void attachEvent(int MODE, void (*_event)(void*), void*); // attach function to specific event
                                                            // see also: states.h
  void detachEvent(int MODE);
  void check(); // check pin state
  int getState(); // get pin state
};

#endif