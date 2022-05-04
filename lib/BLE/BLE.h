#ifndef __TIMER_BLE__
#define __TIMER_BLE__

#include <Arduino.h>
#include <BLECharacteristic.h>
#include <BLEServer.h>
#include <BLEService.h>

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
  static BLECharacteristic *pTiming, *pTime;
  static BLEServer* pServer;
  static BLEService* pService;

  public:
  static bool BLEConnected;
  static void init(String);
  static void setTiming(int);
  static void setTime(uint32_t);
};

#endif