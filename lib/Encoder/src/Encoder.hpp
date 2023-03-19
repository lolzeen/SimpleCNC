#ifndef ENCODER_H
#define ENCODER_H

#include "Arduino.h"

class Encoder
{
  private:
    const int8_t rot_enc_table[16] = {0,1,1,0,1,0,0,1,1,0,0,1,0,1,1,0};
    uint8_t _pin_a;
    uint8_t _pin_b;
    uint8_t prevNextCode = 0;
    uint16_t store=0;

  public:
    Encoder(uint8_t pin_a, uint8_t pin_b);
    Encoder() {};

    void begin(uint8_t pin_a, uint8_t pin_b);
    int8_t process();

};

#endif // ENCODER_H