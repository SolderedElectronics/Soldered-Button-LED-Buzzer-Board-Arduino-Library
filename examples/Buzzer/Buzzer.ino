/**
 **************************************************
 *
 * @file        Buzzer.ino
 * @brief       Buzzer test for Soldered Button, LED & Buzzer Board
 *              Host: ESP32 WROVER-E
 *
 * Plays a sweep of frequencies to test the buzzer.
 *
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "ButtonLedBuzzerBoard-SOLDERED.h"

ButtonLedBuzzerBoard_Soldered board;

const uint16_t frequencies[] = {500, 1000, 2000, 3000, 4000};
const uint8_t numFreqs = sizeof(frequencies) / sizeof(frequencies[0]);

void setup()
{
    Wire.begin(); // if not using Qwiic, specify I2C pins: Wire.begin(21, 22)
    board.begin();
    delay(2000);
}

void loop()
{
    for (uint8_t i = 0; i < numFreqs; i++)
    {
        board.setBuzzer(frequencies[i]);
        delay(400);
        board.setBuzzer(0);
        delay(200);
    }

    delay(1000);
}
