#include "Display.h"

// The display variable needs to be global because it is hard-coded into TcMenu
// (by TcMenu Designer, see flow-controller-menu.emf)

// Pin assignments are in Display.h

// Software SPI mode (slow)
// Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

// Hardware SPI using SPIClass
Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);
int count = 0;

namespace Display {
  char buf[50];
  unsigned long count = 0;

  void drawBackground ();

  void setup() {
    memset(buf, 0, sizeof(buf));

    // display.setFont(&FreeSansOblique12pt7b);  // tc-menu sets the font it likes
    display.begin();
    display.setRotation(2);
    drawBackground();
  }

  void drawBackground () {
    display.fillScreen(BLACK);
    display.drawRGBBitmap(40, 64, face_icon, 48, 48);
  }

  void draw(char *msg) {
    display.setTextColor(BLACK);
    display.setCursor(0, 20);
    display.print(count);
    display.setCursor(0, 40);
    display.print(buf);

    display.setTextColor(YELLOW);
    display.setCursor(0, 20);
    display.print(++count);
    display.setCursor(0, 40);
    display.print(msg);
    strcpy(buf, msg);
  }
}
