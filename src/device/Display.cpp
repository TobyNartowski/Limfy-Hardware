#include "Display.h"

Display::Display()
{
    display.setFont(u8x8_font_7x14_1x2_r);
    display.begin();
}

void Display::drawString(String text)
{
    display.drawString(0, 0, text.c_str());
}

void Display::drawHeartrate(uint8_t heartrate)
{
    if (heartrateBuffer != heartrate) {
        display.clearLine(0);
        display.clearLine(1);
        if (heartrate == 255) {
            display.drawString(0, 0, "No data");
        } else {
            display.drawString(0, 0, ("BPM: " + String(heartrate)).c_str());
        }
    }

    heartrateBuffer = heartrate;
}