#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Arduino.h>

struct InputPins
{
    uint8_t _button_1;
    uint8_t _button_2;
    uint8_t _potentiometer;
};

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

    InputPins user_input;

    void calc_est_time();
    void get_pot_input();
    void get_button_input();
public:
    Userinterface();
    ~Userinterface();

    // TODO
    void get_speed();
    void get_distance();
    void get_time();
    void get_menu_selection();
};

#endif //USERINTERFACE_H