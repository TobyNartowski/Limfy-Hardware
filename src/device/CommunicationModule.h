#pragma once

#include <Arduino.h>
#include <BLEDevice.h>

#include <Config.h>

class CommunicationModule {
private:
    BLEServer *server;
    BLEService *service;

    BLECharacteristic *heartbeatCharacteristic;
    BLECharacteristic *stepsCharacteristic;
    BLECharacteristic *shakinessCharacteristic;

    class ServerCallbacks : public BLEServerCallbacks {
    public:
        void onConnect(BLEServer* pServer) override {
            digitalWrite(PIN_CONNECT_LED, HIGH);
        }

	    void onDisconnect(BLEServer* pServer) override {
            digitalWrite(PIN_CONNECT_LED, LOW);
        }
    };
public:
    CommunicationModule();

    void setHeartbeat(uint8_t heartbeat);
    void setSteps(uint8_t steps);
    void setShakiness(uint8_t shakiness);
};