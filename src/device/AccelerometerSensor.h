#pragma once

#include <Adafruit_LIS3DH.h>

#include <Config.h>

struct AccelerometerModel {
    int16_t x;
    int16_t y;
    int16_t z;
};

class AccelerometerSensor {
private:
    Adafruit_LIS3DH sensor = Adafruit_LIS3DH();
    AccelerometerModel currentSamples[ACCELEROMETER_SAMPLING_LENGTH];
    unsigned int samplePointer = 0;
    unsigned long timestamp;
public:
    AccelerometerSensor();
    bool fetchData();
    AccelerometerModel *getAllMeasurements();
    void clearMeasurements();
};