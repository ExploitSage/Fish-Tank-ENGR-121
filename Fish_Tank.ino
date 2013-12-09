#include "Relay.h"
#include "Sensor.h"
#include "LCD.h"

Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer;
Sensor thermister;
LCD lcd;

void setup() {
  heater.init(10, false);
  salt_solenoid.init(11, false);
  fresh_solenoid.init(12, false);
  salinometer.init(0, 300, 750);
  thermister.init(1, 400, 650);
  delay(1000);
  lcd.setup();
  lcd.update(0,0,false);
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
  float salt_content = 0;
  float temp = 0;
  //Convert/Display Salt and Temp Data
  
  //lcd.update(salt_content, temp, heater.get());
  delay(100);
}
