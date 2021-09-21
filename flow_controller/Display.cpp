#include "Display.h"

// The display variable needs to be global because it is hard-coded into TcMenu
// (by TcMenu Designer, see flow-controller-menu.emf)

// Pin assignments are in Display.h

// Software SPI mode (slow)
// Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

// Hardware SPI using SPIClass
Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);
ustd::map<uint8_t, const uint16_t(*)[64]> sprite;


namespace Display {
  char buf[50];
  unsigned long count = 0;

  void drawBackground ();

  void setup() {
    sprite[7] = &dial_face_7;
    sprite[8] = &dial_face_8;
    sprite[23] = &dial_face_23;
    sprite[24] = &dial_face_24;
    sprite[38] = &dial_face_38;
    sprite[39] = &dial_face_39;
    sprite[40] = &dial_face_40;
    sprite[41] = &dial_face_41;
    sprite[51] = &dial_face_51;
    sprite[52] = &dial_face_52;
    sprite[53] = &dial_face_53;
    sprite[54] = &dial_face_54;
    sprite[55] = &dial_face_55;
    sprite[56] = &dial_face_56;
    sprite[57] = &dial_face_57;
    sprite[58] = &dial_face_58;
    sprite[59] = &dial_face_59;
    sprite[60] = &dial_face_60;
    sprite[67] = &dial_face_67;
    sprite[68] = &dial_face_68;
    sprite[69] = &dial_face_69;
    sprite[70] = &dial_face_70;
    sprite[71] = &dial_face_71;
    sprite[72] = &dial_face_72;
    sprite[74] = &dial_face_74;
    sprite[75] = &dial_face_75;
    sprite[76] = &dial_face_76;
    sprite[81] = &dial_face_81;
    sprite[83] = &dial_face_83;
    sprite[84] = &dial_face_84;
    sprite[86] = &dial_face_86;
    sprite[87] = &dial_face_87;
    sprite[88] = &dial_face_88;
    sprite[89] = &dial_face_89;
    sprite[90] = &dial_face_90;
    sprite[91] = &dial_face_91;
    sprite[92] = &dial_face_92;
    sprite[93] = &dial_face_93;
    sprite[94] = &dial_face_94;
    sprite[95] = &dial_face_95;
    sprite[97] = &dial_face_97;
    sprite[98] = &dial_face_98;
    sprite[99] = &dial_face_99;

    memset(buf, 0, sizeof(buf));

    // display.setFont(&FreeSansOblique12pt7b);  // tc-menu sets the font it likes
    display.begin();
    display.setRotation(2);
    drawBackground();
  }

  void drawBackground () {
    display.fillScreen(BLACK);
    display.drawRGBBitmap(48, 0, *sprite[7], 8, 8);
    display.drawRGBBitmap(56, 0, *sprite[8], 8, 8);
    display.drawRGBBitmap(48, 8, *sprite[23], 8, 8);
    display.drawRGBBitmap(56, 8, *sprite[24], 8, 8);
    display.drawRGBBitmap(40, 16, *sprite[38], 8, 8);
    display.drawRGBBitmap(48, 16, *sprite[39], 8, 8);
    display.drawRGBBitmap(56, 16, *sprite[40], 8, 8);
    display.drawRGBBitmap(64, 16, *sprite[41], 8, 8);
    display.drawRGBBitmap(16, 24, *sprite[51], 8, 8);
    display.drawRGBBitmap(24, 24, *sprite[52], 8, 8);
    display.drawRGBBitmap(32, 24, *sprite[53], 8, 8);
    display.drawRGBBitmap(40, 24, *sprite[54], 8, 8);
    display.drawRGBBitmap(48, 24, *sprite[55], 8, 8);
    display.drawRGBBitmap(56, 24, *sprite[56], 8, 8);
    display.drawRGBBitmap(64, 24, *sprite[57], 8, 8);
    display.drawRGBBitmap(72, 24, *sprite[58], 8, 8);
    display.drawRGBBitmap(80, 24, *sprite[59], 8, 8);
    display.drawRGBBitmap(88, 24, *sprite[60], 8, 8);
    display.drawRGBBitmap(16, 32, *sprite[67], 8, 8);
    display.drawRGBBitmap(24, 32, *sprite[68], 8, 8);
    display.drawRGBBitmap(32, 32, *sprite[69], 8, 8);
    display.drawRGBBitmap(40, 32, *sprite[70], 8, 8);
    display.drawRGBBitmap(48, 32, *sprite[71], 8, 8);
    display.drawRGBBitmap(56, 32, *sprite[72], 8, 8);
  }

  void draw(char *msg) {
    display.setTextColor(BLACK);
    display.setCursor(68, 2);
    // display.print(count);
    // display.setCursor(0, 40);
    display.print(buf);

    display.setTextColor(YELLOW);
    display.setCursor(68, 2);
    // display.print(++count);
    // display.setCursor(0, 40);
    sprintf(msg, "%d", freeMemory());
    display.print(msg);
    strcpy(buf, msg);
  }
}
