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
         currentSamples[samplePointer] = {sensor.x, sensor.y, sensor.z};

         timestamp = millis();
         samplePointer++;
    }

    return samplePointer == (ACCELEROMETER_SAMPLING_LENGTH - 1) ? true : false;
}

AccelerometerModel *AccelerometerSensor::getAllMeasurements()
{
    return currentSamples;
}

void AccelerometerSensor::clearMeasurements()
{
        memset(currentSamples, 0, ACCELEROMETER_SAMPLING_LENGTH);
        samplePointer = 0;
}