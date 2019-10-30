#include "DataProcessor.h"

uint8_t DataProcessor::getHeartrate(uint8_t data[])
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