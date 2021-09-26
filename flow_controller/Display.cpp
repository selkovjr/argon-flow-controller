#include "Display.h"

// The display variable needs to be global because it is hard-coded into TcMenu
// (by TcMenu Designer, see flow-controller-menu.emf)

// Pin assignments are in Display.h

// Software SPI mode (slow)
// Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, CS_PIN, DC_PIN, MOSI_PIN, SCLK_PIN, RST_PIN);

// Hardware SPI using SPIClass
Adafruit_SSD1351 display = Adafruit_SSD1351(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, CS_PIN, DC_PIN, RST_PIN);

namespace Display {
  char buf[50];
  char global_msg[50];
  bool tile[256];
  int16_t previous_value = -1;  // to ensure the needle is rendered the first time

  unsigned long count = 0;

  void setup() {
    memset(tile, 0, sizeof(tile));
    memset(buf, 0, sizeof(buf));

    // display.setFont(&FreeSansOblique12pt7b);  // tc-menu sets the font it likes
    display.begin();
    display.setRotation(2);
    // drawBackground();
  }

  void drawBackground () {
    display.fillScreen(BLACK);
    for (int i = 0; i < 256; i++) {
      if (sprite[i].index) {
        display.drawRGBBitmap(
          sprite[i].x,
          sprite[i].y,
          sprite_bitmap[sprite[i].index],
          TILE_SIZE,
          TILE_SIZE
        );
      }
    }

    display.drawRGBBitmap(86, 1, trigger_state_t4p1, 45, 16);
    // display.drawLine(0, 0, 0, 127, RED);
    // display.drawLine(0, 127, 127, 127, RED);
    // display.drawLine(127, 127, 127, 0, RED);
    // display.drawLine(127, 0, 0, 0, RED);
  }

  void renderText(char *msg) {
    display.setTextColor(BLACK);
    display.setCursor(0, 2);
    // display.print(count);
    // display.setCursor(0, 40);
    display.print(buf);

    display.setTextColor(YELLOW);
    display.setCursor(0, 2);
    // display.print(++count);
    // display.setCursor(0, 40);

    // sprintf(msg, "m: %d", freeMemory());
    display.print(msg);
    strcpy(buf, msg);

    // display.print(global_msg);
    // strcpy(buf, global_msg);

  }

  // Draw the dial guage needle pointing at the value supplied. Presently, the
  // value value represents the number of 1/80th steps on the dial.
  //
  // This function runs 25 .. 35ms, depending on the previous and current
  // position of the needle.
  //
  void draw_needle(int value) {

    if (value == previous_value) {
      return;
    }

    // The outer radius of the scale is 43
    int outer_radius = 45;
    int inner_radius = 11;

    // The needle is rendered as three parallel lines
    static uint8_t offest[3] = {-1, 0, 1};

    // Not sure we want the point object. It may be wasteful
    point start, end;


    // The needle previously pointed at this angle
    float angle = (2 * 3.14159 / 360) * (120 + 300 * previous_value / 80);  // 300: angular scale size; 80; number of steps

    // reset sprite index
    memset(tile, 0, sizeof(tile));

    // Compute needle co-ordinates by imagining three horizontal lines drawn at
    // 0° one pixel apart from each other and rotating their ends. We have to
    // use three lines because the Adafruit graphics library offers no way to
    // control line thickness. It does not transform primitives either, so
    // we're doing our own rotation.
    //
    // For collision detection with supercover_line(), two lines spaced so that
    // they encompass the three lines to be drawn are enough. These imaginary
    // lines are extended 3px inward and are spaced 2px wider to cover for
    // occasional false negatives due to rounding errors. This arrangement
    // guarantees that the four central sprites are always redrawn.
    //
    start = rotate_point({FG_CENTER_X + inner_radius - 3, FG_CENTER_Y - 2}, angle);
    end = rotate_point({FG_CENTER_X + outer_radius + 1, FG_CENTER_Y - 2}, angle);
    supercover_line(start.x, start.y, end.x, end.y);

    start = rotate_point({FG_CENTER_X + inner_radius - 3, FG_CENTER_Y + 2}, angle);
    end = rotate_point({FG_CENTER_X + outer_radius + 1, FG_CENTER_Y + 2}, angle);
    supercover_line(start.x, start.y, end.x, end.y);

    /* 2ms from the start of the function */

    // Re-render sprites touched by the needle in previous position. The ones
    // needing update are marked by a boolean true value in the tile[] array.
    //
    // With 8x8 tiles, 6 .. 12 tiles are updated with each needle rotation.
    // The average number of dirty tiles is 10. It takes 20 .. 30ms to update a
    // typical combination of sprites and blank tiles.
    //
    for (int i = 0; i < 256; i++) {
      if (tile[i]) {  // needs update
        if (sprite[i].index) {  // i-th tile is a sprite
          display.drawRGBBitmap(  /* 2.7 ms */
            sprite[i].x,
            sprite[i].y,
            sprite_bitmap[sprite[i].index],
            TILE_SIZE,
            TILE_SIZE
          );
        }
        else {  // it is a blank tile
          /* 310µs to run this block */
          unsigned long startTime = micros();
          uint16_t x0 = (TILE_SIZE * i) % SCREEN_WIDTH;
          uint16_t y0 = TILE_SIZE * (i / (SCREEN_HEIGHT / TILE_SIZE));
          uint16_t x1 = x0 + TILE_SIZE - 1;
          uint16_t y1 = y0 + TILE_SIZE - 1;
          display.fillRect(x0, y0, TILE_SIZE, TILE_SIZE, BLACK);
          unsigned long elapsed = micros() - startTime;
          sprintf(global_msg, "%d", elapsed);
        }
      }
    }

    // Save the current value and draw the needle.
    previous_value = value;

    // Now the needle points at this angle:
    angle = (2 * 3.14159 / 360) * (120 + 300 * value / 80);  // 300: angular scale size; 80; number of steps

    // Render the needle in current position using three parallel lines for
    // thickness. It takes 5 .. 7ms.
    //
    start = rotate_point({FG_CENTER_X + inner_radius, FG_CENTER_Y - 1}, angle);
    end = rotate_point({FG_CENTER_X + outer_radius, FG_CENTER_Y - 1}, angle);
    display.drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, RED);

    start = rotate_point({FG_CENTER_X + inner_radius, FG_CENTER_Y}, angle);
    end = rotate_point({FG_CENTER_X + outer_radius, FG_CENTER_Y}, angle);
    display.drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, RED);

    start = rotate_point({FG_CENTER_X + inner_radius, FG_CENTER_Y + 1}, angle);
    end = rotate_point({FG_CENTER_X + outer_radius, FG_CENTER_Y + 1}, angle);
    display.drawLine((int)start.x, (int)start.y, (int)end.x, (int)end.y, RED);
  }

  point rotate_point(point p, float angle) {
    float s = sin(angle);
    float c = cos(angle);

    // translate point back to origin:
    p.x -= FG_CENTER_X;
    p.y -= FG_CENTER_Y;

    // rotate point
    float xnew = p.x * c - p.y * s;
    float ynew = p.x * s + p.y * c;

    // translate point back:
    p.x = xnew + FG_CENTER_X;
    p.y = ynew + FG_CENTER_Y;
    return p;
  }

  // after https://www.redblobgames.com/grids/line-drawing.html
  void supercover_line(uint8_t p0x, uint8_t p0y, uint8_t p1x, uint8_t p1y) {
    // This routine can be optimized by converting pixels to tiles and drawing
    // the line over them as if they were pixels. That could easily reduce
    // compute time from 200µs to less than 20µs. However, it will be difficult
    // to appreciate the savings given the 30ms render time of the needle.
    //
    int8_t dx = p1x - p0x, dy = p1y - p0y;
    uint8_t nx = abs(dx), ny = abs(dy);
    int8_t sign_x = dx > 0 ? 1 : -1, sign_y = dy > 0 ? 1 : -1;

    // let p = new Point(p0.x, p0.y); -> (px, py)
    // let points = [new Point(p.x, p.y)]; -> struct tile
    uint8_t px = p0x, py = p0y;
    for (uint8_t ix = 0, iy = 0; ix < nx || iy < ny;) {
      int16_t decision = (1 + 2 * ix) * ny - (1 + 2 * iy) * nx;
      if (decision == 0) {
        // next step is diagonal
        px += sign_x;
        py += sign_y;
        ix++;
        iy++;
      }
      else if (decision < 0) {
        // next step is horizontal
        px += sign_x;
        ix++;
      }
      else {
        // next step is vertical
        py += sign_y;
        iy++;
      }
      //points.push(new Point(p.x, p.y));
      tile[point_to_tile(px, py)] = true;
    }
  }

  uint8_t pixel_to_tile(uint8_t p) {
    return (uint8_t) (p / TILE_SIZE);
  }

  // Ordinal number of the tile containing the point
  uint8_t point_to_tile(uint8_t x, uint8_t y) {
    uint8_t cell_x = (uint8_t) (x / TILE_SIZE);
    uint8_t cell_y = (uint8_t) (y / TILE_SIZE);
    return cell_y * (SCREEN_WIDTH / TILE_SIZE) + cell_x;
  }
}
