// include Arduino core library
#include "Arduino.h"

// include this library's description file
#include "Redgick_GFX.h"

// include description files for other libraries used
#include <fonts.h>

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

Screen::Screen(uint8_t width, uint8_t height, uint8_t color_channels) {
  this->width = width;
  this->height = height;
  this->color_channels = color_channels;
  this->buffer_lenght = width * height * color_channels / 8 ;
  this->buffer = malloc(sizeof(uint8_t) * buffer_lenght);
};

// Public Methods //////////////////////////////////////////////////////////////
// Functions available in Redgick_GFX sketches, this library, and other libraries

Bitmap Font::getBitmap(char c) {
  if (c < min || c > max) {
    c = unknown;
  }
  return characters[c - min];
};

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

  // on commence par éteindre le pixel sur tous les canaux
  for (uint8_t channel = 0 ; channel < color_channels ; channel++) {
    if ( ( color & ( 0b0000001 << channel ) ) >> channel ) {
      // on allume le canal
      buffer[(x / 8) + (y * (width / 8) ) + (offset * channel)] = buffer[(x / 8) + (y * (width / 8)) + (offset * channel)] | (0b10000000 >> (x % 8));
    }
    else {
      // on éteint le canal
      buffer[(x / 8) + (y * (width / 8) ) + (offset * channel)] = buffer[(x / 8) + (y * (width / 8)) + (offset * channel)] & ~(0b10000000 >> (x % 8));
    }
  }

};

// Private Methods /////////////////////////////////////////////////////////////
// Functions only available to other functions in this library
