/**
 * Relay.h
 * Purpose: Operate a 5v Relay (or Transister).
 * 
 * @author <a href="mailto:gus3@michelfamily.org">Gustave A. Michel III</a>
 * @version 1.2 02/06/14
 * @license The GNU Pulic Liscense v3
 */
 #ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
  public:
    /**
     * Empty constructor, an init() method must be called before instance use
     * @since v1.0
     */
    Relay();
    /**
     * Constructor, defaults starting State
     * @param pin Relay Control Pin
     * @since v1.0
     */
    Relay(uint8_t pin);
    /**
     * Constructor
     * @param pin Relay Control Pin
     * @param state Starting State for Relay
     * @since v1.0
     */
    Relay(uint8_t pin, bool state);
    /**
     * Initializes Relay after empty constructor, defaults starting state
     * @param pin Relay Control Pin
     * @since v1.0
     */
    void init(uint8_t pin);
    /**
     * Initializes Relay after empty constructor, defaults starting state
     * @param pin Relay Control Pin
     * @param state Starting State for Relay
     * @since v1.0
     */
    void init(uint8_t pin, bool state);
    /**
     * Set state of Relay
     * @since v1.0
     */
    void set(bool state);
    /**
     * Sets state of Relay to true
     * @since v1.2
     */
    void on();
    /**
     * Sets state of Relay to false
     * @since v1.2
     */
     void off();
    /**
     * Sets state of Relay to true
     * @since v1.1
     */
    void open();
    /**
     * Sets state of Relay to false
     * @since v1.1
     */
    void close();
    /**
     * Get current state of Relay
     * @return State of Relay
     */
    bool get();
  private:
    bool _init, _state; //_init: If the object has been setup; _state current state of relay, defaults to false
    uint8_t _pin; //_pin: Pin of Relay
};

#endif
