/**
 **************************************************
 *
 * @file        LEDs.ino
 * @brief       LED test for Soldered Button, LED & Buzzer Board
 *              Host: ESP32 WROVER-E
 *
 * Cycles each LED through red, green, blue individually,
 * then cycles all LEDs together.
 *
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "ButtonLedBuzzerBoard-SOLDERED.h"

ButtonLedBuzzerBoard_Soldered board;

void setup()
{
    Wire.begin(); // if not using Qwiic, specify I2C pins: Wire.begin(21, 22)
    board.begin();
    delay(2000);

    board.setAllLEDs(0, 0, 0);
}

void loop()
{
    // Test each LED individually
    for (uint8_t i = 0; i < 3; i++)
    {
        board.setAllLEDs(0, 0, 0);
        board.setLED(i, 255, 0, 0); delay(400); // red
        board.setLED(i, 0, 255, 0); delay(400); // green
        board.setLED(i, 0, 0, 255); delay(400); // blue
    }

    // All LEDs together
    board.setAllLEDs(255,   0,   0); delay(500); // red
    board.setAllLEDs(  0, 255,   0); delay(500); // green
    board.setAllLEDs(  0,   0, 255); delay(500); // blue
    board.setAllLEDs(255, 255, 255); delay(500); // white
    board.setAllLEDs(  0,   0,   0); delay(500); // off
}
