#include "DataProcessor.h"

uint8_t DataProcessor::getHeartrateData(uint8_t data[])
{
    uint8_t plusCounter = 0, minusCounter = 0;
    uint8_t beats = 0;
    for (unsigned int i = 0; i < HEARTBEAT_SAMPLE_LENGTH; i++) {
        if (data[i] >= HEARTBEAT_THRESHOLD) {
            if (minusCounter > HEARTBEAT_MAX_PEAK_LENGTH) {
                plusCounter = minusCounter = 0;
            }
            plusCounter++;
        } else {
            minusCounter++;
        }

        if (minusCounter > HEARTBEAT_MAX_PEAK_LENGTH && plusCounter > HEARTBEAT_MIN_LENGTH) {
            plusCounter = minusCounter = 0;
            beats++;
        }
    }

    if (plusCounter > HEARTBEAT_MIN_LENGTH) {
        beats++;
    }

    return beats * (60 / (HEARTBEAT_SAMPLING_TIME / 1000));
}

uint8_t DataProcessor::getAccelerometerSteps(uint16_t data[])
{
    uint8_t stepsCounter = 0;

    uint8_t detect = 255;
    uint16_t buffer = data[1];
    for (int i = 2; i < ACCELEROMETER_SAMPLE_LENGTH - 1; i++) {
        int16_t comparison = abs(data[i] - buffer);
        if (comparison > ACCELEROMETER_STEPS_THRESHOLD && abs(i - detect) > 5) {
            stepsCounter++;
            detect = i;
        }
        buffer = data[i];
    }
    
    return stepsCounter;
}

uint8_t DataProcessor::getAccelerometerShakiness(uint16_t data[])
{
    uint8_t shakeCounter = 0;

    uint16_t buffer = data[1];
    for (int i = 2; i < ACCELEROMETER_SAMPLE_LENGTH - 1; i++) {
        int16_t comparison = abs(data[i] - buffer);
        if (comparison > ACCELEROMETER_SHAKE_THRESHOLD) {
            shakeCounter++;
        }
        
        buffer = data[i];
    }
    
    return shakeCounter;
}