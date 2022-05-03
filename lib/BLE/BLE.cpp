#include "BLE.h"
#include <Arduino.h>
#include <BLE2902.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <String>

bool TimerBLEServer::BLEConnected = false;

void TimerServerCallbacks::onConnect(BLEServer* pServer) {
  TimerBLEServer::BLEConnected = true;
}

void TimerServerCallbacks::onDisconnect(BLEServer* pServer) {
  TimerBLEServer::BLEConnected = false;
}

void TimerCallbacks::onWrite(BLECharacteristic* pCharacteristic) {
  std::string timingValue = pCharacteristic->getValue();
}

void TimerBLEServer::init(String name) {
  TimerBLEServer::BLEConnected = false;
  BLEDevice::init(name.c_str());

  BLEServer* pServer = BLEDevice::createServer();
  pServer->setCallbacks(new TimerServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  timing = pService->createCharacteristic(CHARACTERISTIC_UUID_TIMING, BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
  timing->addDescriptor(new BLE2902());
  timing->setCallbacks(new TimerCallbacks());

  time = pService->createCharacteristic(CHARACTERISTIC_UUID_TIME, BLECharacteristic::PROPERTY_READ);
  time->addDescriptor(new BLE2902());

  pService->start();
  pServer->getAdvertising()->start();
}

void TimerBLEServer::setTiming(int b) {
  timing->setValue(b);
  timing->notify();
}

void TimerBLEServer::setTime(uint32_t t) {
  time->setValue(t);
}