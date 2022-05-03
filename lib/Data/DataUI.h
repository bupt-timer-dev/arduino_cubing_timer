#ifndef __TIMER_DATA_UI__
#define __TIMER_DATA_UI__

#define EEP_START 2 * 1024

#include <Arduino.h>
#include <Data.h>
#include <Devices.h>
#include <MenuProvider.h>

class DataUI : MenuProvider {
  public:
  DataUI() { title = "Data"; }
};

#endif