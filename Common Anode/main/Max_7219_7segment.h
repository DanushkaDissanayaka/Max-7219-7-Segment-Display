#include <SPI.h>
#include <math.h>

#ifndef MAX_7219_7SEGMENT_H
#define MAX_7219_7SEGMENT_H

typedef unsigned char uint8_t;

// The Max7219 Registers :
#define DECODE_MODE 0x09
#define INTENSITY 0x0a
#define SCAN_LIMIT 0x0b
#define SHUTDOWN 0x0c
#define DISPLAY_TEST 0x0f

enum segmants
{
  A = 0b00000001,
  B = 0b00000010,
  C = 0b0000011,
  D = 0b0000100,
  E = 0b0000101,
  F = 0b0000110,
  G = 0b0000111,
  DP = 0b0001000
};

const byte digits[8]{
    0b01000000,
    0b00100000,
    0b00010000,
    0b00001000,
    0b00000100,
    0b00000010,
    0b00000001,
    0b10000000
    };

class Max_7219_7segment
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
  static void buffer(uint8_t address, uint8_t value);

  /*
    *
    * 
    */
  static void drawNumber(uint8_t number, uint8_t position, bool decimal);

  /*
    *
    * 
    */
  static void render(uint8_t chip_select);

  /*
    *
    * 
    */
  static void displayFloat(float number, uint8_t precision, uint8_t lengthNumber);
  /*
   *
   * 
   */
  static void displayNumber(unsigned int number, uint8_t lengthNumber);

public:
  /*
    * Constructor
    * 
    */
  Max_7219_7segment(uint8_t csPin);

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
  void displayNumber(unsigned int number1, uint8_t lengthNumber1, unsigned int number2, uint8_t lengthNumber2);

  /*
    *
    * 
    */
  void displayFloat(float number, uint8_t precision);

  /*
    *
    * 
    */
  void displayFloat(float number1, uint8_t precision1, uint8_t lengthNumber1, float number2, uint8_t precision2, uint8_t lengthNumber2);

  /*
    *
    * 
    */
  void cleanDisplay();
};

#endif
