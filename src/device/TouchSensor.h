#pragma once

class TouchSensor {
private:
    int sensorPin;
public:
    TouchSensor(int sensorPin);
    bool isTouched();
};