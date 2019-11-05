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
    bool checkConnection();
    void initNetwork();
};