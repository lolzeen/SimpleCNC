#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Arduino.h>
#include "Button.hpp"

struct InputPins
{
    InputPins()
    {
        // intentionally empty
    }
    InputPins(const uint8_t& b1, const uint8_t& b2, const uint8_t& pot)
    {
        button_1 = b1;
        button_2 = b2;
        potentiometer = pot;
    }
    InputPins(const InputPins& input_pins)
    {
        button_1 = input_pins.button_1;
        button_2 = input_pins.button_2;
        potentiometer = input_pins.potentiometer;
    }
    // button change
    uint8_t button_1;
    // buton select
    uint8_t button_2;
    uint8_t potentiometer;
};

class UserInterface
{
private:
    Button _button_change, _button_select;
    // DisplayPins _display_pins;
    // DriverPins _driver_x_pins, _driver_z_pins;
    // Debounce _button_change, _button_select;
    // MotorController _axis_x, _axis_z;
    // DisplayController _display;
    
    uint8_t _pot_pin;
    int _pot_value = -10;

    bool _change_menu = false;
    bool _adjust_menu = false;
    bool _change_window = false;
    bool _init_process = false;
    bool _return_home = false;

    uint8_t conv_pot_speed(const int pot_reading);
    
public:
    UserInterface();
    // UserInterface(const InputPins& in_pins, const DisplayPins& disp_pins,  const DriverPins& driv_pins_x, const DriverPins& driv_pins_z);
    UserInterface(const InputPins& in_pins);
    ~UserInterface();

    void get_pot_input();
    void get_button_input();
    
    void set_init_process(bool var);
    void set_return_home(bool var);
    void set_change_menu(bool var);
    void set_adjust_menu(bool var);
    void set_change_window(bool var);

    const bool get_init_process();
    const bool get_return_home();
    const bool get_change_menu();
    const bool get_adjust_menu();
    const bool get_change_window();
    const int get_pot_value();
    
};

#endif // USERINTERFACE_H