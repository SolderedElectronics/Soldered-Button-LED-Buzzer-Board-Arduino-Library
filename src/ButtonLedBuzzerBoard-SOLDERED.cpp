/**
 **************************************************
 *
 * @file        ButtonLedBuzzerBoard-SOLDERED.cpp
 * @brief       Library for Soldered Button, LED & Buzzer Board (ATtiny404)
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Fran Fodor @ soldered.com
 ***************************************************/

#include "ButtonLedBuzzerBoard-SOLDERED.h"

ButtonLedBuzzerBoard_Soldered::ButtonLedBuzzerBoard_Soldered(uint8_t address)
{
    _address = address;
    memset(_ledBuf, 0, sizeof(_ledBuf));
}

void ButtonLedBuzzerBoard_Soldered::begin()
{
    Wire.begin();
}

void ButtonLedBuzzerBoard_Soldered::_writeLEDs()
{
    Wire.beginTransmission(_address);
    Wire.write(BLB_REG_LED);
    Wire.write(_ledBuf, BLB_NUM_LEDS * 3);
    Wire.endTransmission();
}

void ButtonLedBuzzerBoard_Soldered::setLED(uint8_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (index >= BLB_NUM_LEDS) return;
    _ledBuf[index * 3]     = r;
    _ledBuf[index * 3 + 1] = g;
    _ledBuf[index * 3 + 2] = b;
    _writeLEDs();
}

void ButtonLedBuzzerBoard_Soldered::setAllLEDs(uint8_t r, uint8_t g, uint8_t b)
{
    for (uint8_t i = 0; i < BLB_NUM_LEDS; i++)
    {
        _ledBuf[i * 3]     = r;
        _ledBuf[i * 3 + 1] = g;
        _ledBuf[i * 3 + 2] = b;
    }
    _writeLEDs();
}

void ButtonLedBuzzerBoard_Soldered::setLEDs(uint8_t r1, uint8_t g1, uint8_t b1,
                                            uint8_t r2, uint8_t g2, uint8_t b2,
                                            uint8_t r3, uint8_t g3, uint8_t b3)
{
    _ledBuf[0] = r1; _ledBuf[1] = g1; _ledBuf[2] = b1;
    _ledBuf[3] = r2; _ledBuf[4] = g2; _ledBuf[5] = b2;
    _ledBuf[6] = r3; _ledBuf[7] = g3; _ledBuf[8] = b3;
    _writeLEDs();
}

void ButtonLedBuzzerBoard_Soldered::setBuzzer(uint16_t freq)
{
    Wire.beginTransmission(_address);
    Wire.write(BLB_REG_BUZZER);
    Wire.write((uint8_t)(freq >> 8));
    Wire.write((uint8_t)(freq & 0xFF));
    Wire.endTransmission();
}

uint8_t ButtonLedBuzzerBoard_Soldered::readButtons()
{
    Wire.beginTransmission(_address);
    Wire.write(BLB_REG_BUTTONS);
    Wire.endTransmission();

    Wire.requestFrom(_address, (uint8_t)1);
    return Wire.available() ? Wire.read() : 0;
}

bool ButtonLedBuzzerBoard_Soldered::isButton1Pressed()
{
    return readButtons() & 0x01;
}

bool ButtonLedBuzzerBoard_Soldered::isButton2Pressed()
{
    return readButtons() & 0x02;
}

bool ButtonLedBuzzerBoard_Soldered::isButton3Pressed()
{
    return readButtons() & 0x04;
}
