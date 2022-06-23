#ifndef PARAMETERS_H
#define PARAMETERS_H

#include <Arduino.h>

namespace ParametersLeo
{
    class Parameters
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
        
        Parameters(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d);
        Parameters();
        ~Parameters();
        
        
        // TODO: get user input in respect to desired speed ~routine parameters~
        //  void read
        

    };
    
    
    
} // ParametersLeo
#endif // PARAMETERS_H