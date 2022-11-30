#include "Encoder.hpp"
Encoder::Encoder(uint8_t pin_a, uint8_t pin_b) : _pin_a(pin_a), _pin_b(pin_b)
{
    pinMode(_pin_a, INPUT);
    pinMode(_pin_b, INPUT);
}

void Encoder::begin(uint8_t pin_a, uint8_t pin_b)
{
    _pin_a = pin_a;
    _pin_b = pin_b;
    pinMode(_pin_a, INPUT);
    pinMode(_pin_b, INPUT);
}

int8_t Encoder::process()
{
  prevNextCode <<= 2;
  if (digitalRead(_pin_a)) prevNextCode |= 0x02;
  if (digitalRead(_pin_b)) prevNextCode |= 0x01;
  prevNextCode &= 0x0f;

   // If valid then store as 16 bit data.
   if  (rot_enc_table[prevNextCode] ) {
      store <<= 4;
      store |= prevNextCode;
      //if (store==0xd42b) return 1;
      //if (store==0xe817) return -1;
      if ((store&0xff)==0x2b) return -1;
      if ((store&0xff)==0x17) return 1;
   }
   return 0;
}