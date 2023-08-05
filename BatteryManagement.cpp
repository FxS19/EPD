#include "BatteryManagement.h"
#include "HardwareSerial.h"
#include <math.h> 

double BatteryManagement::readRaw(){
  // read analog and make it more linear
  double reading = analogRead(VOLT_PIN);
  for (int i = 0; i < 10; i++) {
    reading = (analogRead(VOLT_PIN) + reading * 9) / 10;
  }
  if (reading < 1 || reading > 4095) return 0;
  return -0.000000000000016 * pow(reading, 4) + 0.000000000118171 * pow(reading, 3) - 0.000000301211691 * pow(reading, 2) + 0.001109019271794 * reading + 0.034143524634089;
}

double BatteryManagement::convertToVoltage(double value){
  return (HIGH_RESISTOR + LOW_RESISTOR) / LOW_RESISTOR  * value + VOLT_OFFSET;
}

double BatteryManagement::voltToPercentage(double voltage) {
  if (voltage < 3.30) return 0;
  double percentage = ((voltage - 3.30 )/0.9);
  if (percentage > 1) percentage = 1;
  if (percentage < 0) percentage = 0;
  Serial.print("Battery: ");
  Serial.print(percentage * 100);
  Serial.println("%");
  return percentage;
}

void BatteryManagement::Update(){
  this->voltage = convertToVoltage(readRaw());
  this->percentage = voltToPercentage(this->voltage);
}