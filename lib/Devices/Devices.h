#ifndef __TIMER_DEVICES__
#define __TIMER_DEVICES__

#define LEFT_TOUCH 6
#define RIGHT_TOUCH 7
#define RESET 8
#define LED 13

#include <Button.h>

namespace devices {
extern Button left_touch, right_touch, reset;

void check();
}

#endif