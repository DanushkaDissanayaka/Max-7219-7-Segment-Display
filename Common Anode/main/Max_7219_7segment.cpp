#include "Max_7219_7segment.h"

byte values[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

Max_7219_7segment ::Max_7219_7segment(uint8_t csPin)
{
    this->chip_select = csPin;
}

void Max_7219_7segment ::init(uint8_t digits, uint8_t brightLevel)
{
    this->numberofDigits = digits;
    pinMode(this->chip_select, OUTPUT); // chip select

    SPI.begin(); // begin SPI Stransfer

    // set up max7219

    // Disabled BCD mode
    MAX7219Send(this->chip_select, DECODE_MODE, 0x00);

    // brightness
    MAX7219Send(this->chip_select, INTENSITY, brightLevel);

    // Set scan limit scan
    MAX7219Send(this->chip_select, SCAN_LIMIT, digits-1);

    // Turn on chip
    MAX7219Send(this->chip_select, SHUTDOWN, 0x01);
}

void Max_7219_7segment::MAX7219Send(uint8_t chip_select, uint8_t address, uint8_t value)
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

void Max_7219_7segment::buffer(uint8_t address, uint8_t value)
{
    switch (address)
    {
    case (A):
        values[0] |= value;
        break;
    case (B):
        values[1] |= value;
        break;
    case (C):
        values[2] |= value;
        break;
    case (D):
        values[3] |= value;
        break;
    case (E):
        values[4] |= value;
        break;
    case (F):
        values[5] |= value;
        break;
    case (G):
        values[6] |= value;
        break;
    case (DP):
        values[7] |= value;
        break;
    default:
        break;
    }
}

void Max_7219_7segment::render(uint8_t chip_select)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        MAX7219Send(chip_select, i + 1, values[i]);
    }
    for (uint8_t i = 0; i < 8; i++)
    {
        values[i] = 0x00;
    }
}

void Max_7219_7segment::drawNumber(uint8_t number, uint8_t position, bool decimal)
{
    switch (number)
    {
    case 0:
        buffer(A, digits[position]);
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        buffer(D, digits[position]);
        buffer(E, digits[position]);
        buffer(F, digits[position]);
        break;
    case 1:
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        break;
    case 2:
        buffer(A, digits[position]);
        buffer(B, digits[position]);
        buffer(G, digits[position]);
        buffer(E, digits[position]);
        buffer(D, digits[position]);
        break;
    case 3:
        buffer(A, digits[position]);
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        buffer(D, digits[position]);
        buffer(G, digits[position]);
        break;
    case 4:
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        buffer(F, digits[position]);
        buffer(G, digits[position]);
        break;
    case 5:
        buffer(A, digits[position]);
        buffer(F, digits[position]);
        buffer(G, digits[position]);
        buffer(C, digits[position]);
        buffer(D, digits[position]);
        break;
    case 6:
        buffer(A, digits[position]);
        buffer(C, digits[position]);
        buffer(D, digits[position]);
        buffer(E, digits[position]);
        buffer(F, digits[position]);
        buffer(G, digits[position]);
        break;
    case 7:
        buffer(A, digits[position]);
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        break;
    case 8:
        buffer(A, digits[position]);
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        buffer(D, digits[position]);
        buffer(E, digits[position]);
        buffer(F, digits[position]);
        buffer(G, digits[position]);
        break;
    case 9:
        buffer(A, digits[position]);
        buffer(B, digits[position]);
        buffer(C, digits[position]);
        buffer(D, digits[position]);
        buffer(F, digits[position]);
        buffer(G, digits[position]);
        break;

    default:
        break;
    }
    if (decimal)
    {
        buffer(DP, digits[position]);
    }
}

void Max_7219_7segment::displayNumber(unsigned int number)
{

    for (uint8_t i = 0; i < this->numberofDigits; i++)
    {
        byte character = number % 10; //get the value of the rightmost digit
        if (number == 0 && i > 0)
            character = 0xf;
        drawNumber(character, this->numberofDigits - (i + 1), false);
        number = number / 10;
    }
    render(this->chip_select);
}

void Max_7219_7segment::displayFloat(float number, uint8_t precision)
{

    int integer = (int)number;
    int decimal = (int)(number * 100) % 100;

    for (int i = 0; i < precision; i++)
    {
        byte character = decimal % 10; //get the value of the rightmost digit
        // if (decimal == 0 && i > 0)
        //     character = 0xf;
        drawNumber(character, this->numberofDigits - (i + 1), false);
        decimal = decimal / 10;
    }

    for (int i = precision; i < this->numberofDigits; i++)
    {
        byte character = integer % 10; //get the value of the rightmost digit
        if (integer == 0 && i > 0)
            character = 0xf;
        if (i == precision)
            drawNumber(character, this->numberofDigits - (i + 1), true);
        else
            drawNumber(character, this->numberofDigits - (i + 1), false);
        integer = integer / 10;
    }
    render(this->chip_select);
}

void Max_7219_7segment::displayNumber(unsigned int number ,uint8_t lengthNumber)
{

    for (uint8_t i = 0; i < lengthNumber; i++)
    {
        byte character = number % 10; //get the value of the rightmost digit
        if (number == 0 && i > 0)
            character = 0xf;
        drawNumber(character, lengthNumber - (i + 1), false);
        number = number / 10;
    }
}

void Max_7219_7segment::displayNumber(unsigned int number1, uint8_t lengthNumber1, unsigned int number2, uint8_t lengthNumber2){
    displayNumber(number2,lengthNumber1+lengthNumber2);
    displayNumber(number1,lengthNumber1);
    render(this->chip_select);
}

void Max_7219_7segment::displayFloat(float number, uint8_t precision, uint8_t lengthNumber)
{
    unsigned int power = pow(10, precision);
    int integer = (int)number;
    int decimal = (int)(number * power) % power;

    for (int i = 0; i < precision; i++)
    {
        byte character = decimal % 10; //get the value of the rightmost digit
        // if (decimal == 0 && i > 0)
        //     character = 0xf;
        drawNumber(character, lengthNumber - (i + 1), false);
        decimal = decimal / 10;
    }

    for (int i = precision; i < lengthNumber; i++)
    {
        byte character = integer % 10; //get the value of the rightmost digit
        if (integer == 0 && i > 0)
            character = 0xf;
        if (i == precision)
            drawNumber(character, lengthNumber - (i + 1), true);
        else
            drawNumber(character, lengthNumber - (i + 1), false);
        integer = integer / 10;
    }
}

void Max_7219_7segment::displayFloat(float number1, uint8_t precision1, uint8_t lengthNumber1, float number2, uint8_t precision2, uint8_t lengthNumber2)
{
    displayFloat(number2, precision2, lengthNumber1 + lengthNumber2);
    displayFloat(number1, precision1, lengthNumber1);
    render(this->chip_select);
}

void Max_7219_7segment::cleanDisplay(){
    for(uint8_t i = 0; i < 8; i++)
    {
        values[i] = 0x00;
    }
}
