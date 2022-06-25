#ifndef MACHINECONTROLLER_H
#define MACHINECONTROLLER_H

#include <Arduino.h>
#include "motorcontroller.hpp"

namespace HardwareLeo
{
    class MachineController
    // Define process parameters and execute movements
    {
    private:
        

        // Axis Position (-1 or +1)
        int pos_x;
        int pos_z;

        struct DriPar
        // Driver parameters
        {
            bool dir;
            bool enable;
        };
        
        void calc_freq();
        void calc_num_pulses();

    public:
        
        // MachineController(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d);
        MachineController();
        ~MachineController();
        
        
        // TODO: get user input in respect to desired speed ~routine parameters~
        //  void read
        

    };
    
    
    
} // ParametersLeo
#endif // MACHINECONTROLLER_H