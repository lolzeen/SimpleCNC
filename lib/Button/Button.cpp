#include "Button.hpp"

void Button::begin(uint8_t pin)
{
    _btn_pin = pin;
    _state = 0;
    pinMode(_btn_pin, INPUT);
    // set_last_debounce(0);
}
void Button::begin(uint8_t pin, bool pull_up)
{
    _btn_pin = pin;
    _state = 0;
    if (pull_up)
        pinMode(_btn_pin, INPUT_PULLUP);
    else
        begin(pin);
    // set_last_debounce(0);
}
bool Button::debounce()
{
    _state = (_state<<1) | !digitalRead(_btn_pin) | 0xfe00;
    return (_state == 0xff00);
}
bool Button::debounce_l()
{
    if (digitalRead(_btn_pin) && (_last_debounce < 200 + millis() || _last_debounce == 0))
    {
        // Serial.println(digitalRead(_btn_pin));
        delayMicroseconds(20);
        if (digitalRead(_btn_pin))
        {
            set_last_debounce(millis());
            return true;
        }
    }
    return false;
}
void Button::set_last_debounce(unsigned long last_db)
{
    _last_debounce = last_db;
}