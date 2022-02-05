#ifndef __TIMER_DEVICES__
#define __TIMER_DEVICES__

#define LEFT_TOUCH 16
#define RIGHT_TOUCH 17
#define RESET 18
#define LED 13

#include <Button.h>
#include <Menu.h>

namespace devices {
extern Button left_touch, right_touch, reset;

void check();

class DeviceUI : public MenuProvider {
};

extern DeviceUI device_menu;
}

#endif