/* Csp  - NaCl Concentration for the setpoint
 * C1   - Initial NaCl Concentration
 * C1   - Target NaCl Concentration
 * G    - Gain
 * OF   - Fraction of Overflow from DI
 * m    - Mass of water in tank
 * X    - Mass of DI Water being added
 * FR   - Flow Rate
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

int deadtime = 6;
double set_point = 0.0;
double upper_bounds;
double lower_bounds;
double flowRate;

uint8_t heater_pin = 10;
uint8_t salt_solenoid_pin = 12;
uint8_t fresh_solenoid_pin = 11;
uint8_t lcd_pin = 2;


Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer, thermister;
LCD lcd;

void setup() {
  Serial.begin(9600);
  salt_solenoid.init(salt_solenoid_pin, false);      //Digital Pin 12
  fresh_solenoid.init(fresh_solenoid_pin, false);    //Digital Pin 11
  heater.init(heater_pin, false);                    //Digital Pin 10
  lcd.init(0,2);                      //Digital Pin 02
  salinometer.init(1, A0);  //Analog  Pin 01
                                      //Digital Pin A0
  thermister.init(2, 400, 650);       //Analog  Pin 02
}

void loop() {
  lcd.write(CLEAR);
  int sal = salinometer.get_value();
  lcd.print(sal);
  Serial.println(sal);
  lcd.write(SECOND_LINE);
  lcd.print(salinity(salinometer.get_value()), 10);
  delay(1000);
}

double salinity(uint16_t salt) {
  return (2.52459*pow(10,-25)*pow(salt,7.9388));
}

double tempurature(uint16_t temp) {
  return 0.0f;
}
