#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <Arduino.h>
#include "MotorController.hpp"

float map_float(int x, int in_min, int in_max, long out_min, long out_max);

// uint8_t conv_pot_speed(int pot_reading);
// long calc_freq(long speed, uint16_t puls_rev);
// IMPROVEMENT: static float conv_pot_time(int pot_reading);
// IMPROVEMENT: static float conv_pot_distance(int pot_reading);



#endif // CALCULATOR_H