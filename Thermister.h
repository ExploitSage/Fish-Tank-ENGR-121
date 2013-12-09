/**
 * Salinometer.h
 * Purpose: Wrapper for Voltage Divider Thermal Meter
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.0 12/07/13
 * @license The GNU Pulic Liscense v3
 */
#ifndef Thermister_h
#define Thermister_h

#include "Arduino.h"

class Thermister {
  public:
    /**
     * Empty constructor, an init() method must be called before instance use
     * @since v1.0
     */
    Thermister();
    /**
     * Constructor, doesn't allow use of is_in_tolerance().
     * @param pin Analog Pin of sensor
     * @since v1.0
     */
    Thermister(uint8_t pin);
    /**
     * Constructor
     * @param pin Analog Pin of sensor
     * @param lower_limit Lower limit calibration
     * @param upper_limit Upper limit calibration
     * @since v1.0
     */
    Thermister(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit);
    /** 
     * Initializes Salinometer after empty constructor, doesn't allow use of is_in_tolerance().
     * @param pin Analog Pin of sensor
     * @since v1.0
     */
    void init(uint8_t pin);
    /**
     * Initializes Salinometer after empty constructor.
     * @param pin Analog Pin of sensor
     * @param lower_limit Lower limit calibration
     * @param upper_limit Upper limit calibration
     */
    void init(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit);
    /**
     * Returns Analog Value of sensor
     * @return Value from 0 to 1023
     */
    uint16_t get_value();
    /**
     * Checks if the value of the sensor is betweent the upper and lower limits
     * @return if the value is between the limits
     */
    bool is_in_tolerance();
    /**
     * Sets the calibration limits, allows use of is_in_tolerance()
     */
    void set_limits(uint16_t lower_limit, uint16_t upper_limit);
  private:
    uint8_t _pin; //_pin: Analog Pin
    uint16_t _lower_limit, _upper_limit; //_lower_limit: Lower, smaller value limit for calibration; _upper_limit: Upper, larger value limit for calibration;
    bool _init, _limits; //_init: if object has been initialized; _limits: if is_in_tolerance() can be used;
};

#endif
