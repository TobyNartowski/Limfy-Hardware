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
    display.clearLine(2);
    display.clearLine(3);
    if (heartrate == 0) {
        display.drawString(0, 10, "Brak danych");
    } else {
        display.drawString(0, 10, ("Puls: " + (String(heartrate) + " BPM")).c_str());
    }
}

void Display::drawSteps(uint16_t steps)
{
    display.clearLine(4);
    display.clearLine(5);
    display.drawString(0, 20, ("Kroki: " + String(steps)).c_str());
}