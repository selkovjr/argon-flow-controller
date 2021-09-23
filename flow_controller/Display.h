#pragma once

#include "SPI.h"              // Includes library for SPI communication of display
#include "Adafruit_GFX.h"     // Includes core graphics library
#include "Adafruit_SSD1351.h" // Includes hardware specific library
#include <Fonts/FreeSansOblique12pt7b.h>

#include "dial_face.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 128

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

// int freeMemory() {
//   char top;
// #ifdef __arm__
//   return &top - reinterpret_cast<char*>(sbrk(0));
// #elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
//   return &top - __brkval;
// #else  // __arm__
//   return __brkval ? &top - __brkval : &top - __malloc_heap_start;
// #endif  // __arm__
// }

// The only pin assignments that work with hardware SPI on a Mega.
// Other, more intuitive assignments based on pin labels work in the
// "software" SPI mode but not in the hardware mode.
//
#define MOSI_PIN 51 // master-out slave-in SDA pin (11 in Uno)
#define SCLK_PIN 52 // slave clock pin (13 in Uno)
#define CS_PIN   11 // chip select pin (10 in Uno)
#define DC_PIN   10 // master-in slave-out pin (7 in Uno)
#define RST_PIN   8 // reset pin (same as in Uno)

#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF
#define GREY            0x8410
#define ORANGE          0xE880


namespace Display {
  #define CENTER_X 64.5
  #define CENTER_Y 64.5
  #define TILE_SIZE 8

  struct point {float x; float y;};
  struct tile_coord {int x; int y;};

  void setup();
  void draw(char *);
  point rotate_point(point, float);
  uint8_t point_to_tile(uint8_t, uint8_t);
  uint8_t pixel_to_tile(uint8_t);
  void supercover_line(uint8_t, uint8_t, uint8_t, uint8_t);
  void draw_needle(int);
  void drawBackground();
}
