#ifndef __TIMER_DEVICES__
#define __TIMER_DEVICES__

#define LEFT_TOUCH 27
#define RIGHT_TOUCH 17
#define RESET 12
#define LED 13
#define EEP_ADDRESS 0x5e
#define EEP_SIZE 256

#include <AT24Cxx.h>
#include <Button.h>
#include <Data.h>
#include <Display.h>
#include <Timer.h>

namespace devices {
extern Button leftTouch, rightTouch, reset;
extern AT24Cxx eep;
extern Data timingData;
extern Timer t;
extern Display display;

void check();
}

#endif