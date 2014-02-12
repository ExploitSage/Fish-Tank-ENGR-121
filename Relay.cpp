#include "Relay.h"

Relay::Relay() {
  _init = false;
}

Relay::Relay(uint8_t pin) {
  Relay(pin, false);
}

Relay::Relay(uint8_t pin, bool state) {
  _pin = pin;
  _state = state;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _state);
  _init = true;
}

void Relay::init(uint8_t pin) {
  init(pin, false);
}

void Relay::init(uint8_t pin, bool state) {
  _pin = pin;
  _state = state;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, _state);
  _init = true;
}

void Relay::set(bool state) {
  if(!_init) {
    return;
  } else {
    _state = state;
    digitalWrite(_pin, _state);
  }
}

void Relay::on() {
  set(true);
}
void Relay::open() {
  set(true);
}

void Relay::off() {
  set(false);
}
void Relay::close() {
  set(false);
}

bool Relay::get() {
    if(!_init) {
    return false;
  } else {
    return _state;
  }
}
