#include "UserInterface.hpp"

UserInterface::UserInterface()
{
    // intentionally empty
}
UserInterface::UserInterface(const InputPins& in_pins, const DisplayPins& disp_pins)
{
    _input_pins = in_pins;
    _display_pins = disp_pins;
    pinMode(_input_pins.button_1, INPUT);
    pinMode(_input_pins.button_2, INPUT);
    _button_change = Debounce(_input_pins.button_1);
    _button_select = Debounce(_input_pins.button_2);
}
UserInterface::~UserInterface()
{
    // intentionally empty
}

void UserInterface::set_menu_content()
{
    while (!_button_select.read_input())
    {
        /* problema: como atualizar o menu enquanto o potenciometro é alterado.
        Nao consigo copiar uma instancia de lcd da main e tambem nao consigo herdar a classe liquid crystal.
        */
        int new_reading = map(analogRead(A0), 0, 1053, 5, 100);
        if (new_reading != _pot_value)
        {
            _pot_value = new_reading;
            content_menus[_current_window][_cursor_position] = _pot_value;
            display_menu();
        }
    }

}
void UserInterface::get_button_input(const int& button)
{
    switch (button)
    {
    // button change
    case 1:
        if (!_button_change.read_input())
        {
            Serial.println("Button Change Pressed");
            if (_current_window == 0 && _cursor_position == 0)
            {
                _cursor_position = 1;
            }
            else if (_current_window < _num_windows - 1)
            {
                _current_window += 1;

            }
            // else if (_current_window == _num_windows -1)
            else
            {
                _current_window = 0;
                _cursor_position = 0;
            }
            display_menu();
        }
        
        break;
    // button select
    case 2:
        if (!_button_change.read_input())
        {
            Serial.println("Button Select Pressed");
            set_menu_content();
        }
        break;
    default:
        break;
    }
}
int UserInterface::get_current_window()
{
    return _current_window;
}
void UserInterface::set_current_window(int new_window)
{
    _current_window = new_window;
}
uint8_t UserInterface::get_cursor_position()
{
    return _cursor_position;
}
void UserInterface::set_cursor_position(uint8_t new_cur_pos)
{
    _cursor_position = new_cur_pos;
}
void UserInterface::display_menu()
{
    switch (get_current_window())
    {   
    case 1:
        _lcd.clear();
        _lcd.print(content_menus[1][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(content_menus[1][1]);
        break;
    case 2:
        _lcd.clear();
        _lcd.print(content_menus[2][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(content_menus[2][1]);
        break;
    default:
        _lcd.clear();
        _lcd.print(content_menus[0][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(content_menus[0][1]);
        set_current_window(0);
        break;
    }
    Serial.println("Display Updated");
}
void UserInterface::initialize_display()
{
    _lcd.begin(16,2);
    _lcd.clear();
    _lcd.print("     LASIN");
    delay(1000);
    Serial.println("Display initialized");
    display_menu();
}