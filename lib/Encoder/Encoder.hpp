#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"

class Encoder
{
    private:
        uint8_t _pin_a;
        uint8_t _pin_b;

    public:
        void begin(uint8_t pin_a, uint8_t pin_b);
};

#endif // ENCODER_H