#include "HeartbeatSensor.h"

HeartbeatSensor::HeartbeatSensor() {
    timestamp = millis();
    adc2_config_channel_atten(PIN_HEARTBEAT_SENSOR, ADC_ATTEN_0db);
    data = (int *) malloc(sizeof(int));
}

bool HeartbeatSensor::fetchData() {
    if (millis() - timestamp > HEARTBEAT_SAMPLING_DELAY) {
        adc2_get_raw(PIN_HEARTBEAT_SENSOR, ADC_WIDTH_12Bit, data);

        if ((*data) >= HEARTBEAT_THRESHOLD) {
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

        timestamp = millis();
        pointer++;
    }

    return pointer == (HEARTBEAT_SAMPLE_LENGTH - 1);
}

uint8_t HeartbeatSensor::getHeartrate()
{
    uint8_t bufferBeats = beats;
    pointer = plusCounter = minusCounter = beats = 0;
    return bufferBeats * (60 / (HEARTBEAT_SAMPLING_TIME / 1000));
}