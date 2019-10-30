#pragma once

#include <Arduino.h>

#include <Config.h>

class HeartbeatSensor {
private:
    uint8_t sensorPin;
    uint8_t currentSamples[HEARTBEAT_SAMPLE_LENGTH];
    unsigned int samplePointer = 0;
    unsigned long timestamp;

public:
    HeartbeatSensor(uint8_t sensorPin);

    bool fetchData();
    uint8_t *getAllMeasurements();
    void clearMeasurements();
};