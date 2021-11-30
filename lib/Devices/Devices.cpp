#include "Devices.h"
#include "consts.h"
#include <Button.h>

Button devices::left_touch(LEFT_TOUCH), devices::right_touch(RIGHT_TOUCH), devices::reset(RESET);

void devices::check() {
  left_touch.check();
  right_touch.check();
  reset.check();
}