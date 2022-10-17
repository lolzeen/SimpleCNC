#include "DisplayController.hpp"

DisplayController::DisplayController()
{
    initialize_display();
}
DisplayController::DisplayController(const uint8_t& feed_speed, const uint8_t& dive_speed)
{
    initialize_display(true);
    uint8_t content[] = {feed_speed, dive_speed};
    set_menu_content(content, 2);
    update_display();
}
DisplayController::~DisplayController()
{
    // intentionally empty
}
void DisplayController::update_display()
{
    if (_current_window > NUM_CASES - 1)
    {
        _current_window = 0;
    }
    else if (_current_window < 0)
    {
        _current_window = NUM_CASES - 1;
    }
        #if NUM_CASES == 5
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
                case 4:
                    _lcd.clear();
                    _lcd.print(_content_menus[4][0]);
                    _lcd.setCursor(0, 1);
                    _lcd.print(_content_menus[4][1]);
                default:
                    break;
            }
        #endif
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
void DisplayController::set_menu_content(uint8_t* values, uint8_t num_values)
{
    if (num_values > 0)
    {
        if (num_values == 2)
        {
            _content_menus[2][1] = *values;
            _content_menus[2][1] += " cm/min";
            _content_menus[3][1] = *(values+1);
            _content_menus[3][1] += " cm/min";
        }
        
    }
    
}
void DisplayController::countdown_window()
{
    for (int i = 5; i > 0 ; i--)
    {
        _lcd.clear();
        _lcd.setCursor(0, 0);
        _lcd.print("Iniciando em ");
        _lcd.print(i);
        _lcd.print("s");
        delay(1000);
    }
}
void DisplayController::process_window()
{
    _lcd.clear();
    _lcd.setCursor(0,0);
    _lcd.print("Executando");
    _lcd.setCursor(1,0);
    _lcd.print("Processo");
}