#include "Devices.h"
#include <BLE.h>
#include <Button.h>
#include <Data.h>
#include <utils.h>

namespace devices {
Button leftTouch(LEFT_TOUCH), rightTouch(RIGHT_TOUCH), reset(RESET);
AT24Cxx eep(EEP_ADDRESS, EEP_SIZE);
Data timingData(&eep, 2 * 1024);
TimerBLEServer ble;
bool BLE_connected = false;

void check() {
  leftTouch.check();
  rightTouch.check();
  reset.check();
}
}