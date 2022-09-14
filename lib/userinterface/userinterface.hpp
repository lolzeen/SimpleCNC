#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Arduino.h>
#include "Button.hpp"
#include "Encoder.hpp"

struct InputPins
{
    InputPins()
    {
        // intentionally empty
    }
    InputPins(const uint8_t& b, const uint8_t& enc_a, const uint8_t& enc_b)
    {
        button = b;
        encoder_a = enc_a;
        encoder_b = enc_b;
    }
    InputPins(const InputPins& input_pins)
    {
        button = input_pins.button;
        encoder_a = input_pins.encoder_a;
        encoder_b = input_pins.encoder_b;
    }
    uint8_t button;
    uint8_t encoder_a;
    uint8_t encoder_b;
};

class UserInterface
{
private:
    Button _button;
    Encoder _encoder;
    // DisplayPins _display_pins;
    
    // DriverPins _driver_x_pins, _driver_z_pins;
    // Debounce _button_change, _button_select;
    // MotorController _axis_x, _axis_z;
    // DisplayController _display;
    
    InputPins _input_pins;
    int _speed_value = 10; // TODO: to definindo a vlocidade la no setup, tem que combinar essas duas

    int8_t _enc_direction;
    volatile int8_t _enc_count = 0;
    bool _button_state = false;
    bool _change_menu = false;
    bool _adjust_menu = false;
    bool _change_window = false;
    bool _init_process = false;
    bool _return_home = false;
    
public:
    UserInterface();
    // UserInterface(const InputPins& in_pins, const DisplayPins& disp_pins,  const DriverPins& driv_pins_x, const DriverPins& driv_pins_z);
    UserInterface(const InputPins& in_pins);
    ~UserInterface();
    
    void set_init_process(bool var);
    void set_return_home(bool var);
    void set_change_menu(bool var);
    void set_adjust_menu(bool var);
    void set_change_window(bool var);
    void set_enc_count(int8_t num);

    const bool get_init_process();
    const bool get_return_home();
    const bool get_change_menu();
    const bool get_adjust_menu();
    const bool get_change_window();
    const int get_speed_value();
    const int8_t get_enc_direction();
    const int8_t get_enc_count();
    
    void button_press(const uint8_t& current_window);
    void read_enc_values();
    bool validate_enc_values();
};

#endif // USERINTERFACE_H