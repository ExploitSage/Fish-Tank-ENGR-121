/* 
 * Csp  - NaCl Concentration for the setpoint
 * C1   - Initial NaCl Concentration
 * C1   - Target NaCl Concentration
 * G    - Gain
 * OF   - Fraction of Overflow from DI
 * m    - Mass of water in tank
 * X    - Mass of DI Water being added
 * FR   - Flow Rate (5.5g/s)
 * t    - Time to leave valve open (in ms)
 *
 * C2 = C1 + (Csp-C1) * G
 * X = (m(C1-C2))/(C1(1-OF))
 * t = (FR)^-1 * (60*X)
 */

#include "Relay.h"
#include "Sensor.h"
#include "LCD.h"
#include <SoftwareSerial.h> //For LCD

uint8_t heater_pin = 10;
uint8_t salt_solenoid_pin = 12;
uint8_t fresh_solenoid_pin = 11;
uint8_t lcd_pin = 2;
uint8_t salinometer_pin = 1;
uint8_t salinometer_read_pin = A0;
uint8_t thermister_pin = 2;

int dead_time = 6;
int st_dev_3 = 6;
double set_point = 0.0010;
double set_point_analog;
double upper_bounds;
double lower_bounds;
double flow_rate;

Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer, thermister;
LCD lcd;

void setup() {
  Serial.begin(9600);
  salt_solenoid.init(salt_solenoid_pin, false);
  fresh_solenoid.init(fresh_solenoid_pin, false);
  heater.init(heater_pin, false);
  lcd.init(0,lcd_pin);
  salinometer.init(salinometer_pin, salinometer_read_pin); //TODO Calculate and use upper and lower bounds
  thermister.init(thermister_pin);
  
  set_point_analog = salinity_to_analog(set_point);
  
  upper_bounds = set_point_analog+st_dev_3;
  lower_bounds = set_point_analog-st_dev_3;
  Serial.print("Upper: ");
  Serial.println(analog_to_salinity(upper_bounds), 20);
  Serial.print("Lower: ");
  Serial.println(analog_to_salinity(lower_bounds), 20);
}

void loop() {
  /*lcd.write(CLEAR);
  int sal = salinometer.get_value();
  lcd.print(sal);
  Serial.println(sal);
  lcd.write(SECOND_LINE);
  lcd.print(analog_to_salinity(salinometer.get_value()), 10);
  delay(1000);*/
}

double analog_to_salinity(uint16_t value) {
  return (2.52459*pow(10,-25)*pow(value,7.9388));
}
uint16_t salinity_to_analog(double value) {
  return (1254.383008*pow(value, 0.1259637));
}

double analog_to_tempurature(uint16_t temp) {
  return 0.0f;
}
