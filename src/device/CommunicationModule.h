#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <Config.h>

class CommunicationModule {
private:
    SoftwareSerial *com;
    String readSerial(unsigned long timeout);
    uint8_t bootCounter = 0;
    void checkConnection();
    void initNetwork();
    void reset();
public:
    CommunicationModule();
    void begin();
    void check();
    void sendData(String data);
    String executeCommand(String command, unsigned long delayMs);
};