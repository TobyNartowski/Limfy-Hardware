#include "AccelerometerSensor.h"

#include <Wire.h>

AccelerometerSensor::AccelerometerSensor()
{
    Wire.begin(PIN_ACCELEROMETER_SDA, PIN_ACCELEREMOTER_SCL);
    sensor.begin();
    sensor.setRange(LIS3DH_RANGE_4_G);
    timestamp = millis();
}

bool AccelerometerSensor::fetchData()
{
    if (millis() - timestamp > ACCELEROMETER_SAMPLING_DELAY) {
        sensor.read();
        uint16_t measurement = abs(sensor.x + sensor.y + sensor.z);
        if (pointer) {
            int32_t comparison = abs(measurement - buffer);
            if (comparison > ACCELEROMETER_STEPS_THRESHOLD && abs(pointer - detect) > 20) {
                stepsCounter++;
                detect = pointer;
            }

            if (comparison > ACCELEROMETER_SHAKE_THRESHOLD) {
                shakeCounter++;
            }

            if (comparison >= ACCELEROMETER_FALL_THRESHOLD) {
                fallDetected = true;
            }
            Serial.println(comparison);
        }

        buffer = measurement;
        timestamp = millis();
        pointer++;
    }
    
    return pointer == (ACCELEROMETER_SAMPLE_LENGTH - 2);
}

uint8_t AccelerometerSensor::getSteps()
{
    return stepsCounter;
}

uint8_t AccelerometerSensor::getShakiness()
{
    return shakeCounter;
}

bool AccelerometerSensor::isFallDetected()
{
    return fallDetected;
}

void AccelerometerSensor::clearMeasurements()
{
    pointer = buffer = detect = stepsCounter = shakeCounter = 0;
    fallDetected = false;
}