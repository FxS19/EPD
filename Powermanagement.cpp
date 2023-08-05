#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */ 
#define TIME_TO_SLEEP 500 /* Time ESP32 will go to sleep (in seconds) */

#include <SD.h>
#include "DisplayImports.h"

class Powermanagement {
  private:
    GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * display;
  public:
    Powermanagement(GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * p_display):
      display(p_display)
      {
        //empty
      };
    
    void Powerdown(){
      Powerdown(TIME_TO_SLEEP);
    }

    void Powerdown(int seconds) {
      display->hibernate();
      SD.end();
      esp_sleep_enable_timer_wakeup(seconds * uS_TO_S_FACTOR);
      esp_deep_sleep_start();
    }

};