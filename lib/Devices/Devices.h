#ifndef __TIMER_DEVICES__
#define __TIMER_DEVICES__

#include <Button.h>

namespace devices {
extern Button left_touch, right_touch, reset;

void check();
}

#endif