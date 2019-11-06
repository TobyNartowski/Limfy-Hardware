#pragma once

#include <Arduino.h>
#include <SoftwareSerial.h>

#include <Config.h>

class CommunicationModule {
private:
    SoftwareSerial *com;
    String readSerial(unsigned long timeout);
public:
    CommunicationModule();
    void begin();
    void reset();
    bool checkConnection();
    void initNetwork();
    void sendData();
    String executeCommand(String command, unsigned long delayMs);
};