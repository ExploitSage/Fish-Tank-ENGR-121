#include "LCD.h"

/* A partial listing of commands recognized by the LCD is provided below.    */
/* See the data sheet for the LCD on the Parallax web site for more details. */
/* row and position commands are shown below for all 80 character positions  */
/*    ROW 0:   128=(0,0)  129=(0,1)  130=(0,2)  131=(0,3)  132=(0,4)         */
/*             133=(0,5)  134=(0,6)  135=(0,7)  136=(0,8)  137=(0,9)         */
/*             138=(0,10) 139=(0,11) 140=(0,12) 141=(0,13) 142=(0,14)        */
/*             143=(0,15) 144=(0,16) 145=(0,17) 146=(0,18) 147=(0,19)        */
/*    ROW 1:   148=(1,0)  149=(1,1)  150=(1,2)  151=(1,3)  152=(1,4)         */
/*             153=(1,5)  154=(1,6)  155=(1,7)  156=(1,8)  157=(1,9)         */
/*             158=(1,10) 159=(1,11) 160=(1,12) 161=(1,13) 162=(1,14)        */
/*             163=(1,15) 164=(1,16) 165=(1,17) 166=(1,18) 167=(1,19)        */
/*    ROW 2:   168=(2,0)  169=(2,1)  170=(2,2)  171=(2,3)  172=(2,4)         */
/*             173=(2,5)  174=(2,6)  175=(2,7)  176=(2,8)  177=(2,9)         */
/*             178=(2,10) 179=(2,11) 180=(2,12) 181=(2,13) 182=(2,14)        */
/*             183=(2,15) 184=(2,16) 185=(2,17) 186=(2,18) 187=(2,19)        */
/*    ROW 3:   188=(3,0)  189=(3,1)  190=(3,2)  191=(3,3)  192=(3,4)         */
/*             193=(3,5)  194=(3,6)  195=(3,7)  196=(3,8)  197=(3,9)         */
/*             198=(3,10) 199=(3,11) 200=(3,12) 201=(3,13) 202=(3,14)        */
/*             203=(3,15) 204=(3,16) 205=(3,17) 206=(3,18) 207=(3,19)        */

LCD::LCD() {
  display->begin(9600);
  //pinMode(1, OUTPUT);
  display->write(CLEAR);
  display->write(BACKLIGHT_ON);
  display->write(CURSOR_OFF_NO_BLINK);
}
LCD::LCD(int rx_pin, int tx_pin) {
  display = new SoftwareSerial(rx_pin, tx_pin);
  display->begin(9600);
  display->write(CLEAR);
  display->write(BACKLIGHT_ON);
  display->write(CURSOR_OFF_NO_BLINK);
}

void LCD::init(int rx_pin, int tx_pin) {
  display = new SoftwareSerial(rx_pin, tx_pin);
  display->begin(9600);
  display->write(CLEAR);
  display->write(BACKLIGHT_ON);
  display->write(CURSOR_OFF_NO_BLINK);
}

void LCD::setup() {
  display->write(BACKLIGHT_ON);
  display->write(FIRST_LINE);
  display->write(" LCL    SP     UCL  ");
  display->write(SECOND_LINE);
  display->write("0.072  0.100  0.108 ");
  display->write(THIRD_LINE);
  display->write(" OFF   0.148   ON   ");
}
void LCD::update(double salt, double temp, bool heat) {
  display->write(FOURTH_LINE);
  display->write("S=");
  display->print(salt, 0);
  display->write(196);
  display->write("T=");
  display->print(temp, 0);
  display->write(205);
  if(heat)
    display->write("ON");
  else
    display->write("OFF");
}

void LCD::write(int value) {
  display->write(value);
}
void LCD::write(String value) {
  display->write((char*)value.c_str());
}
void LCD::print(int value) {
  display->print(value);
}
void LCD::print(float value) {
  display->print(value);
}
void LCD::print(float value, int decimals) {
  display->print(value, decimals);
}
void LCD::print(double value) {
  display->print(value);
}
void LCD::print(double value, int decimals) {
  display->print(value, decimals);
}
