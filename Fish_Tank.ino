#include "Relay.h"
#include "Salinometer.h"

Relay heater, salt_solenoid, fresh_solenoid;
bool state = false;
void setup() {
  heater.init(11, false);
  salt_solenoid.init(12, false);
  fresh_solenoid.init(12, false);
}

void loop() {
  heater.set(state);
  state = !state;
  delay(1000);
}
