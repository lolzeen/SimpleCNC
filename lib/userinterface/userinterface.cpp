#include "UserInterface.hpp"

UserInterface::UserInterface()
{
    // intentionally empty
}
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
    if (new_reading < _pot_value - 1 || new_reading > _pot_value + 1)
    {
        _pot_value = conv_pot_speed(new_reading);
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
    if (_button_select.debounce())
    {
        if (_change_menu == false)
        {
            Serial.println("Button Select Pressed: Start Editing");
            set_change_menu(true);
        }
        else
        {
            Serial.println("Button Select Pressed: End Editing");
            set_change_menu(false);
        }
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
void UserInterface::set_return_home(const bool var)
{
    _return_home = var;
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
const bool UserInterface::get_return_home()
{
    return _return_home;
}
const int UserInterface::get_pot_value()
{
    return _pot_value;
}
uint8_t UserInterface::conv_pot_speed(const int pot_reading)
{
  uint8_t _in_min = 0;
  uint16_t _in_max = 1023;
  uint8_t _out_min = 100;
  uint8_t _out_max = 0;
  return map(pot_reading, _in_min, _in_max, _out_min, _out_max);
}

