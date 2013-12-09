#include "Relay.h"
#include "Salinometer.h"
#include "Thermister.h"

Relay heater, salt_solenoid, fresh_solenoid;
Salinometer salinometer;
Thermister thermister;

bool state = false;

void setup() {
  heater.init(11, false);
  salt_solenoid.init(12, false);
  fresh_solenoid.init(12, false);
  salinometer.init(0, 255, 767);
  thermister.init(0, 255, 767);
}

void loop() {
  heater.set(state);
  state = !state;
  delay(1000);
  
  if(!salinometer.is_in_tolerance()) {
    
  }
  if(!thermister.is_in_tolerance()) {
    
  }
}
