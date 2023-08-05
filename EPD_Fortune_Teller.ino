#define LILYGO_T5_V213
#include "boards.h"
#include "DisplayImports.h"
#include "BatteryDisplay.cpp"
#include "MessageDisplay.cpp"
#include "FortuneDisplay.cpp"
#include "Powermanagement.cpp"
#include "BatteryManagement.h"
#include <SD.h>
#include <FS.h>
#include <SPIFFS.h>

GxEPD2_BW<GxEPD2_213_M21, GxEPD2_213_M21::HEIGHT> display(GxEPD2_213_M21(/*CS=15*/ EPD_CS, /*DC=4*/ EPD_DC, /*RST=5*/ EPD_RSET, /*BUSY=16*/ EPD_BUSY)); // GDEW0213M21
U8G2_FOR_ADAFRUIT_GFX u8g2Fonts;
SPIClass SDSPI(HSPI);
BatteryManagement batteryManagement;

void setup() {
  batteryManagement.Update();
  if(batteryManagement.percentage == 0){
    Powermanagement powerManagement = Powermanagement(&display);
    powerManagement.Powerdown(500);
  }

  Serial.begin(115200);
  SPI.begin(EPD_SCLK, EPD_MISO, EPD_MOSI);
  setupDisplay();
  setupU8g2();

  if(!SPIFFS.begin(true)){
    Serial.println("An Error has occurred while mounting SPIFFS");
    auto messageDisplay = MessageDisplay(&display, &u8g2Fonts, F("Internal filesystem corrupted"), 40, 45);
    UpdateDisplay([&](){
      messageDisplay.Draw();
    });
    return;
  }

  if (esp_sleep_get_wakeup_cause() != ESP_SLEEP_WAKEUP_TIMER) {
    auto messageDisplay = MessageDisplay(&display, &u8g2Fonts, F("Booting..."), 40, 45);
    UpdateDisplay([&](){
      messageDisplay.Draw();
    });
    if (setupSD()){
      auto messageDisplay = MessageDisplay(&display, &u8g2Fonts, F("SD detected... Updating"), 40, 45);
      UpdateDisplay([&](){
        messageDisplay.Draw();
      });
      // MessageDisplay errDisplay = MessageDisplay(&display, &u8g2Fonts, F("Keine SD-Karte"), 40, 45);
      // Powermanagement powerManagement = Powermanagement(&display);
      // BatteryDisplay batteryDisplay = BatteryDisplay(&batteryManagement, &display, display.width() - 17, display.height() - 9);
      // errDisplay.Draw();
      // batteryDisplay.Draw();
      // display.update();
      // powerManagement.Powerdown();
      SD.end();
    }
  }
}

void setupDisplay(){
  display.init();
  display.setRotation(1);
  display.setFullWindow();
}

bool setupSD(){
  pinMode(SDCARD_MISO, INPUT_PULLUP);
  SDSPI.begin(SDCARD_SCLK, SDCARD_MISO, SDCARD_MOSI);
  return SD.begin(SDCARD_CS, SDSPI);
}

void setupU8g2(){
  u8g2Fonts.begin(display);
  u8g2Fonts.setFontMode(1);                           // use u8g2 transparent mode (this is default)
  u8g2Fonts.setFontDirection(0);                      // left to right (this is default)
  u8g2Fonts.setForegroundColor(GxEPD_BLACK);          // apply Adafruit GFX color
  u8g2Fonts.setBackgroundColor(GxEPD_WHITE);          // apply Adafruit GFX color
}

void loop() {
  Powermanagement powerManagement = Powermanagement(&display);

  batteryManagement.Update();
  if (batteryManagement.percentage < 0.02){
    auto messageDisplay = MessageDisplay(&display, &u8g2Fonts, F("Akku leer :("), 40, 45);
    UpdateDisplay([&](){
      display.fillScreen(GxEPD_WHITE);
      messageDisplay.Draw();
    });
    powerManagement.Powerdown();
  }

  auto fortuneDisplay = FortuneDisplay(&display, &u8g2Fonts, 1, 1, 0, 0);
  auto batteryDisplay = BatteryDisplay(&batteryManagement, &display, display.width() - 17, display.height() - 9);
  
  UpdateDisplay([&](){
    display.fillScreen(GxEPD_WHITE);
    fortuneDisplay.Draw();
    batteryDisplay.Draw();
  });
  powerManagement.Powerdown();
}

template<typename Functor>
void UpdateDisplay(Functor functor)
{
  display.firstPage();
  do {
    functor();
  } while (display.nextPage());
}
