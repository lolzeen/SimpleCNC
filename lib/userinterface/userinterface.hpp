#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Arduino.h>

namespace UserLeo
{
    class Userinterface
    {
    private:
    // calculated
        int est_time = 0;
    //user defined
        float spe_x = 0.;
        float spe_z = 0.;
        float dis_x = 0.;
        float dis_z = 0.;
        int time_delay = 0;
        
        
        void calc_est_time();
    public:
        Userinterface(/* args */);
        ~Userinterface();
    };
    
    

} // UserLeo

#endif //USERINTERFACE_H