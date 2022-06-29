#ifndef UserInterface_H
#define UserInterface_H

#include <Arduino.h>
#include "motorcontroller.hpp"
#include "displaycontroller.hpp"
#include <LiquidCrystal.h>

struct InputPins
{
    uint8_t button_1;
    uint8_t button_2;
    uint8_t potentiometer;
};

struct InputState
{
    uint8_t button_state_1;
    uint8_t last_state_button_1 = LOW;
    uint8_t button_state_2;
    uint8_t last_state_button_2 = LOW;
    uint16_t pot_value = 0;
};

class Debounce 
{
    private:
        uint8_t pin;
        uint8_t state;
        uint8_t last_state = LOW;
        unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
        unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

    public:
        Debounce();
        Debounce(const InputPins& pins);
        ~Debounce();
        bool read_input();

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
    
    // IMPROVEMENT int time_delay = 0;

    InputPins input_pins;

    int current_window = 0;

    // IMPROVEMENT void calc_est_time();
    int get_pot_input();
    void get_button_input();

    void adjust_item();

    // const int num_menus = 3;
    
public:
    UserInterface();
    UserInterface(const InputPins& pins);
    ~UserInterface();

    // TODO: inputs via serial
    void get_speed();
    // IMPROVEMENT void get_distance();
    // IMPROVEMENT void get_time();
    // IMPROVEMENT void get_time_delay();
    
    String content_menus[3][2] = {{"Iniciar Processo", "Ajustar Param."}, {"Vel. Avanco", ""}, {"Vel. Mergulho", ""}};

    uint8_t get_current_window() const;
    void display_menu(LiquidCrystal& _lcd);
    // void select_item(LiquidCrystal& _lcd);
};

#endif //UserInterface_H