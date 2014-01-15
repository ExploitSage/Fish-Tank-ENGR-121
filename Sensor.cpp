#include "Sensor.h"

Sensor::Sensor() {
  _init = false;
  _limits = false;
  _read = false;
}

Sensor::Sensor(uint8_t pin) {
  _pin = pin;
  _init = true;
  _limits = false;
  _read = false;
}

Sensor::Sensor(uint8_t pin, uint8_t read_pin) {
  _pin = pin;
  _read_pin = read_pin;
  pinMode(_read_pin, OUTPUT);
  _init = true;
  _limits = false;
  _read = true;
}

Sensor::Sensor(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit) {
  _pin = pin;
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _init = true;
  _limits = true;
  _read = false;
}

Sensor::Sensor(uint8_t pin, uint8_t read_pin, uint16_t lower_limit, uint16_t upper_limit) {
  _pin = pin;
  _read_pin = read_pin;
  pinMode(_read_pin, OUTPUT);
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _init = true;
  _limits = true;
  _read = true;
}

void Sensor::init(uint8_t pin) {
  _pin = pin;
  _init = true;
  _limits = false;
  _read = false;
}

void Sensor::init(uint8_t pin, uint8_t read_pin) {
  _pin = pin;
  _read_pin = read_pin;
  pinMode(_read_pin, OUTPUT);
  _init = true;
  _limits = false;
  _read = true;
}

void Sensor::init(uint8_t pin, uint16_t lower_limit, uint16_t upper_limit) {
  _pin = pin;
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _init = true;
  _limits = true;
  _read = false;
}

void Sensor::init(uint8_t pin, uint8_t read_pin, uint16_t lower_limit, uint16_t upper_limit) {
  _pin = pin;
  _read_pin = read_pin;
  pinMode(_read_pin, OUTPUT);
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _init = true;
  _limits = true;
  _read = true;
}

int Sensor::get_value() {
  int result = 0;
  if(!_init) {
    return 0;
  } else if(_read) {
    digitalWrite(_read_pin, HIGH);
    delay(100);
    result = analogRead(_pin);
    digitalWrite(_read_pin, LOW);
  } else {
    result = analogRead(_pin);
  }
  return result;
}
bool Sensor::is_in_tolerance() {
  if(!_init && !_limits)
    return 0;
  else {
    int value = get_value();
    if(value >= _lower_limit && value <= _upper_limit)
      return true;
    return false;
  }
}

bool Sensor::is_low() {
  if(get_value() < _lower_limit)
    return true;
  return false;
}

bool Sensor::is_high() {
  if(get_value() > _upper_limit)
    return true;
  return false;
}
void Sensor::set_limits(uint16_t lower_limit, uint16_t upper_limit) {
  _lower_limit = lower_limit;
  _upper_limit = upper_limit;
  _limits = true;
}
