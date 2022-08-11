#include "Calculator.hpp"


float map_float(int x, int in_min, int in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

uint8_t conv_pot_speed(int pot_reading)
{
  uint8_t _in_min = 0;
  uint16_t _in_max = 1023;
  uint8_t _out_min = 90;
  uint8_t _out_max = 6;
  return map(pot_reading, _in_min, _in_max, _out_min, _out_max);
}

/*
def calc_ocr_top(lin_speed, pulses_per_rev, pre_scaler_div):
    return 16e6 * 48 / (2 * pre_scaler_div * lin_speed * pulses_per_rev)

    
    if (speed[i] <= 10):
        ocr_val[i] = calc_ocr_top(speed[i], 8e3, 128)
    elif (speed[i] <= 38):
        ocr_val[i] = calc_ocr_top(speed[i], 8e3, 32)
    elif (speed[i] <= 90):
        ocr_val[i] = calc_ocr_top(speed[i], 8e3, 8)
*/
