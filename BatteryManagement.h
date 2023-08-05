#ifndef BATTERY_MANAGEMENT_H_
#define BATTERY_MANAGEMENT_H_

#define HIGH_RESISTOR 100000
#define LOW_RESISTOR 100000
#define VOLT_PIN 35
#define VOLT_OFFSET 0.08

class BatteryManagement {
  private:
    double readRaw();
    double convertToVoltage(double value);
    double voltToPercentage(double voltage);
  public:
    double percentage {0};
    double voltage {0};
    void Update();
};

#endif