#include "Calculator.hpp"


float map_float(int x, int in_min, int in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// long conv_pot_speed(int pot_reading)
// {
//     uint8_t _in_min = 0;
//     uint16_t _in_max = 1023;
//     float _out_min = 0.5;
//     float _out_max = 50.;
//     return map(pot_reading, _in_min, _in_max, _out_min, _out_max);
// }
long conv_pot_speed(int pot_reading)
{
  uint8_t _in_min = 0;
  uint16_t _in_max = 1023;
  long _out_min = 90;
  long _out_max = 6;
  return map(pot_reading, _in_min, _in_max, _out_min, _out_max);
}
long calc_freq(long speed, uint16_t puls_rev)
{
  return speed*puls_rev/48;
}