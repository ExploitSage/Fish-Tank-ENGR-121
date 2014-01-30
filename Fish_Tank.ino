#define Csp 0.0010

#define ABOVE_UCL true
#define BELOW_LCL false

#define DEBUG false
/* 
 * Csp  - NaCl Concentration for the setpoint
 * C1   - Initial NaCl Concentration
 * C2   - Target NaCl Concentration
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

/*******************Pin Declarations**********************/
uint8_t fresh_solenoid_pin = 10;
uint8_t salt_solenoid_pin = 9;
uint8_t heater_pin = 8;
uint8_t lcd_pin = 2; //tx pin, use 0 for rx
uint8_t salinometer_pin = 1; //Analog Pin
uint8_t salinometer_read_pin = A0; //Digital Pin for reading
uint8_t thermister_pin = 2;
/*********************************************************/

int dead_time = 6000;
int st_dev = 6; //2.0*3

double FR = 0.33; // liters/minute
double G = 0.7; 
double m = 78.252; // grams //TODO find actual
double OF = 0.15;
double X = 0;
double C1 = 0;
double C2 = 0;

uint32_t t = 0; // milliseconds
uint32_t tlast = 0;
uint16_t topen = 0;

uint16_t set_point, 
  UCL, 
  LCL;



Relay heater, salt_solenoid, fresh_solenoid;
Sensor salinometer, thermister;
LCD lcd;

void setup() {

/*********Set Point and Control Limit Initialisation********/
  set_point = salinity_to_analog(Csp);
  UCL = set_point+st_dev;
  LCL = set_point-st_dev;
/***********************************************************/

  if(DEBUG)
    Serial.begin(9600);
  
/******************Object Initialisation********************/
  salt_solenoid.init(salt_solenoid_pin, false);
  fresh_solenoid.init(fresh_solenoid_pin, false);
  salinometer.init(salinometer_pin, salinometer_read_pin,
    LCL, UCL);
  
  heater.init(heater_pin, false);
  thermister.init(thermister_pin);
  
  lcd.init(0,lcd_pin);
/***********************************************************/

  update_template();

}

void loop() {
  t = millis()-tlast;

  int output = salinometer.get_value();
  C1 = analog_to_salinity(output);

  update_salinity();

  if(DEBUG) {
    Serial.print(output);
    Serial.print(": ");
    Serial.print(C1*100, 3);
    Serial.print(". ");
    Serial.print(set_point);
    Serial.print(": ");
    Serial.println(Csp*100, 3);
  }

  if(t>dead_time) //Salinity Control
  {
    bool correction = NULL;

    if(output < LCL) //Salt Needed
      correction = BELOW_LCL;
    else if(output > UCL) //DI Needed
      correction = ABOVE_UCL;

    if(correction != NULL){
      C2 = get_target(correction, C1);
      X = get_mass(correction, C2);
      topen = get_time(X);
      open_solenoid(correction);
      delay(topen);
      close_solenoid(correction);
      tlast = millis();
    }
  }

  delay(500); //Keep from over saturating salinometer sensor
}

void open_solenoid(bool solenoid) {
  if(solenoid == BELOW_LCL){ //salt
      salt_solenoid.open();
  } else if(solenoid == ABOVE_UCL) { //fresh
      fresh_solenoid.open();
  }
  update_solenoids();
}

void close_solenoid(bool solenoid) {
  if(solenoid == BELOW_LCL){ //salt
      salt_solenoid.close();
  } else if(solenoid == ABOVE_UCL) { //fresh
      fresh_solenoid.close();
  }
  update_solenoids();
}

void update_solenoids() {
  lcd.write(169); lcd.print(salt_solenoid.get());
  lcd.write(183); lcd.print(fresh_solenoid.get());
}

void update_salinity() {
  lcd.write(175); lcd.print((C1*100), 3);
}

double get_target(bool mode, double initial) {
  if(mode == BELOW_LCL)
    return (initial+(Csp-initial)*G);
  else if(mode == ABOVE_UCL)
    return (initial-(initial-Csp)*G);
  else
    return (0);
}

double get_mass(bool mode, double target) {
  if(mode == BELOW_LCL)
    return (m*(target-C1))/((1-OF)*(0.01-C1));
  else if(mode == ABOVE_UCL)
    return (m*(C1-target))/((1-OF)*C1);
  else
    return (0);
}

uint16_t get_time(double mass) {
  return (60*(mass/FR));
}

double analog_to_salinity(uint16_t value) {
  return (2.52459*pow(10,-25)*pow(value,7.9388));
}
uint16_t salinity_to_analog(double value) {
  return (1254.383008*pow(value, 0.1259637));
}

double analog_to_tempurature(uint16_t value) {
  return 0.0f;
}

void update_template() {
  lcd.write(FIRST_LINE);
  lcd.write(" LCL    SP     UCL");
  lcd.write(SECOND_LINE);
  lcd.print(analog_to_salinity(LCL)*100, 3);
  lcd.write("  ");
  lcd.print(Csp*100, 3);
  lcd.write("  ");
  lcd.print(analog_to_salinity(UCL)*100, 3);
  lcd.write(FOURTH_LINE);
  lcd.write("salty current  DI   ");
  update_solenoids();
  update_salinity();
}