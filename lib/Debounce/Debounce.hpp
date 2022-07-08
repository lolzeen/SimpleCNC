#ifndef DEBOUNCE_H
#define DEBOUNCE_H

#include <Arduino.h>

class Debounce 
{
    private:
        uint8_t _pin;
        uint8_t _state;
        uint8_t _last_state = LOW;
        unsigned long _lastDebounceTime = 0;  // the last time the output pin was toggled
        unsigned long _debounceDelay = 100;    // the debounce time; increase if the output flickers

    public:
        Debounce();
        Debounce(const uint8_t& pin);
        ~Debounce();
        bool read_input();

};

#endif // DEBOUNCE_H