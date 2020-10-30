#include "Max_7219_Com_Cathod.h"

Max_7219_Com_Cathod::Max_7219_Com_Cathod(uint8_t csPin)
{
    this->chip_select = csPin;
}

void Max_7219_Com_Cathod::init(uint8_t digits, uint8_t brightLevel)
{
    this->numberofDigits = digits;
    pinMode(this->chip_select, OUTPUT); // chip select

    SPI.begin(); // begin SPI Stransfer

    // set up max7219

    // Disabled BCD mode
    MAX7219Send(this->chip_select, DECODE_MODE, 0xFF);

    // brightness
    MAX7219Send(this->chip_select, INTENSITY, brightLevel);

    // Set scan limit scan
    MAX7219Send(this->chip_select, SCAN_LIMIT, digits - 1);

    // Turn on chip
    MAX7219Send(this->chip_select, SHUTDOWN, 0x01);
}

 void Max_7219_Com_Cathod::MAX7219Send(uint8_t chip_select, uint8_t address, uint8_t value)
{
    // Ensure LOAD/CS is LOW
    digitalWrite(chip_select, LOW);

    // Send the register address
    SPI.transfer(address);

    // Send the value
    SPI.transfer(value);

    // Tell chip to load in data
    digitalWrite(chip_select, HIGH);
}

 void Max_7219_Com_Cathod::displayNumber(uint8_t chip_select, unsigned int number, uint8_t lengthNumber)
{
    for (int i = 0; i < lengthNumber; i++)
    {
        byte character = number % 10; //get the value of the rightmost digit
        if (number == 0 && i > 0)
            character = 0xf;
        MAX7219Send(chip_select, lengthNumber - i, character);
        number = number / 10;
    }
}

void Max_7219_Com_Cathod::displayNumber(unsigned int number)
{
    displayNumber(this->chip_select, number, this->numberofDigits);
}

void Max_7219_Com_Cathod::displayNumber(unsigned int number1, uint8_t lengthNumber1,
                                        unsigned int number2, uint8_t lengthNumber2)
{
    displayNumber(this->chip_select, number2, lengthNumber1 + lengthNumber2);
    displayNumber(this->chip_select, number1, lengthNumber1);
}

 void Max_7219_Com_Cathod::displayFloat(uint8_t chip_select, float number, uint8_t precision, uint8_t lengthNumber)
{
    unsigned int power = pow(10, precision);
    int integer = (int)number;
    int decimal = (int)(number * power) % power;

    for (int i = 0; i < precision; i++)
    {
        byte character = decimal % 10; //get the value of the rightmost digit
        // if (decimal == 0 && i > 0)
        //     character = 0xf;
        MAX7219Send(chip_select, lengthNumber - i, character);
        decimal = decimal / 10;
    }

    for (int i = precision; i < lengthNumber; i++)
    {
        byte character = integer % 10; //get the value of the rightmost digit
        if (integer == 0 && i > 0)
            character = 0xf;
        if (i == precision && precision != 0)
            MAX7219Send(chip_select, lengthNumber - i, character + 128);
        else
            MAX7219Send(chip_select, lengthNumber - i, character);
        integer = integer / 10;
    }
}

void Max_7219_Com_Cathod::displayFloat(float number, uint8_t precision)
{
    displayFloat(this->chip_select, number, precision, this->numberofDigits);
}

void Max_7219_Com_Cathod::displayFloat(float number1, uint8_t precision1, uint8_t lengthNumber1,
                                       float number2, uint8_t precision2, uint8_t lengthNumber2)
{
    displayFloat(this->chip_select, number2, precision2, lengthNumber1 + lengthNumber2);
    displayFloat(this->chip_select, number1, precision1, lengthNumber1);
}

void Max_7219_Com_Cathod::displayFloat(float number1, uint8_t precision1, uint8_t lengthNumber1,
                                       float number2, uint8_t precision2, uint8_t lengthNumber2,
                                       float number3, uint8_t precision3, uint8_t lengthNumber3)
{
    displayFloat(this->chip_select, number3, precision3, lengthNumber1 + lengthNumber2 + lengthNumber3);
    displayFloat(this->chip_select, number2, precision2, lengthNumber1 + lengthNumber2);
    displayFloat(this->chip_select, number1, precision1, lengthNumber1);
}
