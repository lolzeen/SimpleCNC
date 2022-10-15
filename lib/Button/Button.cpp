#include "Button.hpp"

void Button::begin(uint8_t pin)
{
    _btn_pin = pin;
    _state = 0;
    pinMode(_btn_pin, INPUT);
}
void Button::begin(uint8_t pin, bool pull_up)
{
    _btn_pin = pin;
    _state = 0;
    if (pull_up)
        pinMode(_btn_pin, INPUT_PULLUP);
    else
        begin(pin);
}
bool Button::debounce()
{
    _state = (_state<<1) | !digitalRead(_btn_pin) | 0xfe00;
    return (_state == 0xff00);
}
bool Button::debounce_l()
{
    if (digitalRead(_btn_pin))
    {
        // Serial.println(digitalRead(_btn_pin));
        delayMicroseconds(10);
        if (digitalRead(_btn_pin))
        {
            delayMicroseconds(5);
            if (digitalRead(_btn_pin))
            {
                return true;
            }
        }
    }
    return false;
}