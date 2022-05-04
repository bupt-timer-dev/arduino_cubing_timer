#include "BLE.h"
#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <Devices.h>
#include <String>

BLECharacteristic *TimerBLEServer::pTiming = NULL, *TimerBLEServer::pTime = NULL;
BLEServer* TimerBLEServer::pServer = NULL;
BLEService* TimerBLEServer::pService = NULL;
bool TimerBLEServer::BLEConnected = false;

void TimerServerCallbacks::onConnect(BLEServer* pServer) {
  TimerBLEServer::BLEConnected = true;
}

void TimerServerCallbacks::onDisconnect(BLEServer* pServer) {
  TimerBLEServer::BLEConnected = false;
  pServer->getAdvertising()->start();
}

void TimerCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
  std::string timingValue = pCharacteristic->getValue();
  if (timingValue[0] == '0' && devices::t.isTiming()) { devices::t.stop(); }
  if (timingValue[0] == '1' && !devices::t.isTiming()) { devices::t.start(); }
}

void TimerBLEServer::init(String name) {
  TimerBLEServer::BLEConnected = false;
  BLEDevice::init(name.c_str());

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new TimerServerCallbacks());

  pService = pServer->createService(SERVICE_UUID);

  pTiming = pService->createCharacteristic(CHARACTERISTIC_UUID_TIMING, BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  pTiming->addDescriptor(new BLE2902());
  pTiming->setCallbacks(new TimerCallbacks());

  pTime = pService->createCharacteristic(CHARACTERISTIC_UUID_TIME, BLECharacteristic::PROPERTY_READ);
  pTime->addDescriptor(new BLE2902());

  pService->start();
  pServer->getAdvertising()->start();
}

void TimerBLEServer::setTiming(int b) {
  pTiming->setValue(b);
  pTiming->notify();
}

void TimerBLEServer::setTime(uint32_t t) {
  pTime->setValue(t);
}