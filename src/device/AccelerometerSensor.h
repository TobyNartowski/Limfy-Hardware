#pragma once

#include <Adafruit_LIS3DH.h>

#include <Config.h>


class AccelerometerSensor {
private:
    Adafruit_LIS3DH sensor = Adafruit_LIS3DH();
    uint16_t pointer = 0;
    unsigned long timestamp;
    uint16_t buffer = 0;
    uint8_t detect = 0, stepsCounter = 0, shakeCounter = 0;
    bool fallDetected = false;
public:
    AccelerometerSensor();
    bool fetchData();
    uint8_t getSteps();
    uint8_t getShakiness();
    bool isFallDetected();
    void clearMeasurements();
};