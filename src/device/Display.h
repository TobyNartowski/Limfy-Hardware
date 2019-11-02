#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

class Display {
private:
    U8X8_SH1106_128X64_VCOMH0_HW_I2C display;
    uint8_t heartrateBuffer = 0;
public:
    Display();
    void readyToDraw();
    void sendBuffer();
    void drawString(String text);
    void drawHeartrate(uint8_t heartrate);
};