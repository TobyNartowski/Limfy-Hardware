#pragma once

#include <Arduino.h>

#include <Config.h>
#include <device/AccelerometerSensor.h>

#define DATA_HEARTRATE 0
#define DATA_STEPS 1
#define DATA_SHAKINESS 2

class DataProcessor {
private:
public:
    uint8_t getHeartrateData(uint8_t data[]);
    uint8_t getAccelerometerSteps(uint16_t data[]);
    uint8_t getAccelerometerShakiness(uint16_t data[]);
};