#include "Debounce.hpp"

Debounce::Debounce()
{
    // intentionally empty
}
Debounce::Debounce(const uint8_t& pin)
{
    _pin = pin;
    _state = LOW;
}
Debounce::~Debounce()
{
    
}
bool Debounce::read_input()
{
    int reading = digitalRead(_pin);

    if (reading != _last_state)
    {
    // reset the debouncing timer
    _lastDebounceTime = millis();
    }
    if ((millis() - _lastDebounceTime) > _debounceDelay)
    {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != _state)
        {
            _state = reading;
            return _state;   
        }
    }
}