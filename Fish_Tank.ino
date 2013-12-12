#include "Relay.h"
#include "Sensor.h"
#include "LCD.h"
#include <SoftwareSerial.h> //For LCD

Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer;
Sensor thermister;
LCD lcd;

void setup() {
  salt_solenoid.init(A0, false);
  fresh_solenoid.init(A1, false);
  heater.init(A2, false);
  lcd.init(0,A3);
  salinometer.init(4, 300, 750);
  thermister.init(5, 400, 650);
}

void loop() {
  if(thermister.is_low())
    heater.set(true);
  else
    heater.set(false);
  
  if(salinometer.is_high()) {
    salt_solenoid.set(false);
    fresh_solenoid.set(true);
  } else if(salinometer.is_low()) {
    salt_solenoid.set(true);
    fresh_solenoid.set(false);
  } else {
    salt_solenoid.set(false);
    fresh_solenoid.set(false);
  }
  
  //float salt_content = salinity(salinometer.get_value());
  //float temp = tempurature(thermister.get_value());
  float salt_content = salinometer.get_value();
  float temp = thermister.get_value();
  lcd.setup();
  lcd.update(salt_content, temp, heater.get());
  delay(100);
}

float salinity(uint16_t salt) {
  return 0.0f;
}

float tempurature(uint16_t temp) {
  return 0.0f;
}
