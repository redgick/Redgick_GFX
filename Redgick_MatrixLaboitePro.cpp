// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "Redgick_MatrixLaboitePro.h"

// include description files for other libraries used
#include <Redgick_GFX.h>

// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances
Redgick_MatrixLaboitePro::Redgick_MatrixLaboitePro(void) {

}

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Redgick_MatrixLaboitePro sketches, this library, and other libraries

void Redgick_MatrixLaboitePro::init() {
  pinMode(pinMOSI, OUTPUT);
  digitalWrite(pinMOSI, LOW);

  pinMode(pinCS1, OUTPUT);
  digitalWrite(pinCS1, HIGH);

  pinMode(pinCS2, OUTPUT);
  digitalWrite(pinCS2, HIGH);

  pinMode(pinCLK, OUTPUT);
  digitalWrite(pinCLK, LOW);

  commandAll(DECODE_MODE, NO_DECODE);
  commandAll(INTENSITY, INTENSITY_MIN);
  commandAll(SCAN_LIMIT, DISPLAY_ALL_DIGITS);
  commandAll(SHUTDOWN, NORMAL_OPERATION);
  commandAll(DISPLAY_TEST, DISPLAY_TEST_NORMAL_OPERATION);
  clear();
}

void Redgick_MatrixLaboitePro::intensity(uint8_t value) {
  // value between 0 and 15
  if (value > 15) {
    value = 15;
  }
  commandAll(INTENSITY, value);
}

void Redgick_MatrixLaboitePro::clear() {
  for (uint8_t digit = 1; digit < 9; digit++) {
    commandAll(digit, 0);
  }
}

void Redgick_MatrixLaboitePro::test() {
  while(1) {
    for (uint8_t digit = 1; digit < 9; digit++) {
      commandAll(digit, 0b10101010);
    }
    delay(1000);
    for (uint8_t digit = 1; digit < 9; digit++) {
      commandAll(digit, 0b01010101);
    }
    delay(1000);
  }
}

void Redgick_MatrixLaboitePro::display(uint8_t * buffer64) {
  for (uint8_t digit = 1; digit < 9; digit++) {
    MAX72XX_CS1_0;
    for (uint8_t driver = 4; driver > 0; driver--) {
      //sendDigit(digit, (digit-1) + ((driver-1)<<4));
      uint8_t colonne = 0;
      for (uint8_t segment = 0; segment < 8; segment ++) {
        //colonne += (buffer64[segment*4 + (driver-1)] & (1 << 7)) >> segment;
        uint8_t pixel = (buffer64[segment*4 + (driver-1)] & (1 << (8-digit))) >> (8-digit);
        colonne += pixel << segment;
      }
      sendDigit(digit, colonne);
    }
    MAX72XX_CS1_1;
  }
  for (uint8_t digit = 1; digit < 9; digit++) {
    MAX72XX_CS2_0;
    for (uint8_t driver = 4; driver > 0; driver--) {
      //sendDigit(digit, (digit-1) + ((driver-1)<<4));
      uint8_t colonne = 0;
      for (uint8_t segment = 0; segment < 8; segment ++) {
        //colonne += (buffer64[segment*4 + (driver-1)] & (1 << 7)) >> segment;
        uint8_t pixel = (buffer64[segment*4 + (driver-1) + 32] & (1 << (8-digit))) >> (8-digit);
        colonne += pixel << segment;
      }
      sendDigit(digit, colonne);
    }
    MAX72XX_CS2_1;
  }
}

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void Redgick_MatrixLaboitePro::shiftMSBFirst(uint8_t data) {
  uint8_t k;
  for (uint8_t j = 0; j < 8; j++) {
    k = data & 0x80;  // return the MSB
    data = data << 1; // move the control character to the left one
    k = k >> 7;       // position the value at the LSB
    MAX72XX_CLK_0;
    MAX72XX_DATA(k);  // send the value to the data port
    CLK_DELAY;

    MAX72XX_CLK_1;    // clock pulse
    CLK_DELAY;
  }
}

void Redgick_MatrixLaboitePro::shiftLSBFirst(uint8_t data) {
  uint8_t k;
  for (uint8_t j = 0; j < 8; j++) {
    k = data & 0x01;  // return the LSB
    data = data >> 1; // move the control character to the right one
    MAX72XX_CLK_0;
    MAX72XX_DATA(k);  // send the value to the data port
    CLK_DELAY;

    MAX72XX_CLK_1;    // clock pulse
    CLK_DELAY;
  }
}

void Redgick_MatrixLaboitePro::command(uint8_t address, uint8_t data) {
  shiftMSBFirst(address);
  shiftMSBFirst(data);
}

void Redgick_MatrixLaboitePro::commandAll(uint8_t address, uint8_t data) {
  MAX72XX_CS1_0;
  MAX72XX_CS2_0;

  for (uint8_t i = 0; i < 4; i++) {
    command(address, data);
  }

  MAX72XX_CS1_1;
  MAX72XX_CS2_1;
}

void Redgick_MatrixLaboitePro::sendDigit(uint8_t digit, uint8_t data) {
  shiftMSBFirst(digit);
  shiftLSBFirst(data);
}
