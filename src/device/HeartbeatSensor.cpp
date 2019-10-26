#include "HeartbeatSensor.h"

HeartbeatSensor::HeartbeatSensor(uint8_t sensorPin) {
    this->sensorPin = sensorPin;
    this->timestamp = millis();
    memset(currentSamples, 0, SAMPLE_LENGTH);
}

bool HeartbeatSensor::fetchData() {
    if (millis() - timestamp > SAMPLING_DELAY) {
        uint8_t rawValue = analogRead(sensorPin);
        currentSamples[samplePointer] = rawValue;

        timestamp = millis();
        samplePointer++;
    }

    return samplePointer == (SAMPLE_LENGTH - 1) ? true : false;
}

uint8_t *HeartbeatSensor::getAllMeasurements()
{
    return currentSamples;
}

void HeartbeatSensor::clearMeasurements()
{
        memset(currentSamples, 0, SAMPLE_LENGTH);
        samplePointer = 0;
}