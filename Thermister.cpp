#include "Thermister.h"

Thermister::Thermister() {
  _init = false;
  _limits = false;
}

Thermister::Thermister(uint8_t pin) {
  _pin = pin;
  _init = true;
  _limits = false;
}

Thermister::Thermister(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit) {
  _pin = pin;
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _init = true;
  _limits = true;
}

void Thermister::init(uint8_t pin) {
  _pin = pin;
  _init = true;
  _limits = false;
}

void Thermister::init(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit) {
  _pin = pin;
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _init = true;
  _limits = true;
}

uint16_t Thermister::get_value() {
  if(!_init) {
    return 0;
  } else {
    return analogRead(_pin);
  }
}
bool Thermister::is_in_tolerance() {
  if(!_init && !_limits) {
    return 0;
  } else {
    uint16_t value = get_value();
    if(value >= _lower_limit && value <= _upper_limit)
      return true;
    else
      return false;
  }
}

void Thermister::set_limits(uint16_t lower_limit, uint16_t upper_limit) {
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _limits = true;
}
