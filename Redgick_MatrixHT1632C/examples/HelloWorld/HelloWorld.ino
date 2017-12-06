// Sure-electronics 32x16 RG Dual Color LED Dot Matrix Unit Board
#include <Redgick_MatrixHT1632C.h>
Redgick_MatrixHT1632C afficheur;

// creation of a objet "Screen" which is a buffer to be send to the matrix
Screen image(32, 16, BICOLOR); // with, height, colors);

void setup() {
  // LED Matrix initialization:
  afficheur.init();

  // print some text in the buffer
  image.print(1, 1, "Hello,", FONT_DEFAULT, GREEN);
  image.print(1, 9, "World!.", FONT_DEFAULT, ORANGE);

  // display the buffer on the LED Matrix
  afficheur.display(image.getBuffer());
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1);
}
