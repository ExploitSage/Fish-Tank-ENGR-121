#ifndef Relay_h
#define Relay_h

#include "Arduino.h"

class Relay {
  public:
    Relay();
    Relay(uint8_t pin);
    Relay(uint8_t pin, bool state);
    void init(uint8_t pin);
    void init(uint8_t pin, bool state);
    void set(bool state);
    bool get();
  private:
    bool _init, _state;
    uint8_t _pin;
};

#endif
