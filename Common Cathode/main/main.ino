/*
 * By Danushka Dissanayaka
 * Pin configuration
 * 13 -> SCK
 * 11 -> DIN
 * 10 -> LOAD
 */

#include "Max_7219_Com_Cathod.h"

Max_7219_Com_Cathod display(10);

void setup()
{
    display.init(2, 0xFF); // number of digits and display brightness
    Serial.begin(115200);
}

void loop()
{
    for (int i = 0; i < 100; i++)
    {
        display.displayNumber(i);
        delay(1000);
    }
}
