/*
  Redgick_MatrixMAX72XX.h - Library description ...
*/

// ensure this library description is only included once
#ifndef Redgick_MatrixMAX72XX_h
#define Redgick_MatrixMAX72XX_h

// uncomment to activate debugging mode
//#define DEBUG 1

// include description files for other libraries used
#include <Redgick_GFX.h>

// define constants
#define pinMOSI 13
#define pinCS   15
#define pinCLK  14

#define CLK_DELAY         __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t")
#define MAX72XX_CLK_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<14))
#define MAX72XX_CLK_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<14))
#define MAX72XX_CS_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<15))
#define MAX72XX_CS_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<15))
#define MAX72XX_DATA_0    (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<13))
#define MAX72XX_DATA_1    (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<13))
#define MAX72XX_DATA(x)   ((x)?MAX72XX_DATA_1:MAX72XX_DATA_0)

#define CLK_DELAY         __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t")
#define MAX72XX_CLK_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<14))
#define MAX72XX_CLK_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<14))
#define MAX72XX_CS1_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<15))
#define MAX72XX_CS1_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<15))
#define MAX72XX_CS2_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<2))
#define MAX72XX_CS2_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<2))
#define MAX72XX_DATA_0    (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<13))
#define MAX72XX_DATA_1    (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<13))
#define MAX72XX_DATA(x)   ((x)?MAX72XX_DATA_1:MAX72XX_DATA_0)

#define NO_OP 0b00000000

#define DIGIT_0 0b00000001
#define DIGIT_1 0b00000010
#define DIGIT_2 0b00000011
#define DIGIT_3 0b00000100
#define DIGIT_4 0b00000101
#define DIGIT_5 0b00000110
#define DIGIT_6 0b00000111
#define DIGIT_7 0b00001000

#define DECODE_MODE       0b00001001
#define NO_DECODE         0b00000000
#define CODE_B_DIGIT_0    0b00000001
#define CODE_B_DIGITS_1_0 0b00000011
// and so on ...
#define CODE_B_DIGITS_7_0 0b11111111

#define INTENSITY     0b00001010
#define INTENSITY_MIN 0b00000000
#define INTENSITY_1   0b00000000
#define INTENSITY_2   0b00000001
#define INTENSITY_3   0b00000010
#define INTENSITY_4   0b00000011
#define INTENSITY_5   0b00000100
#define INTENSITY_6   0b00000101
#define INTENSITY_7   0b00000110
#define INTENSITY_8   0b00000111
#define INTENSITY_9   0b00001000
#define INTENSITY_10  0b00001001
#define INTENSITY_11  0b00001010
#define INTENSITY_12  0b00001011
#define INTENSITY_13  0b00001100
#define INTENSITY_14  0b00001101
#define INTENSITY_15  0b00001110
#define INTENSITY_16  0b00001111
#define INTENSITY_MAX 0b00001111

#define SCAN_LIMIT         0b00001011
#define DISPLAY_DIGIT_0    0b00000000
#define DISPLAY_DIGITS_0_1 0b00000001
#define DISPLAY_DIGITS_0_2 0b00000010
// and so on ...
#define DISPLAY_ALL_DIGITS 0b00000111

#define SHUTDOWN         0b00001100
#define SHUTDOWN_MODE    0b00000000
#define NORMAL_OPERATION 0b00000001

#define DISPLAY_TEST                  0b00001111
#define DISPLAY_TEST_NORMAL_OPERATION 0b00000000
#define DISPLAY_TEST_MODE             0b00000001

// library interface description
class Redgick_MatrixMAX72XX {
  // user-accessible "public" interface
  public:
    Redgick_MatrixMAX72XX(void);

    void init();
    void intensity(uint8_t value);
    void clear();
    void test();
    void display(uint8_t * buffer64);

  // library-accessible "private" interface
  private:
    void shiftMSBFirst(uint8_t data);
    void shiftLSBFirst(uint8_t data);
    void command(uint8_t address, uint8_t data);
    void commandAll(uint8_t address, uint8_t data);
    void sendDigit(uint8_t digit, uint8_t data);
};

#endif
