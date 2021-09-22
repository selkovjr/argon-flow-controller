#include "Display.h"

// The display variable needs to be global because it is hard-coded into TcMenu
// (by TcMenu Designer, see flow-controller-menu.emf)

// Pin assignments are in Display.h

// Software SPI mode (slow)
// Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

// Hardware SPI using SPIClass
Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
  char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
  return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}

bool is_blank[256];

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
    for (int i = 0; i < 256; i++) {
      if (sprite[i].index) {
        display.drawRGBBitmap(sprite[i].x, sprite[i].y, sprite_bitmap[sprite[i].index], 8, 8);
      }
    }
  }

  void draw(char *msg) {
    display.setTextColor(BLACK);
    display.setCursor(80, 2);
    // display.print(count);
    // display.setCursor(0, 40);
    display.print(buf);

    display.setTextColor(YELLOW);
    display.setCursor(80, 2);
    // display.print(++count);
    // display.setCursor(0, 40);

    sprintf(msg, "m: %d", freeMemory());
    //display.print(msg);
    strcpy(buf, msg);
  }
}
