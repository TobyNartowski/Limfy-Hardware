#include "Display.h"

Display::Display()
{
    display.setFont(u8x8_font_7x14_1x2_r);
    display.begin();
}

void Display::drawCenter(String text)
{
    display.clearDisplay();
    display.drawString(display.getCols() / 2 - (text.length() / 2), display.getRows() /2 - 1, text.c_str());
}

void Display::drawHeartrate(uint8_t heartrate)
{
    display.clearLine(0);
    display.clearLine(1);
    if (heartrate == 0) {
        display.drawString(0, 0, "No data");
    } else {
        display.drawString(0, 0, ("BPM: " + String(heartrate)).c_str());
    }
}

void Display::drawAccelerometerData(uint8_t steps, uint8_t shakiness)
{
    display.clearLine(2);
    display.clearLine(3);
    display.drawString(0, 10, ("Steps: " + String(steps)).c_str());

    display.clearLine(4);
    display.clearLine(5);
    display.drawString(0, 20, ("Shakiness: " + String(shakiness)).c_str());
}