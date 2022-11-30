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
DisplayController::~DisplayController()
{
    // intentionally empty
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
                if (!get_init_process()) set_init_process(true);
                else set_init_process(false);
                update_display_static();
                break;
            case 1:
                if (!get_return_home()) set_return_home(true);
                else set_return_home(false);
                update_display_static();
                break;
            default:
                if (_current_window == 2 ||
                    _current_window == 3 ||
                    _current_window == 30 ||
                    _current_window == 31)
                {
                    _current_window *= 10;
                    update_display_static();
                }
                // else if ((_current_window == 20 ||
                //         _current_window == 21  ||
                //         _current_window == 300 ||
                //         _current_window == 301 ||
                //         _current_window == 302 ||
                //         _current_window == 303 ||
                //         _current_window == 304 ||
                //         _current_window == 310 ||
                //         _current_window == 311) &&
                //         !get_adjust_menu())
                else if ((_current_window == 20 ||
                        _current_window == 21  ||
                        _current_window == 310 ||
                        _current_window == 311 ||
                        (_current_window >= 300 &&
                        _current_window <= 304)) &&
                        !get_adjust_menu())
                {
                    _current_window *= 10;
                    set_adjust_menu(true);
                    update_display_dynamic(_current_window,"");
                }
                // else if (_current_window == 200 ||
                //         _current_window == 210 ||
                //         _current_window == 3000 ||
                //         _current_window == 3010 ||
                //         _current_window == 3020 ||
                //         _current_window == 3030 ||
                //         _current_window == 3040 ||
                //         _current_window == 3100 ||
                //         _current_window == 3110)
                else if (_current_window == 200 ||
                        _current_window == 210 ||
                        _current_window >= 3000)
                {
                    _current_window /= 10;
                    set_adjust_menu(false);
                    update_display_static();
                }
                else if (_current_window == 22 ||
                        _current_window == 305 ||
                        _current_window == 312)
                {
                    _current_window /= 10;
                    update_display_static();
                }
                else
                {
                    _current_window = 0;
                    update_display_static();
                }
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
    update_display_static();
}
void DisplayController::initialize_display(bool has_init_speeds)
{
    _lcd.begin(16,2);
    _lcd.clear();
    // _lcd.print("     LASIN");
    // Serial.println("Display initialized");
    set_current_window(0);
    update_display_static();
}
void DisplayController::next_window()
{
    if (validateWindow(_current_window+1))
    {
        _current_window++;
        update_display_static();
    }
}
void DisplayController::next_option()
{
    if (validateWindow(_current_window*10))
    {
        _current_window *= 10;
        update_display_static();
    }
}
void DisplayController::previous_option()
{
    if (validateWindow(_current_window/10))
    {
        _current_window /= 10;
        update_display_static();
    }
}
void DisplayController::previous_window()
{
    if (validateWindow(_current_window-1))
    {
        _current_window--;
        update_display_static();
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
void DisplayController::read_enc_values()
{
    if (abs(_enc_count)>120) _enc_count = 0;
    _enc_direction =_encoder.process();
    _enc_count += _enc_direction;
    
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
    case EDIT_POS_HORIZONTAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_POS_VERTICAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_SPEED_FORW:
        _lcd.setCursor(0,0);
        _lcd.print(content+"cm/min");
        break;
    case EDIT_SPEED_DIVE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"cm/min");
        break;
    case EDIT_VOLTAGE_TOLERANCE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;
    case EDIT_ARC_GAIN:
        _lcd.setCursor(0,0);
        _lcd.print(content);
        break;
    case EDIT_ARC_SHORT_CIRCUIT_VOLTAGE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;        
    default:
        break;
    }
}
void DisplayController::set_menu_content(int content_descriptor, int content)
{
    set_menu_content(content_descriptor, String(content));
}
void DisplayController::set_menu_content(const char* upper, const char* lower)
{
    _lcd.clear();
    _lcd.print(upper);
    _lcd.setCursor(0, 1);
    _lcd.print(lower);
}
/*
Update display with PREDEFINED information.
Intended for all transitions that DO NOT print acquired data.
*/
void DisplayController::update_display_static()
{
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
        case 21:
            set_menu_content(MES_POS_VERT, MES_PRESS_EDIT);
            break;
        case 22:
            set_menu_content(MES_RETURN_MAIN_MENU, MES_PRESS_CONFIRM);
            break;
        case 3:
            set_menu_content(MES_CONFIG, MES_PRESS_EDIT);
            break;
        case 30:
            set_menu_content(MES_ARC, MES_PRESS_EDIT);
            break;
        case 300:
            set_menu_content(MES_ARC_SHORT_CIRCUIT_VOLTAGE, MES_PRESS_EDIT);
            break;
        case 301:
            set_menu_content(MES_ARC_VOLTAGE, MES_PRESS_EDIT);
            break;
        case 302:
            set_menu_content(MES_ARC_TOL, MES_PRESS_EDIT);
            break;
        case 303:
            set_menu_content(MES_ARC_GAIN, MES_PRESS_EDIT);
            break;
        case 304:
            set_menu_content(MES_DELAY_INIT_FOWARD_MOVE, MES_PRESS_EDIT);
            break;
        case 31:
            set_menu_content(MES_SPEED, MES_PRESS_EDIT);
            break;
        case 310:
            set_menu_content(MES_SPEED_FORW, MES_PRESS_EDIT);
            break;
        case 311:
            set_menu_content(MES_SPEED_DIVE, MES_PRESS_EDIT);
            break;
        case 32:
            set_menu_content(MES_SAVE, MES_PRESS_CONFIRM);
            break;
        default:
            if (_current_window == 22 || _current_window == 33|| _current_window == 313 || _current_window == 306) set_menu_content(MES_RETURN_MAIN_MENU, MES_PRESS_CONFIRM);
            else if (_current_window == 312 || _current_window == 305) set_menu_content(MES_RETURN_PREVIOUS_MENU, MES_PRESS_CONFIRM);
            break;
    }
    Serial.println("Current. Window: "+String(_current_window));
}
/*
Update display with ACQUIRED DATA information.
Intended for all transitions that print acquired data.
*/
void DisplayController::update_display_dynamic(int content_descriptor, String content)
{
    _lcd.clear();
    switch (content_descriptor)
    {
    case EDIT_POS_HORIZONTAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_POS_VERTICAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_SPEED_FORW:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_SPEED_DIVE:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_VOLTAGE_TOLERANCE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;
    case EDIT_ARC_GAIN:
        _lcd.setCursor(0,0);
        _lcd.print("Ganho: "+content);
        break;
    case EDIT_ARC_SHORT_CIRCUIT_VOLTAGE:
        _lcd.setCursor(0,0);
        _lcd.print(content+" V");
        break;
    case EDIT_DELAY_INIT_FORWARD_MOVE:
        _lcd.setCursor(0,0);
        _lcd.print("Tempo: "+content+" ms");
        break;
    case EDIT_WELDING_VOLTAGE:

    default:
        break;
    }
    _lcd.setCursor(0,1);
    _lcd.print(MES_PRESS_CONFIRM);
    Serial.println("Current. Window: "+String(_current_window));
}
void DisplayController::update_display_dynamic(int content_descriptor,uint8_t content)
{
    update_display_dynamic(content_descriptor, String(content));
}
bool DisplayController::validateWindow(int id)
{
    for (int valid_id : valid_window_ids)
    {
        if (valid_id == id)
        {
            Serial.println("Valid Window");
            return true;
        }
    }
    Serial.println("Window id: "+String(id));
    Serial.println("Inalid Window");
    return false;
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