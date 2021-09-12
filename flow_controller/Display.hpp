#include "SPI.h"              // Includes library for SPI communication of display
#include "Adafruit_GFX.h"     // Includes core graphics library
#include "Adafruit_SSD1351.h" // Includes hardware specific library

#include "LibPrintf.h"

#include "computer-icon.c"

extern const uint16_t computer_icon[];

// screen dimensions
#define SCREEN_WIDTH 128 //pixel width
#define SCREEN_HEIGHT 128 //pixel height

// pin definitions
#define SCLK_PIN 52 //defines slave clock pin (13 in Uno)
#define MOSI_PIN 51 //defines master-out slave-in SDA pin (11 in Uno)
#define RST_PIN   8 //defines reset pin
#define DC_PIN   50 //defines master-in slave-out pin
#define CS_PIN   21 //defines chip select pin

// Colour definitions
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
  // Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);
  Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

  void setup() {
    display.begin();
    display.setRotation(2);
    display.fillScreen(BLACK);
  }

  void draw() {
    display.drawRGBBitmap(40, 40, computer_icon, 48, 48);
  }
}
