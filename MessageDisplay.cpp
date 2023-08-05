#include "DisplayImports.h"
#include "VirtualDisplayClass.h"

class MessageDisplay : public virtual VirtualDisplayClass {
  private:
    GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * display;
    U8G2_FOR_ADAFRUIT_GFX * u8g2Fonts;
    int x;
    int y;
    String message;


    // display a string on multiple lines, keeping words intact where possible
    void printwords(const char *msg, int xloc, int yloc) {

      // int dspwidth = u8g2.getDisplayWidth();                        // display width in pixels
      // int strwidth = 0;                         // string width in pixels
      // char glyph[2]; glyph[1] = 0;

      // for (const char *ptr = msg, *lastblank = NULL; *ptr; ++ptr) {
      //     while (xloc == 0 && *msg == ' ')
      //       if (ptr == msg++) ++ptr;                        // skip blanks at the left edge

      //     glyph[0] = *ptr;
          
      //     strwidth += u8g2.getStrWidth(glyph);                        // accumulate the pixel width
      //     if (*ptr == ' ')  lastblank = ptr;                        // remember where the last blank was
      //     else ++strwidth;                        // non-blanks will be separated by one additional pixel

      //     if (xloc + strwidth > dspwidth) {                        // if we ran past the right edge of the display
      //       int starting_xloc = xloc;
      //       while (msg < (lastblank ? lastblank : ptr)) {                        // print to the last blank, or a full line
      //           glyph[0] = *msg++;
      //           xloc += u8g2.drawStr(xloc, yloc, glyph); 
      //       }

      //       strwidth -= xloc - starting_xloc;                        // account for what we printed
      //       yloc += u8g2.getMaxCharHeight();                        // advance to the next line
      //       xloc = 0; lastblank = NULL;
      //     }
      // }
      // while (*msg) {                        // print any characters left over
      //     glyph[0] = *msg++;
      //     xloc += u8g2.drawStr(xloc, yloc, glyph);
      // }
    }
    

  public:
    MessageDisplay(GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * p_display, 
      U8G2_FOR_ADAFRUIT_GFX * p_u8g2Fonts, String p_message, 
      int p_x, int p_y):
      display(p_display),
      u8g2Fonts(p_u8g2Fonts),
      x(p_x),
      y(p_y),
      message(p_message){
        //empty
    }

    bool Draw() override {
      u8g2Fonts->setFont(u8g2_font_helvR14_tf);
      //char buf[message.length()];
      //message.toCharArray(&buf, message.length());
      //printwords(&buf, x, y);
      u8g2Fonts->setCursor(x, y + 14);                          // start writing at this position
      u8g2Fonts->print(message);
      return true;
    }

};