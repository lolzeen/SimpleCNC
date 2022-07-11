#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <Arduino.h>

float map_float(int x, int in_min, int in_max, long out_min, long out_max);


float conv_pot_speed(int pot_reading);
        // IMPROVEMENT: static float conv_pot_time(int pot_reading);
        // IMPROVEMENT: static float conv_pot_distance(int pot_reading);



#endif // CALCULATOR_H