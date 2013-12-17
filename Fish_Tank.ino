#include "Relay.h"
#include "Sensor.h"
#include "LCD.h"
#include <SoftwareSerial.h> //For LCD

Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer;
Sensor thermister;
LCD lcd;

void setup() {
  salt_solenoid.init(12, false);      //Digital Pin 12
  fresh_solenoid.init(11, false);     //Digital Pin 11
  heater.init(10, false);             //Digital Pin 10
  lcd.init(0,2);                      //Digital Pin 02
  salinometer.init(1, A0, 300, 750);  //Analog  Pin 01
                                      //Digital Pin A0
  thermister.init(2, 400, 650);       //Analog  Pin 02
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
