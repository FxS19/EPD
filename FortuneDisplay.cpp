#include "Arduino.h"
#include "DisplayImports.h"
#include "VirtualDisplayClass.h"

class FortuneDisplay : public virtual VirtualDisplayClass {
  private:
    GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * display;
    U8G2_FOR_ADAFRUIT_GFX * u8g2Fonts;
    int x;
    int y;
    int widthX;
    int widthY;
    

  public:
    FortuneDisplay(GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * p_display, 
      U8G2_FOR_ADAFRUIT_GFX * p_u8g2Fonts, 
      int p_x, int p_y, int p_widthX, int p_widthY):
      display(p_display),
      u8g2Fonts(p_u8g2Fonts),
      x(p_x),
      y(p_y),
      widthX(p_widthX),
      widthY(p_widthY) {
        //empty
    }

    bool Draw() override {
      u8g2Fonts->setFont(u8g2_font_helvR14_tf);
      u8g2Fonts->setCursor(x, y + 14);                          // start writing at this position
      u8g2Fonts->print("Hello World!");
      return true;
    }

};