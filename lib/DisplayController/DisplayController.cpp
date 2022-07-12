#include "DisplayController.hpp"

DisplayController::DisplayController()
{
    initialize_display();
}
DisplayController::~DisplayController()
{
    // intentionally empty
}
void DisplayController::display_menu()
{
    switch (get_current_window())
    {   
    case 1:
        _lcd.clear();
        _lcd.print(_content_menus[1][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(_content_menus[1][1]);
        break;
    case 2:
        _lcd.clear();
        _lcd.print(_content_menus[2][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(_content_menus[2][1]);
        break;
    default:
        _lcd.clear();
        _lcd.print(_content_menus[0][0]);
        _lcd.setCursor(0, 1);
        _lcd.print(_content_menus[0][1]);
        set_current_window(0);
        break;
    }
    Serial.println("Display Updated");
}
void DisplayController::set_current_window(uint8_t new_window)
{
    _current_window = new_window;
}
void DisplayController::next_window()
{
    _current_window += 1;
    display_menu();
}
int DisplayController::get_current_window()
{
    return _current_window;
}
void DisplayController::initialize_display()
{
    _lcd.begin(16,2);
    _lcd.clear();
    // _lcd.print("     LASIN");
    Serial.println("Display initialized");
    set_current_window(0);
    display_menu();
}
void DisplayController::set_menu_content(float content)
{
    _content_menus[get_current_window()][1] = content;
    _content_menus[get_current_window()][1] += " cm/min";
    display_menu();
}
