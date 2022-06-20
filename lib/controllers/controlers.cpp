// ISR
#include "controllers.hpp"

namespace ControllersLeo
{
    Controllers::Controllers(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d) : es_pin_x_r(pin_x_r), es_pin_x_l(pin_x_l), es_pin_z_u(pin_z_u), es_pin_z_d(pin_z_d)
    {   
        // intentionally empty
    }

    Controllers::Controllers()
    {   
        // intentionally empty
    }
    Controllers::~Controllers()
    {   
        // intentionally empty
    }

    void Controllers::setEsPins(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d)
    {
        Controllers::es_pin_x_r = pin_x_r;
        Controllers::es_pin_x_r = pin_x_l;
        Controllers::es_pin_x_r = pin_z_u;
        Controllers::es_pin_x_r = pin_z_d;
    }

    void Controllers::esxR()
    {
        digitalWrite(Controllers::es_pin_x_r, LOW);
        Controllers::ax = 1;
    }
    void Controllers::esxL()
    {
        digitalWrite(Controllers::es_pin_x_l, LOW);
        Controllers::ax = -1;
    }
    void Controllers::eszU()
    {
        digitalWrite(Controllers::es_pin_z_u, LOW);
        Controllers::az = 1;
    }
    void Controllers::eszD()
    {
        digitalWrite(Controllers::es_pin_z_d, LOW);
        Controllers::az = 1;
    }
} // ControllersLeo