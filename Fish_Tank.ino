#include "Relay.h"
#include "Salinometer.h"
#include "Thermister.h"

Relay heater, salt_solenoid, fresh_solenoid;
Salinometer salinometer;
Thermister thermister;

void setup() {
  heater.init(10, false);
  salt_solenoid.init(11, false);
  fresh_solenoid.init(12, false);
  salinometer.init(0, 255, 767);
  thermister.init(0, 255, 767);
}

void loop() {
  heater.set(!heater.get());
  delay(50);
  salt_solenoid.set(!salt_solenoid.get());
  delay(50);
  fresh_solenoid.set(!fresh_solenoid.get());
  delay(100);
  fresh_solenoid.set(!fresh_solenoid.get());
  delay(50);
  salt_solenoid.set(!salt_solenoid.get());
  delay(50);
  heater.set(!heater.get());
  delay(500);
}
