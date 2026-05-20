/**
 **************************************************
 *
 * @file        Buttons.ino
 * @brief       Button test for Soldered Button, LED & Buzzer Board
 *              Host: ESP32 WROVER-E
 *
 * Prints button states to Serial Monitor (115200 baud).
 * Shows press and release events.
 *
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "ButtonLedBuzzerBoard-SOLDERED.h"

ButtonLedBuzzerBoard_Soldered board;

uint8_t lastButtons = 0;

void setup()
{
    Serial.begin(115200);
    Wire.begin(); // if not using Qwiic, specify I2C pins: Wire.begin(21, 22)
    board.begin();
    delay(2000);

    Serial.println("Button, LED & Buzzer Board - Button Test");
    Serial.println("Press any button...");
}

void loop()
{
    uint8_t buttons = board.readButtons();

    if (buttons != lastButtons)
    {
        for (uint8_t i = 0; i < 3; i++)
        {
            uint8_t mask = 1 << i;
            if ((buttons & mask) && !(lastButtons & mask))
            {
                Serial.print("BTN"); Serial.print(i + 1); Serial.println(" pressed");
            }
            else if (!(buttons & mask) && (lastButtons & mask))
            {
                Serial.print("BTN"); Serial.print(i + 1); Serial.println(" released");
            }
        }
        lastButtons = buttons;
    }

    delay(20);
}
