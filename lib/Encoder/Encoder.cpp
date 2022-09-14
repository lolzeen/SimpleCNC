#include "Encoder.hpp"

void Encoder::begin(uint8_t pin_a, uint8_t pin_b)
{
    _pin_a = pin_a;
    _pin_b = _pin_b;
    pinMode(_pin_a, INPUT);
    pinMode(_pin_b, INPUT);
}