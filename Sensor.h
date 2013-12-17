/**
 * Sensor.h
 * Purpose: Wrapper for Voltage Divider Salinity Meter
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.1 12/09/13
 * @license The GNU Pulic Liscense v3
 */
 #ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"

class Sensor {
  public:
    /**
     * Empty constructor, an init() method must be called before instance use
     * @since v1.0
     */
    Sensor();
    /**
     * Constructor, doesn't allow use of is_in_tolerance().
     * @param pin Analog Pin of sensor
     * @since v1.0
     */
    Sensor(uint8_t pin);
    /**
     * Constructor, doesn't allow use of is_in_tolerance().
     * @param pin Analog Pin of sensor
     * @param read_pin Digital Pin to be used to activate sensor read
     * @since v1.0
     */
    Sensor(uint8_t pin, uint8_t read_pin);
    /**
     * Constructor
     * @param pin Analog Pin of sensor
     * @param lower_limit Lower limit calibration
     * @param upper_limit Upper limit calibration
     * @since v1.0
     */
    Sensor(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit);
    /**
     * Constructor
     * @param pin Analog Pin of sensor
     * @param read_pin Digital Pin to be used to activate sensor read
     * @param lower_limit Lower limit calibration
     * @param upper_limit Upper limit calibration
     * @since v1.0
     */
    Sensor(uint8_t pin, uint8_t read_pin, uint16_t lower_limit, uint16_t upper_limit);
    /** 
     * Initializes Sensor after empty constructor, doesn't allow use of is_in_tolerance().
     * @param pin Analog Pin of sensor
     * @since v1.0
     */
    void init(uint8_t pin);
    /** 
     * Initializes Sensor after empty constructor, doesn't allow use of is_in_tolerance().
     * @param pin Analog Pin of sensor
     * @param read_pin Digital Pin to be used to activate sensor read
     * @since v1.0
     */
    void init(uint8_t pin, uint8_t read_pin);
    /**
     * Initializes Sensor after empty constructor.
     * @param pin Analog Pin of sensor
     * @param lower_limit Lower limit calibration
     * @param upper_limit Upper limit calibration
     */
    void init(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit);
    /**
     * Initializes Sensor after empty constructor.
     * @param pin Analog Pin of sensor
     * @param read_pin Digital Pin to be used to activate sensor read
     * @param lower_limit Lower limit calibration
     * @param upper_limit Upper limit calibration
     */
    void init(uint8_t pin, uint8_t read_pin, uint16_t lower_limit, uint16_t upper_limit);
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
     * Checks if the sensor is above the upper limit
     * @return if the value of the sensor is above the upper limit
     */
    bool is_high();
    /**
     * Checks if the sensor is below the lower limit
     * @return if the value of the sensor is below the lower limit
     */
    bool is_low();
    /**
     * Sets the calibration limits, allows use of is_in_tolerance()
     */
    void set_limits(uint16_t lower_limit, uint16_t upper_limit);
  private:
    uint8_t _pin, _read_pin; //_pin: Analog Pin; _read_pin: pin to be used to active sensor during readings;
    uint16_t _lower_limit, _upper_limit; //_lower_limit: Lower, smaller value limit for calibration; _upper_limit: Upper, larger value limit for calibration;
    bool _init, _limits, _read; //_init: if object has been initialized; _limits: if is_in_tolerance() can be used; _read: if a read_pin is specified;
};

#endif
