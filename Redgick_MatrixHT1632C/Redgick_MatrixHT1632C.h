/*
  Redgick_MatrixHT1632C.h - Library description ...
*/

// ensure this library description is only included once
#ifndef Redgick_MatrixHT1632C_h
#define Redgick_MatrixHT1632C_h

// uncomment to activate debugging mode
//#define DEBUG 1

// include description files for other libraries used
#include <Redgick_GFX.h>
/*
#if not defined(ESP8266)
  #define uint8 uint8_t
  #define uint16 uint16_t
#endif
*/
// NO-OP Definition
// The HT1632 requires a 1MHz clock.
// The HT1632 requires at least 50 ns between the change in data and the rising
// edge of the WR signal.
// On a 80MHz processor, __asm__("nop\n\t"); provides 12.5ns per NOP.
// On a 16MHz processor, __asm__("nop\n\t"); provides 62.5ns per NOP.
#if defined(ESP8266)
  #define CLK_DELAY; __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t"); __asm__("nop\n\t");
#else
  #define CLK_DELAY; __asm__("nop\n\t");
#endif // defined(ESP8266)

// pin definition

// select microcontroler
#if defined(ARDUINO_AVR_UNO)

  // D7 = Blue = DATA
  #define HT1632_DATA_1     PORTD |= B10000000
  #define HT1632_DATA_0     PORTD &= B01111111
  #define HT1632_DATA(x)    ((x)?HT1632_DATA_1:HT1632_DATA_0)

  // D5 = Green = CS
  #define HT1632_CS_1       PORTD |= B00100000
  #define HT1632_CS_0       PORTD &= B11011111

  // D6 = Yellow = WR
  #define HT1632_WR_1       PORTD |= B01000000
  #define HT1632_WR_0       PORTD &= B10111111

  // D4 = Orange = CLK
  #define HT1632_CLK_1      PORTD |= B00010000
  #define HT1632_CLK_0      PORTD &= B11101111

#elif defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_AVR_ADK)

  // D7 = Blue = DATA
  #define HT1632_DATA_1     PORTH |= B00010000
  #define HT1632_DATA_0     PORTH &= B11101111
  #define HT1632_DATA(x)    ((x)?HT1632_DATA_1:HT1632_DATA_0)

  // D5 = Green = CS
  #define HT1632_CS_1       PORTE |= B00001000
  #define HT1632_CS_0       PORTE &= B11110111

  // D6 = Yellow = WR
  #define HT1632_WR_1       PORTH |= B00001000
  #define HT1632_WR_0       PORTH &= B11110111

  // D4 = Orange = CLK
  #define HT1632_CLK_1      PORTG |= B00100000
  #define HT1632_CLK_0      PORTG &= B11011111

#elif defined(ESP8266)

  // D5 = GPIO14 = Blue = DATA
  #define HT1632_DATA_1     (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<14))
  #define HT1632_DATA_0     (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<14))
  #define HT1632_DATA(x)    ((x)?HT1632_DATA_1:HT1632_DATA_0)

  // D6 = GPIO12 = Green = CS
  #define HT1632_CS_1       (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<12))
  #define HT1632_CS_0       (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<12))

  // D7 = GPIO13 = Yellow = WR
  #define HT1632_WR_1       (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<13))
  #define HT1632_WR_0       (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<13))

  // D8 = GPIO15 = Orange = CLK
  #define HT1632_CLK_1      (GPIO_REG_WRITE(GPIO_OUT_W1TS_ADDRESS, 1<<15))
  #define HT1632_CLK_0      (GPIO_REG_WRITE(GPIO_OUT_W1TC_ADDRESS, 1<<15))

#endif // select microcontroler


//Following definition facilitates compilation of HT1632C control commands.
#define SYS_DIS        0b100000000000 //Turn off both system oscillator and LED duty cycle generator
#define SYS_EN         0b100000000010 //Turn on system oscillator
#define LED_OFF        0b100000000100 //Turn off LED duty cycle generator
#define LED_ON         0b100000000110 //Turn on LED duty cycle generator
#define BLINK_OFF      0b100000010000 //Turn off blinking function
#define BLINK_ON       0b100000010010 //Turn on blinking function
#define SLAVE_MODE     0b100000100000 // Set slave mode and clock source from external clock
#define MASTER_MODE    0b100000101000 // Set master mode and clock source on-chip RC oscillator, the system clock output to OSC pin
#define RC_MASTER_MODE 0b100000110000 // System clock source, on-chip RC oscillator
#define EXT_CLK        0b100000111000 // System clock source, external clock source

#define N_MOS_COM8     0b100001000000 //N-MOS open drain output and 8 common option
#define N_MOS_COM16    0b100001001000 //N-MOS open drain output and 16 common option
#define P_MOS_COM8     0b100001010000 //P-MOS open drain output and 8 common option
#define P_MOS_COM16    0b100001011000 //P-MOS open drain output and 16 common option

#define PWM_1          0b100101000000 //PWM 1/16 duty
#define PWM_2          0b100101000010 //PWM 2/16 duty
#define PWM_3          0b100101000100 //PWM 3/16 duty
#define PWM_4          0b100101000110 //PWM 4/16 duty
#define PWM_5          0b100101001000 //PWM 5/16 duty
#define PWM_6          0b100101001010 //PWM 6/16 duty
#define PWM_7          0b100101001100 //PWM 7/16 duty
#define PWM_8          0b100101001110 //PWM 8/16 duty
#define PWM_9          0b100101010000 //PWM 9/16 duty
#define PWM_10         0b100101010010 //PWM 10/16 duty
#define PWM_11         0b100101010100 //PWM 11/16 duty
#define PWM_12         0b100101010110 //PWM 12/16 duty
#define PWM_13         0b100101011000 //PWM 13/16 duty
#define PWM_14         0b100101011010 //PWM 14/16 duty
#define PWM_15         0b100101011100 //PWM 15/16 duty
#define PWM_16         0b100101011110 //PWM 16/16 duty

// library interface description
class Redgick_MatrixHT1632C {
  // user-accessible "public" interface
  public:
    Redgick_MatrixHT1632C(void);

    void init();
    void intensity(uint8_t value);
    void clear();
    //void test();
    void display(uint8_t * buffer128);

  // library-accessible "private" interface
  private:
    void begin();
    void selectAll();
    void selectNone();
    void commandWrite(uint16_t command);
    void dataWrite(uint8_t * buffer128);

    uint16_t intentity_value = PWM_1;
};

#endif
