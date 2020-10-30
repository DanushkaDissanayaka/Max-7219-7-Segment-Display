/*
 * By Danushka Dissanayaka
 * Pin configuration
 * 13 -> SCK
 * 11 -> DIN
 * 10 -> LOAD
 */
#include "Max_7219_7segment.h"

Max_7219_7segment display1(10);

void setup()
{
    Serial.begin(9600);
    display1.init(1, 0xFF);
}

void loop()
{
    for (unsigned int i = 0; i < 10; i++)
    {
        display1.displayNumber(i);
        delay(500);
    }
}
