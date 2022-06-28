#ifndef UserInterface_H
#define UserInterface_H

#include <Arduino.h>
#include "motorcontroller.hpp"
#include "displaycontroller.hpp"

struct InputPins
{
    uint8_t _button_1;
    uint8_t _button_2;
    uint8_t _potentiometer;
};

class UserInterface
{
private:
// calculated
    int est_time = 0;
//user defined
    // struct Speed
    // {
    //     float x = 0.;
    //     float z = 0.;
    // } linear_speed;
    // struct Distance
    // {
    //     float dis_x = 0.;
    //     float dis_z = 0.;
    // } metric_distance;
    
    int time_delay = 0;

    InputPins input_pins;
    bool io_device;
    uint8_t menu_option; // find better name

    void calc_est_time();
    void get_pot_input();
    void get_button_input();
    void get_serial_input();
    void navigate_through_menu();
public:
    UserInterface();
    UserInterface(const InputPins& pins);
    ~UserInterface();

    // TODO: inputs via serial
    void get_speed();
    void get_distance();
    void get_time();
    void get_time_delay();
    void get_menu_selection();
    void display_main_menu();
    void display_speed_menu();
    void display_distance_menu();
    void display_time_menu();
    // void 
};

#endif //UserInterface_H