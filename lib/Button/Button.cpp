#include "Button.hpp"

void Button::begin(uint8_t pin)
{
    _btn_pin = pin;
    _state = 0;
    pinMode(_btn_pin, INPUT_PULLUP);
}
bool Button::debounce()
{
      _state = (_state<<1) | digitalRead(_btn_pin) | 0xfe00;
      return (_state == 0xff00);
}