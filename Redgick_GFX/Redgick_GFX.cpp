// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "Redgick_GFX.h"

// include description files for other libraries used
#include <fonts.h>
#include <stdlib.h>
// Constructor /////////////////////////////////////////////////////////////////
// Function that handles the creation and setup of instances

Bitmap::Bitmap(uint8_t width, uint8_t height, String raw) {
  this->width = width;
  this->height = height;
  this->raw = raw;
};

Font::Font(uint8_t min, uint8_t max, uint8_t unknown, Bitmap* characters) {
  // attention, aucun buffer n'est initialisé à ce stade !
  this->min = min;
  this->max = max;
  this->unknown = unknown;
  this->characters = characters;
};

Screen::Screen() {

};

Screen::Screen(uint8_t width, uint8_t height, uint8_t color_channels) {
  init(width, height, color_channels);
};

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Redgick_GFX sketches, this library, and other libraries

Bitmap Font::getBitmap(char c) {
  if (c < min || c > max) {
    c = unknown;
  }
  return characters[c - min];
};

void Screen::init(uint8_t width, uint8_t height, uint8_t color_channels) {
  this->width = width;
  this->height = height;
  this->color_channels = color_channels;
  this->buffer_lenght = width * height * color_channels / 8 ;

  #ifdef __AVR__
  this->buffer = malloc(sizeof(uint8_t) * buffer_lenght);
  #endif

  clear();
}

void Screen::clear() {
  for (int i = 0; i < buffer_lenght; i++) {
    buffer[i] = 0b00000000;
  }
};

uint8_t* Screen::getBuffer() {
  return buffer;
};

void Screen::setPixel(uint8_t x, uint8_t y, uint8_t color) {

  if (x >= width or y >= height) {
    // en dehors de l'écran !
    return;
  }

  uint16_t offset = width * height / 8;

  // pour les afficheurs qui n'affichent pas toutes les couleurs (les afficheurs monochromes
  // et bicolors), on utilise le canal le plus élevé pour afficher les couleurs des canaux supérieurs.
  if (color >> color_channels) {
    color = color | ( 0b00000001 << (color_channels - 1) );
  }

  // pour chaque canal de couleur, on allume ou non la led concernée
  for (uint8_t channel = 0 ; channel < color_channels ; channel++) {
    if ( ( color & ( 0b00000001 << channel ) ) >> channel ) {
      // on allume le canal
      buffer[(x / 8) + (y * (width / 8) ) + (offset * channel)] = buffer[(x / 8) + (y * (width / 8)) + (offset * channel)] | (0b10000000 >> (x % 8));
    }
    else {
      // on éteint le canal
      buffer[(x / 8) + (y * (width / 8) ) + (offset * channel)] = buffer[(x / 8) + (y * (width / 8)) + (offset * channel)] & ~(0b10000000 >> (x % 8));
    }
  }

};

void Screen::drawBitmap(uint8_t x, uint8_t y, Bitmap bitmap, uint8_t color) {
  // cette fonction est très moche !
  // elle nécessite d'être réecrite
  int bitIndex = 0;
  int demiOctetIndex = 0;
  int demiOctetOffset = 0;
  int demiOctet = 0;

  for (int j = 0; j < bitmap.height; j++) {
    for (int i = 0; i < bitmap.width; i++) {
      demiOctetIndex = 3 - (bitIndex % 4);
      demiOctetOffset = bitIndex / 4;
      uint8_t masque = 0b00000001;
      char contentChar = bitmap.raw[demiOctetOffset + 2];
      switch (contentChar) {
        case '0':
          demiOctet = 0;
          break;

        case '1':
          demiOctet = 1;
          break;

        case '2':
          demiOctet = 2;
          break;

        case '3':
          demiOctet = 3;
          break;

        case '4':
          demiOctet = 4;
          break;

        case '5':
          demiOctet = 5;
          break;

        case '6':
          demiOctet = 6;
          break;

        case '7':
          demiOctet = 7;
          break;

        case '8':
          demiOctet = 8;
          break;

        case '9':
          demiOctet = 9;
          break;

        case 'a':
          demiOctet = 10;
          break;

        case 'b':
          demiOctet = 11;
          break;

        case 'c':
          demiOctet = 12;
          break;

        case 'd':
          demiOctet = 13;
          break;

        case 'e':
          demiOctet = 14;
          break;

        case 'f':
          demiOctet = 15;
          break;
      }
      if ((demiOctet >> demiOctetIndex) & masque) {
        if (bitmap.raw.length() - 2 > demiOctetOffset) { // bug de l'icone vélo
          setPixel(i + x, j + y, color);
        }
      }
      bitIndex += 1;
    }
  }
};

void Screen::print(uint8_t x, uint8_t y, String s, uint8_t font_name, uint8_t color) {
  int offset = 0;
  for (int i = 0; i < s.length(); i++) {
    switch (font_name) {
      case FONT_4X6:
        print(x + offset, y, s[i], font_4x6, color);
        // on déplace le curseur de la largeur du caractère imprimé
        offset += font_4x6->getBitmap(s[i]).width;
        break;
      case FONT_5X7:
      default:
        print(x + offset, y, s[i], font_5x7, color);
        // on déplace le curseur de la largeur du caractère imprimé
        offset += font_5x7->getBitmap(s[i]).width;
        break;
    }
  }
};

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library

void Screen::print(uint8_t x, uint8_t y, char c, Font * font, uint8_t color) {
  drawBitmap(x, y, font->getBitmap(c), color);
};
