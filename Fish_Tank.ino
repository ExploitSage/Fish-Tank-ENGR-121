#include "Relay.h"
#include "Sensor.h"

Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer;
Sensor thermister;

void setup() {
  heater.init(10, false);
  salt_solenoid.init(11, false);
  fresh_solenoid.init(12, false);
  salinometer.init(0, 255, 767);
  thermister.init(0, 255, 767);
}

void loop() {
  if(!thermister.is_in_tolerance())
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
}
