#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <Arduino.h>

namespace ControllersLeo
{
    class Controllers
    {
    private:
        int es_pin_x_r = 0;
        int es_pin_x_l = 0;
        int es_pin_z_u = 0;
        int es_pin_z_d = 0;
        int ax = 0;
        int az = 0;

    public:
        
        Controllers(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d);
        Controllers();
        ~Controllers();
        
        void setEsPins(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d);

        void esxR();
        void esxL();
        void eszU();
        void eszD();
    };
    
    
    
} // ControllersLeo
#endif // CONTROLLERS_H