#include "UserInterface.hpp"

UserInterface::UserInterface()
{
    // intentionally empty
}
// UserInterface::UserInterface(const InputPins& in_pins, const DisplayPins& disp_pins, const DriverPins& driv_pins_x, const DriverPins& driv_pins_z)
// {
//     _input_pins = in_pins;
//     _display_pins = disp_pins;
//     _driver_x_pins = driv_pins_x;
//     _driver_z_pins = driv_pins_z;
    
//     _button_change = Debounce(_input_pins.button_1);
//     _button_select = Debounce(_input_pins.button_2);
//     _axis_x = MotorController(_driver_x_pins);
//     _axis_z = MotorController(_driver_z_pins);

// }
UserInterface::UserInterface(const InputPins& in_pins)
{
    _button_change.begin(in_pins.button_1);
    _button_select.begin(in_pins.button_2);
    _pot_pin = in_pins.potentiometer;
}
UserInterface::~UserInterface()
{
    // intentionally empty
}

void UserInterface::get_pot_input()
{
    int new_reading = analogRead(_pot_pin);
    if (new_reading <= _pot_value - 10 || new_reading > _pot_value + 10)
    {
        _pot_value = new_reading;
        set_adjust_menu(true);
        // content_menus[_current_window][1] = _pot_value;
        // display_menu();
    }
    else
    {
        set_adjust_menu(false);
    }
}
void UserInterface::get_button_input()
{
    if (_button_select.debounce() && _change_menu == false)
    {
        Serial.println("Button Select Pressed");
        set_change_menu(true);  
    }
    else if (_button_select.debounce() && _change_menu == true)
    {
        set_change_menu(false);
    }
    if (_button_change.debounce())
    {
        Serial.println("Button Change Pressed");
        set_change_window(true);
    }
}
void UserInterface::set_change_menu(const bool var)
{
    _change_menu = var;
}
void UserInterface::set_adjust_menu(const bool var)
{
    _adjust_menu = var;
}
void UserInterface::set_change_window(const bool var)
{
    _change_window = var;
}
void UserInterface::set_init_process(const bool var)
{
    _init_process = var;
}
const bool UserInterface::get_change_menu()
{
    return _change_menu;
}
const bool UserInterface::get_adjust_menu()
{
    return _adjust_menu;
}
const bool UserInterface::get_change_window()
{
    return _change_window;
}
const bool UserInterface::get_init_process()
{
    return _init_process;
}
const int UserInterface::get_pot_value()
{
    return _pot_value;
}
