#include "AccelerometerSensor.h"

AccelerometerSensor::AccelerometerSensor()
{
    sensor.begin();
    sensor.setRange(LIS3DH_RANGE_4_G);
    timestamp = millis();
    memset(currentSamples, 0, HEARTBEAT_SAMPLE_LENGTH);
}

bool AccelerometerSensor::fetchData()
{
    if (millis() - timestamp > ACCELEROMETER_SAMPLING_DELAY) {
        sensor.read();
         currentSamples[samplePointer] = abs(sensor.x + sensor.y + sensor.z);

         timestamp = millis();
         samplePointer++;
    }

    return samplePointer == (ACCELEROMETER_SAMPLE_LENGTH - 1) ? true : false;
}

uint16_t *AccelerometerSensor::getAllMeasurements()
{
    return currentSamples;
}

void AccelerometerSensor::clearMeasurements()
{
        memset(currentSamples, 0, ACCELEROMETER_SAMPLE_LENGTH);
        samplePointer = 0;
}