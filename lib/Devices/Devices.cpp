#include "Devices.h"
#include <AT24Cxx.h>
#include <Button.h>
#include <Data.h>
#include <Display.h>
#include <Timer.h>

namespace devices {
Button leftTouch(LEFT_TOUCH), rightTouch(RIGHT_TOUCH), reset(RESET);
AT24Cxx eep(EEP_ADDRESS, EEP_SIZE);
Data timingData(&eep, 2 * 1024);
Display display(LCD_ADDRESS, LCD_WIDTH, LCD_HEIGHT);
Timer t;

void check() {
  leftTouch.check();
  rightTouch.check();
  reset.check();
}
}