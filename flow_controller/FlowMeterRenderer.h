#include <BaseRenderers.h>
#include "flow_controller_menu.h"

// https://www.thecoderscorner.com/products/arduino-libraries/tc-menu/renderer-take-over-display

class FlowMeterRenderer : public CustomDrawing {
  public:
    virtual ~FlowMeterRenderer() = default;

    void reset() override {
      // if we get here the display has been reset because
      // of a timeout of the user interface for example to
      // take over the display
      Display::drawBackground();
      Display::draw_needle(0);  // fetch the current value
      renderer.takeOverDisplay();
      switches.changeEncoderPrecision(80, 0);
    }

    void started(BaseMenuRenderer* currentRenderer) override {
      // take over display has just been called, and we
      // now need to do any initial activity
      // for example here we may clear the display and
      // print the title
      //
      // Not running drawBackground() here results in
      // menu rendering itself on top or pre-existing background.
      Display::drawBackground();
      Display::draw_needle(0);  // fetch the current value
    }

    void renderLoop(unsigned int encoderValue, RenderPressMode userClick) override {
      // At this point clicked is the status of the select button
      // it can be RPRESS_NONE, RPRESS_PRESSED or RPRESS_HELD
      // encoderValue is the current value of the rotary encoder
      // for example to exit when the user clicks
      // if(userClick) renderer.giveBackDisplay();
      // for example to update a menu based on current value of the encoder.
      // don't forget you could call changePrecision in started(..)
      // menuAnalogToAlter.setCurrentValue(encoderValue);
      char buf[50];

      if (userClick == 1) {
        renderer.giveBackDisplay();
      }
      else if (userClick == 2) {
        sprintf(buf, "alarm: %d\n", encoderValue);
        Display::renderText(buf);
      }
      else {
        sprintf(buf, "sp: %d\n", encoderValue);
        Display::renderText(buf);
        Display::draw_needle(encoderValue);
      }
    }
} flowMeterRenderer;
