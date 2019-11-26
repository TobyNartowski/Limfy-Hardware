#pragma once

#include <Arduino.h>
#include <driver/adc.h>

#include <Config.h>

class HeartbeatSensor {
private:
    uint16_t pointer = 0;
    unsigned long timestamp;
    uint8_t plusCounter = 0, minusCounter = 0, beats = 0;
    int *data;
public:
    HeartbeatSensor();

    bool fetchData();
    uint8_t getHeartrate();
};