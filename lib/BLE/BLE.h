#include <Arduino.h>
#include <BLEServer.h>

#ifndef __TIMER_BLE__

#define __TIMER_BLE__

#define SERVICE_UUID "8F3984DD-E8F8-47CB-919C-C9EC3DC2F0DB"
#define CHARACTERISTIC_UUID_TIMING "8F3984DE-E8F8-47CB-919C-C9EC3DC2F0DB"
#define CHARACTERISTIC_UUID_TIME "8F3984DF-E8F8-47CB-919C-C9EC3DC2F0DB"

class TimerServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer*);
  void onDisconnect(BLEServer*);
};

class TimerCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic*);
};

class TimerBLEServer {
  BLECharacteristic *timing, *time;

  public:
  static bool BLEConnected;
  void init(String);
  void setTiming(int);
  void setTime(uint32_t);
};

#endif