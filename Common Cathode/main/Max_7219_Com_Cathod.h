#include <SPI.h>
#include <math.h>
#ifndef MAX_7219_COM_CATHOD_H
#define MAX_7219_COM_CATHOD_H

// The Max7219 Registers :
#define DECODE_MODE 0x09
#define INTENSITY 0x0a
#define SCAN_LIMIT 0x0b
#define SHUTDOWN 0x0c
#define DISPLAY_TEST 0x0f

class Max_7219_Com_Cathod
{
  private:
    uint8_t chip_select;
    uint8_t numberofDigits;
    /*
    * To send command directly to MAX7219 use this method
    * Address is the registry address
    * Value is registry value
    */
    static void MAX7219Send(uint8_t chip_select, uint8_t address, uint8_t value);
    /*
    *
    * 
    */
    static void displayFloat(float number, uint8_t precision, uint8_t lengthNumber);
    /*
    *
    * 
    */
    static void displayNumber(uint8_t chip_select, unsigned int number, uint8_t lengthNumber);
    /*
    *
    * 
    */
    static void displayFloat(uint8_t chip_select, float number, uint8_t precision, uint8_t lengthNumber);

  public:
    /*
    * Constructor
    * 
    */
    Max_7219_Com_Cathod(uint8_t csPin);

    /*
    * initialize MAX7219 chip communication
    * before use the device init() method has to be call
    * digits is no of digits that you want to display
    */
    void init(uint8_t digits, uint8_t brightLevel);

    /*
    *
    * 
    */
    void displayNumber(unsigned int number);

    /*
    *
    * 
    */
    void displayNumber(unsigned int number1, uint8_t lengthNumber1,
                       unsigned int number2, uint8_t lengthNumber2);
    /*
    *
    * 
    */
    void displayFloat(float number, uint8_t precision);
    /*
    *
    * 
    */
    void displayFloat(float number1, uint8_t precision1, uint8_t lengthNumber1,
                      float number2, uint8_t precision2, uint8_t lengthNumber2);
    /*
    *
    * 
    */
    void displayFloat(float number1, uint8_t precision1, uint8_t lengthNumber1,
                      float number2, uint8_t precision2, uint8_t lengthNumber2,
                      float number3, uint8_t precision3, uint8_t lengthNumber3);
};

#endif