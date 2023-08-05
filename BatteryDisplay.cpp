#define batXSize 16
#define batYSize 8

#include "DisplayImports.h"
#include "VirtualDisplayClass.h"
#include "BatteryManagement.h"

class BatteryDisplay : public virtual VirtualDisplayClass {
  private:
    GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * display;
    BatteryManagement * batteryManagement;

    int batX0;
    int batY0;

  public:
    BatteryDisplay(BatteryManagement * p_batteryManagement, 
      GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> * p_display, 
      int x, int y):
      batteryManagement(p_batteryManagement),
      display(p_display),
      batX0(x),
      batY0(y) {}

    bool Draw() override {
      display->fillRect(batX0, batY0, batXSize - 2, batYSize, GxEPD_BLACK);
      display->fillRect(batX0 + 1, batY0 + 1, batXSize - 4, batYSize - 2, GxEPD_WHITE);
      display->fillRect(batX0 + batXSize - 2, batY0 + (batYSize/2.0)-2, 2, 4, GxEPD_BLACK);
      display->fillRect(batX0 + 1, batY0 + 1, (int)((batXSize - 4) * (double)batteryManagement->percentage + 0.5), batYSize - 2, GxEPD_BLACK);

      return true;
    }

};