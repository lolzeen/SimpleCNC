#include "DisplayController.hpp"

DisplayController::DisplayController()
{
    initialize_display();
}
DisplayController::DisplayController(const uint8_t& feed_speed, const uint8_t& dive_speed)
{
    initialize_display(true);
    set_menu_content(feed_speed, dive_speed);
    update_display();
}
DisplayController::~DisplayController()
{
    // intentionally empty
}
void DisplayController::update_display()
{
    if (_current_window > _num_windows - 1)
    {
        _current_window = 0;
    }
    else if (_current_window < 0)
    {
        _current_window = _num_windows - 1;
    }
    switch (get_current_window())
    {
        case 0:
            _lcd.clear();
            _lcd.print(_content_menus[0][0]);
            _lcd.setCursor(0, 1);
            _lcd.print(_content_menus[0][1]);
            break;
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
        case 3:
            _lcd.clear();
            _lcd.print(_content_menus[3][0]);
            _lcd.setCursor(0, 1);
            _lcd.print(_content_menus[3][1]);
            break;
        default:
            break;
    }
    // Serial.println("Display Updated");
}
void DisplayController::set_current_window(uint8_t new_window)
{
    _current_window = new_window;
}
void DisplayController::next_window()
{
    _current_window++;
    update_display();
}
void DisplayController::previous_window()
{
    _current_window--;
    update_display();
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
    // Serial.println("Display initialized");
    set_current_window(0);
    update_display();
}
void DisplayController::initialize_display(bool has_init_speeds)
{
    _lcd.begin(16,2);
    _lcd.clear();
    // _lcd.print("     LASIN");
    // Serial.println("Display initialized");
    set_current_window(0);
    set_menu_content(true);
    update_display();
}
void DisplayController::set_menu_content(const uint8_t& content)
{
    _content_menus[get_current_window()][1] = content;
    _content_menus[get_current_window()][1] += " cm/min";
}
void DisplayController::set_menu_content(const uint8_t& _feed_speed, const uint8_t& _dive_speed)
{
    _content_menus[2][1] = _feed_speed;
    _content_menus[2][1] += " cm/min";
    _content_menus[3][1] = _dive_speed;
    _content_menus[3][1] += " cm/min";
}