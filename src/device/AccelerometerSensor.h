#pragma once

#include <Adafruit_LIS3DH.h>

#include <Config.h>

class AccelerometerSensor {
private:
    Adafruit_LIS3DH sensor = Adafruit_LIS3DH();
    uint16_t currentSamples[ACCELEROMETER_SAMPLE_LENGTH];
    unsigned int samplePointer = 0;
    unsigned long timestamp;
public:
    AccelerometerSensor();
    bool fetchData();
    uint16_t *getAllMeasurements();
    void clearMeasurements();
};