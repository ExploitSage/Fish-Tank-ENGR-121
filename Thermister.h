#ifndef Thermister_h
#define Thermister_h

#include "Arduino.h"

class Thermister {
  public:
    Thermister();
    Thermister(uint8_t pin);
    Thermister(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit);
    void init(uint8_t pin);
    void init(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit);
    uint16_t get_value();
    bool is_in_tolerance();
    void set_limits(uint16_t lower_limit, uint16_t upper_limit);
  private:
    uint8_t _pin;
    uint16_t _lower_limit, _upper_limit;
    bool _init, _limits;
};

#endif
