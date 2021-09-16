#include "Display.h"

// Software SPI mode (slow)
// Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

// Hardware SPI using SPIClass
Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

namespace Display {

  void setup() {
    display.setFont(&FreeSansOblique12pt7b);
    display.begin();
    display.setRotation(2);
    display.fillScreen(BLACK);
  }

  void draw() {
    display.setTextColor(YELLOW);
    display.setCursor(10, 30);
    display.print("hello ");
    display.println("there");

    display.drawRGBBitmap(40, 50, face_icon, 48, 48);
  }
}
