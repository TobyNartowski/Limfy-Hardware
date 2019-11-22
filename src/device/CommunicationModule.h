#pragma once

#include <Arduino.h>
#include <BLEDevice.h>

class CommunicationModule {
private:
    BLEServer *server;
    BLEService *service;

    BLECharacteristic *heartbeatCharacteristic;
    BLECharacteristic *stepsCharacteristic;
    BLECharacteristic *shakinessCharacteristic;
public:
    CommunicationModule();

    void setHeartbeat(uint8_t heartbeat);
    void setSteps(uint8_t steps);
    void setShakiness(uint16_t shakiness);
};