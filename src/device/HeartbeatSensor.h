#pragma once

#include <Arduino.h>

#define SAMPLING_TIME 12000
#define SAMPLING_DELAY 30

#define SAMPLE_LENGTH SAMPLING_TIME / SAMPLING_DELAY

class HeartbeatSensor {
private:
    uint8_t sensorPin;
    uint8_t currentSamples[SAMPLE_LENGTH];
    unsigned int samplePointer = 0;
    unsigned long timestamp;

public:
    HeartbeatSensor(uint8_t sensorPin);

    bool fetchData();
    uint8_t *getAllMeasurements();
    void clearMeasurements();
};