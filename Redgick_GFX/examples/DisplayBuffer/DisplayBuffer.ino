// uncomment the folling lines following the actual Matrix used
// two modules MAX7219 4 in 1 connected in serial to compose a monochrome 32x16 LED matrix
//#include <Redgick_MatrixMAX72XX.h>
//Redgick_MatrixMAX72XX afficheur;

// Redgick prototype 32x16 white square LEDs
#include <Redgick_MatrixLaboitePro.h>
Redgick_MatrixLaboitePro afficheur;

uint8_t image[64] = {0b00000000, 0b00000000, 0b00000000, 0b00000000, // red LEDs
                     0b01000000, 0b00000000, 0b00000000, 0b00000000,
                     0b01000000, 0b00000000, 0b00000000, 0b00000000,
                     0b01000001, 0b11000000, 0b00000000, 0b00000000,
                     0b01000010, 0b01000000, 0b00000000, 0b00000000,
                     0b01000010, 0b11000000, 0b00000000, 0b00000000,
                     0b01111001, 0b01000000, 0b00000000, 0b00000000,
                     0b00000000, 0b00000000, 0b00000000, 0b00000000,
                     0b00000000, 0b00000000, 0b00000000, 0b00000000,
                     0b01110000, 0b00001000, 0b10000000, 0b00000000,
                     0b01001000, 0b00000001, 0b11000000, 0b00000000,
                     0b01110001, 0b10011000, 0b10000110, 0b00000000,
                     0b01001010, 0b01001000, 0b10001011, 0b00000000,
                     0b01001010, 0b01001000, 0b10001100, 0b00000000,
                     0b01110001, 0b10011100, 0b01100110, 0b00000000,
                     0b00000000, 0b00000000, 0b00000000, 0b00000000,
                    };

void setup() {
  // put your setup code here, to run once:

  afficheur.init();
  afficheur.display(image);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (int i = 0; i < 16; i++) {
    afficheur.intensity(i);
    delay(100);
  }

  delay(1);
}
