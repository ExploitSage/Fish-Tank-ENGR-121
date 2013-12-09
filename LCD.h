/**
 * LCD.h
 * Purpose: Operate a Parallax 20x4 Serial LCD Display
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.0 12/09/13
 * @license The GNU Pulic Liscense v3
 */

#ifndef LCD_h
#define LCD_h

#define BACKSPACE 8
#define SPACE 9
#define DROP 10
#define CLEAR 12
#define CARRIAGE_RETURN 13
#define BACKLIGHT_ON 17
#define BACKLIGHT_OFF 18
#define DISPLAY_OFF 21
#define CURSOR_OFF_NO_BLINK 22
#define CURSOR_OFF_BLINK 23
#define CURSOR_NO_BLINK 24
#define CURSOR_BLINK 25
#define FIRST_LINE 128
#define SECOND_LINE 148
#define THIRD_LINE 168
#define FOURTH_LINE 188

#include "Arduino.h"

class LCD {
  public:
    /**
     * Constructor
     * @since v1.0
     */
    LCD();
    /**
     * 
     * @since v1.0
     */
    void update(float salt, float temp, bool heat);
    void setup();
    void write(int value);
    void write(String value);
    void print(int value);
    void print(float value);
    void print(float value, int decimals);
  private:
};

#endif
