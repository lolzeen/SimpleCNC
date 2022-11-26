#include "DisplayController.hpp"

DisplayController::DisplayController()
{
    initialize_display();
}
DisplayController::DisplayController(const InputPins& in_pins)
{
    _input_pins = in_pins;
    _button.begin(in_pins.button, true);
    _encoder.begin(in_pins.encoder_a, in_pins.encoder_b);
    initialize_display();
}
DisplayController::DisplayController(const InputPins& in_pins, const uint8_t& feed_speed, const uint8_t& dive_speed)
{
    _input_pins = in_pins;
    _button.begin(in_pins.button, true);
    _encoder.begin(in_pins.encoder_a, in_pins.encoder_b);
    initialize_display(true);
    // uint8_t content[] = {feed_speed, dive_speed};
    // set_menu_content(content, 2);
    update_display();
    
}
DisplayController::~DisplayController()
{
    // intentionally empty
}

void DisplayController::set_adjust_menu(const bool var)
{
    _adjust_menu = var;
}
void DisplayController::set_change_menu(const bool var)
{
    _change_menu = var;
}
void DisplayController::set_current_window(uint8_t new_window)
{
    _current_window = new_window;
}
void DisplayController::set_change_window(const bool var)
{
    _change_window = var;
}
void DisplayController::set_enc_count(int8_t num)
{
    _enc_count = num;
}
void DisplayController::set_init_process(const bool var)
{
    _init_process = var;
}
void DisplayController::set_menu_content(String lower)
{
    _lcd.setCursor(0, 1);
    _lcd.print(lower);
}
void DisplayController::set_menu_content(int content_descriptor, String content)
{
    switch (content_descriptor)
    {
    case POS_EDIT_HORIZONTAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case POS_EDIT_VERTICAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case SPEED_EDIT_HORIZONTAL:
        _lcd.setCursor(0,0);
        _lcd.print(content+"cm/min");
        break;
    case SPEED_EDIT_VERTICAL:
        _lcd.setCursor(0,0);
        _lcd.print(content+"cm/min");
        break;
    case VOLTAGE_TOLERANCE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;
    case ARC_GAIN_EDIT:
        _lcd.setCursor(0,0);
        _lcd.print(content);
        break;
    case ARC_SHORT_CIRCUIT_VOLTAGE_EDIT:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;        
    default:
        break;
    }
}
void DisplayController::set_menu_content(const char* upper, const char* lower)
{
    _lcd.clear();
    _lcd.print(upper);
    _lcd.setCursor(0, 1);
    _lcd.print(lower);
}
void DisplayController::set_return_home(const bool var)
{
    _return_home = var;
}

#if NUM_CASES == 5
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
#endif
#if NUM_CASES == 20
void DisplayController::set_menu_content(const uint8_t& content)
{
    String new_content = "";
    new_content += content;
    new_content += " cm/min";
    set_menu_content(new_content);
}
#endif

const int DisplayController::get_current_window()
{
    return _current_window;
}
const bool DisplayController::get_change_menu()
{
    return _change_menu;
}
const bool DisplayController::get_adjust_menu()
{
    return _adjust_menu;
}
const bool DisplayController::get_change_window()
{
    return _change_window;
}
const bool DisplayController::get_init_process()
{
    return _init_process;
}
const bool DisplayController::get_return_home()
{
    return _return_home;
}
const int DisplayController::get_speed_value()
{
    return _speed_value;
}
const int8_t DisplayController::get_enc_direction()
{
    return _enc_direction;
}
const int8_t DisplayController::get_enc_count()
{
    return _enc_count;
}

void DisplayController::button_press()
{
    button_press(true);
}
void DisplayController::button_press(bool activate_update_display)
{
    if (_button.debounce())
    {
        // Serial.println("button");
        switch (_current_window)
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
            default:
            // TODO: implement case 5 (save)
                if (_current_window >=2 || _current_window <= 4)
                {
                    _current_window *= 10;
                    
                }
                else if (_current_window == (20||21||30||31||40||41||42))
                {
                    _current_window *= 10;
                    
                    set_adjust_menu(true);
                }
                else if (_current_window == (200||210||300||310||400||410||420))
                {
                    _current_window /= 10;
                    
                    set_adjust_menu(false);
                }
                else if (_current_window == (22||32||43||52||201||211||301||311||401||411||421))
                {
                    _current_window /= 10;
                }
                else
                {
                    _current_window = 0;
                }
                if (activate_update_display) update_display();
                break;
        }
    }
    delayMicroseconds(500);
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
void DisplayController::next_window()
{
    _current_window++;
    update_display();
}
void DisplayController::next_option()
{
    _current_window *= 10;
}
void DisplayController::previous_option()
{
    _current_window /= 10;
}
void DisplayController::previous_window()
{
    _current_window--;
    update_display();
}
void DisplayController::process_window()
{
    _lcd.clear();
    _lcd.setCursor(0,0);
    _lcd.print("Executando");
    _lcd.setCursor(1,0);
    _lcd.print("Processo");
}
void DisplayController::read_enc_values()
{
    delayMicroseconds(100); // previous setting 100
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
}
void DisplayController::update_display()
{
    if (_current_window < 0)
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
    #if NUM_CASES == 20
        switch (get_current_window())
        {
            case 0:
                set_menu_content(MES_INIT, MES_PRESS_CONFIRM);
                break;
            case 1:
                set_menu_content(MES_RETU, MES_PRESS_CONFIRM);
                break;
            case 2:
                set_menu_content(MES_POS, MES_PRESS_EDIT);
                break;
            case 20:
                set_menu_content(MES_POS_HORI, MES_PRESS_EDIT);
                break;
            case POS_EDIT_HORIZONTAL:
                set_menu_content(MES_POS_EDIT, MES_PRESS_CONFIRM);
                break;
            case 21:
                set_menu_content(MES_POS_VERT, MES_PRESS_EDIT);
                break;
            case POS_EDIT_VERTICAL:
                set_menu_content(MES_POS_VERT, MES_PRESS_CONFIRM);
                break;
            case 3:
                set_menu_content(MES_SPEED, MES_PRESS_EDIT);
                break;
            case 30:
                set_menu_content(MES_SPEED_FORW, MES_PRESS_EDIT);
                break;
            case SPEED_EDIT_HORIZONTAL:
                set_menu_content(MES_SPEED_FORW, MES_PRESS_CONFIRM);
                break;
            case 31:
                set_menu_content(MES_SPEED_DIVE, MES_PRESS_EDIT);
                break;
            case SPEED_EDIT_VERTICAL:
                set_menu_content(MES_SPEED_DIVE, MES_PRESS_CONFIRM);
                break;
            case 4:
                set_menu_content(MES_ARC, MES_PRESS_EDIT);
                break;
            case 40:
               
            case 41:
                set_menu_content(MES_ARC_GAIN, MES_PRESS_EDIT);
                break;
            case ARC_GAIN_EDIT:
                set_menu_content(MES_ARC_GAIN, MES_PRESS_CONFIRM);
                break;
            case 5:
                set_menu_content(MES_SAVE, MES_PRESS_CONFIRM);
                break;
            default:
                if (_current_window == (22||32||42||52||211||311||411))
                {
                    set_menu_content(MES_RETURN_PREVIOUS_MENU, MES_PRESS_CONFIRM);
                }
                else
                {
                    set_menu_content(MES_RETURN_MAIN_MENU, MES_PRESS_CONFIRM);
                }
                break;
        }
    #endif
    // Serial.println("Display Updated");
}
// void DisplayController::encoder_action()
// {
//     if (_enc_count != _last_enc_count)
//     {
//         if (!_adjust_menu)
//         {
//             if (_enc_direction > 0)
//             {
//                 _change_window += 1;
//             }
//             else
//             {
//                 _change_window -= 1;
//             }
//         }
//         while (_adjust_menu)
//         {
//             if (_enc_count != _last_enc_count)
//             {
//                 switch (_current_window)
//                 {
//                 case 200:
//                     //TODO start horizontal jogging
//                     break;
//                 case 210:
//                     // TODO start vertical jogging
//                     break;
//                 case 300:
//                     // TODO set velocidade de avanco
//                     break;
//                 case 310:
//                     // TODO set velocidade de mergulho
//                     break;
//                 case 400:
//                     // TODO set initial arc height
//                     break;
//                 case 410:
//                     // TODO set arc controller gain
//                 default:
//                     break;
//                 }
//             }
//             button_press();
//         }
//     }
//     _last_enc_count = 0;
//     set_enc_count(0);
// }