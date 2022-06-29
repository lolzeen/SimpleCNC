#include "UserInterface.hpp"

Debounce::Debounce()
{

}
Debounce::Debounce(const InputPins& pins)
{
    
}
Debounce::~Debounce()
{
    
}

bool Debounce::read_input()
{
    int reading = digitalRead(pin);

    if (reading != last_state)
    {
    // reset the debouncing timer
    lastDebounceTime = millis();
    }
    if ((millis() - lastDebounceTime) > debounceDelay)
    {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading != Debounce::state)
        {
            Debounce::state = reading;
            return Debounce::state;   
        }
    }
}

UserInterface::UserInterface()
{
    
}

UserInterface::UserInterface(const InputPins& pins)
{
    UserInterface::input_pins = pins;
    pinMode(UserInterface::input_pins.button_1, INPUT);
    pinMode(UserInterface::input_pins.button_2, INPUT);
}

UserInterface::~UserInterface()
{
}

// TODO: update second row according to get_pot_input
void UserInterface::display_menu(LiquidCrystal& _lcd)
{
    switch (UserInterface::current_window)
    {   
    case 1:
        _lcd.clear();
        _lcd.print(UserInterface::content_menus[1][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(UserInterface::content_menus[1][1]);
        break;
    
    case 2:
        _lcd.clear();
        _lcd.print(UserInterface::content_menus[2][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(UserInterface::content_menus[2][1]);
        break;
    
    default:
        _lcd.clear();
        _lcd.print(UserInterface::content_menus[0][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(UserInterface::content_menus[0][1]);
        UserInterface::current_window = 0;
        break;
    }
}

uint8_t UserInterface::get_current_window() const
{
    return UserInterface::current_window;
}

void UserInterface::adjust_item()
{
    // TODO: define condition
    // while ()
    // {
    //     int value = map(analogRead(A0), 0, 1053, 5, 100);
        
    // }
}

//TODO: finish function
void UserInterface::get_button_input()
{
    // implement debounce
    // adpat the following
    // if (button_state_1 == HIGH)
    // {
    //     current_menu = current_menu + 1;
    //     interface.display_menu(lcd, current_menu);
    //     Serial.println(current_menu);
    // }
    // last_state_button_1 = reading1;
}

/*
int UserInterface::get_pot_input()
{
    return analogRead(A0);
}
*/

