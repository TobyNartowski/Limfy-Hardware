#include "HeartbeatSensor.h"

HeartbeatSensor::HeartbeatSensor(uint8_t sensorPin) {
    this->sensorPin = sensorPin;
    timestamp = millis();
    memset(currentSamples, 0, HEARTBEAT_SAMPLE_LENGTH);
}

bool HeartbeatSensor::fetchData() {
    if (millis() - timestamp > HEARTBEAT_SAMPLING_DELAY) {
        uint8_t rawValue = analogRead(sensorPin);
        currentSamples[samplePointer] = rawValue;

        timestamp = millis();
        samplePointer++;
    }

    return samplePointer == (HEARTBEAT_SAMPLE_LENGTH - 1) ? true : false;
}

uint8_t *HeartbeatSensor::getAllMeasurements()
{
    return currentSamples;
}

void HeartbeatSensor::clearMeasurements()
{
        memset(currentSamples, 0, HEARTBEAT_SAMPLE_LENGTH);
        samplePointer = 0;
}