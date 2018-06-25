/*
  Redgick_GFX.h

  Cette bibliothèque a pour but de proposer une interface commune de génération
  de buffers pour ensuite aller les transférer sur n'importe quel afficheur
  matriciel.
  Cette bibliothèque doit permettre également de générer les transitions.

  Un buffer est constitué d'un tableau d'octets (8 bits).
  Chaque octet représente une ligne horizontale de 8 pixels.
  Les octets s'enchaînent de telle sorte que l'image est décrite à partir du
  pixel en haut à gauche, puis ligne par ligne.
  Pour une image en quatre couleurs (ex. : noir, rouge, vert, jaune), le buffer
  contient l'information de l'ensemble de l'image pour la première couleur
  (ex. : rouge) puis l'ensemble de l'image pour la seconde couleur (ex. : verte).
  De même, pour une image en huit couleur, le buffer contient à la suite
  l'information pour l'image Rouge, puis Verte et enfin Bleue.
*/

// ensure this library description is only included once
#ifndef Redgick_GFX_h
#define Redgick_GFX_h

// uncomment to activate debugging mode
//#define DEBUG 1

// include description files for other libraries used

// pour utiliser PROGMEM
#ifdef __AVR__
 #include <avr/pgmspace.h>
#elif defined(ESP8266)
 #include <pgmspace.h>
#else
 #define PROGMEM
#endif

// font definition
#define FONT_DEFAULT 1
#define FONT_5X7     1
#define FONT_4X6     2

// color depth
#define MONOCHROME 1
#define BICOLOR    2
#define RGB        3

// color definition
#define BLACK   0
#define RED     1
#define GREEN   2
#define YELLOW  3
#define ORANGE  3 // on the bicolor matrix, yellow looks like orange !
#define BLUE    4
#define MAGENTA 5
#define CYAN    6
#define WHITE   7

// library interface description
class Bitmap {
  public:
    Bitmap(uint8_t width, uint8_t height, String raw);

  //private:
    uint8_t width;
    uint8_t height;
    String raw;
};

class Font {
  public:
    Font(uint8_t min, uint8_t max, uint8_t unknown, Bitmap* characters);
    Bitmap getBitmap(char c);

  //private:
    uint8_t min;
    uint8_t max;
    uint8_t unknown;
    Bitmap* characters = NULL;
};

class Screen {
  // user-accessible "public" interface
  public:
    Screen();
    Screen(uint8_t width, uint8_t height, uint8_t color_channels);
    void init(uint8_t width, uint8_t height, uint8_t color_channels);
    void clear();
    uint8_t* getBuffer();
    void setPixel(uint16_t x, uint16_t y, uint8_t color);
    void drawBitmap(uint16_t x, uint16_t y, Bitmap bitmap, uint8_t color);
    void print(uint16_t x, uint16_t y, String s, uint8_t font_name, uint8_t color);
    void print(uint16_t x, uint16_t y, String s) { print(x, y, s, FONT_DEFAULT, RED); };

  // library-accessible "private" interface
  private:

#ifdef __AVR__
    uint8_t* buffer = NULL; // pointeur qui peut contenir l'adresse du premier élément du tableau buffer créé en même temps que l'instance de la classe
#elif defined(ESP8266)
    uint8_t buffer[128];
#endif

    uint16_t buffer_lenght = 0;
    uint8_t width = 0;
    uint8_t height = 0;
    uint8_t color_channels = 0;

    void print(uint16_t x, uint16_t y, char c, Font* font, uint8_t color);
};

#endif
