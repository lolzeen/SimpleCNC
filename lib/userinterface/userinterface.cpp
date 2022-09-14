#include "UserInterface.hpp"

UserInterface::UserInterface()
{
    // intentionally empty
}
UserInterface::UserInterface(const InputPins& in_pins)
{
    
    _input_pins = in_pins;
    _button.begin(in_pins.button);
    _encoder.begin(in_pins.encoder_a, in_pins.encoder_b);
}
UserInterface::~UserInterface()
{
    // intentionally empty
}
/*void UserInterface::get_enc_input()
{
    uint8_t enc_a_new_value = digitalRead(_input_pins.encoder_a);
    uint8_t enc_b_new_value = digitalRead(_input_pins.encoder_b);

    if (_enc_a_value != enc_a_new_value || _enc_b_value != enc_b_new_value)
    {
        if (enc_a_new_value == 0 && enc_b_new_value == 1)
        {
            _speed_value += 1;
            set_adjust_menu(true);
        }
        else if (enc_a_new_value == 1 && enc_b_new_value == 0)
        {
            _speed_value -= 1;
            set_adjust_menu(true);
        }
        _enc_a_value = enc_a_new_value;
        _enc_b_value = enc_b_new_value;
    }
    else
    {
        set_adjust_menu(false);
    }
}
*/
/*void UserInterface::get_button_input()
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
*/
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
void UserInterface::set_enc_count(int8_t num)
{
    _enc_count = num;
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
const int UserInterface::get_speed_value()
{
    return _speed_value;
}
const int8_t UserInterface::get_enc_direction()
{
    return _enc_direction;
}
const int8_t UserInterface::get_enc_count()
{
    return _enc_count;
}
void UserInterface::read_enc_values()
{
    delayMicroseconds(100);
    uint8_t state = (digitalRead(_input_pins.encoder_a) << 1 | digitalRead(_input_pins.encoder_b));
    static uint8_t start_byte[2];
    if (state >= 2)
    {
        start_byte[state - 2] = 1;
    }
    else if (start_byte[0] && state)
    {
        // CLOCKWISE
        start_byte[0] = start_byte[1] = 0;
        _enc_direction = 1;
        _enc_count++;
    }
    else if (start_byte[1] && !state)
    {
        // COUNTERCLOCKWISE
        start_byte[0] = start_byte[1] = 0;
        _enc_direction = -1;
        _enc_count--;
    }
    if (_enc_count > 125)
    {
        _enc_count = 1;
    }
    else if (_enc_count < -126)
    {
        _enc_count = -1;
    }
    Serial.println(_enc_count);
}
void UserInterface::button_press(const uint8_t& current_window)
{
    if (_button.debounce())
    {
        Serial.println("button");
        switch (current_window)
        {
            case 0:
            if (!get_init_process())
                set_init_process(true);
            else
                set_init_process(false);
            break;
            case 1:
                if (!get_return_home())
                    set_return_home(true);
                else
                    set_return_home(false);
                break;
            case 2:
                if (!get_adjust_menu())
                    set_adjust_menu(true);
                else
                    set_adjust_menu(false);
                break;
            case 3:
                if (!get_adjust_menu())
                    set_adjust_menu(true);
                else
                    set_adjust_menu(false);
                break;
            default:
                break;
        }
    }
    delayMicroseconds(500);
    
}

