#include "Devices.h"
#include <Button.h>
#include <utils.h>

Button devices::left_touch(LEFT_TOUCH), devices::right_touch(RIGHT_TOUCH), devices::reset(RESET);

void devices::check() {
  left_touch.check();
  right_touch.check();
  reset.check();
}