#define VERBOSE_ 1
#include <Arduino.h>
#include "MotorController.hpp"
#include "DisplayController.hpp"
// eixo z não realiza a função return home
// endswitch 4 home faz o eixo z realizar um cartridge return e depois corre infinito
// endswithces do eixo z não respondem como deveriam
/* ----- Driver Pins ----- */
// azul = EN, verde = DIR, amarelo = STEP
const int ENX = 23, DIRX = 25, STEPX = 5, ENZ = 29, DIRZ = 27, STEPZ = 6, ESX1 = 20, ESX2 = 21, ESZ1 = 19, ESZ2 = 18, OUTX = 33, OUTZ = 35;
DriverPins driver_x_pins = {ESX1, ESX2, DIRX, ENX, STEPX, OUTX};
DriverPins driver_z_pins = {ESZ1, ESZ2,  DIRZ, ENZ, STEPZ, OUTZ};

/* ----- Display Pins ----- */
const uint8_t display_rs = 13;
const uint8_t display_en = 12;
const uint8_t display_d4 = 11;
const uint8_t display_d5 = 10;
const uint8_t display_d6 = 9;
const uint8_t display_d7 = 8;
DisplayPins display_pins = {display_rs, display_en, display_d4, display_d5, display_d6, display_d7};

/* ---- Input Pins ----- */
const uint8_t button = 31;
const uint8_t encoder_a = 2; //3;
const uint8_t encoder_b = 3;// 25;
InputPins input_pins = {button, encoder_a, encoder_b};

/* ---- Driver Parameters ----- */
const uint16_t driver_params = 8000; // 8000 pulses per revolution
const uint8_t EIXO_X_ID = 3;
const uint8_t EIXO_Z_ID = 4;
const uint8_t EIXO_X_DIS = 34;
const uint8_t EIXO_Z_DIS = 33;
const uint8_t CORRECT_HEIGHT = 1;
MotorController eixo_x(driver_x_pins, driver_params, EIXO_X_ID, EIXO_X_DIS);
MotorController eixo_z(driver_z_pins, driver_params, EIXO_Z_ID, EIXO_Z_DIS);
DisplayController display(input_pins);

bool isrx_home_flag = false;
bool isrx_finish_flag = false;
bool isrz_home_flag = false;
bool isrz_finish_flag = false;
bool isr_enc_flag = false;
int8_t enc_count = 0;
/* ----- ISRs ----- */

void isr_encoder()
{
    // Serial.println("isr_encoder");
    display.read_enc_values();
    isr_enc_flag = true;
}

void setup ()
{
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(input_pins.encoder_a), isr_encoder, CHANGE);
}

void loop ()
{
    eixo_x.run();
    eixo_z.run(true);
    display.button_press(false);
    if (isr_enc_flag) // TODO: 
    {
        // if (display.validate_enc_values())
        if (enc_count != display.get_enc_count())
        {
            if (!display.get_adjust_menu())
            {
                Serial.println("Current window: "+String(display.get_current_window()));
                if (display.get_enc_direction() == 1) display.next_window();
                else if (display.get_enc_direction() == -1) display.previous_window();
            }
            else
            {
                while (display.get_adjust_menu())
                {
                    if (enc_count != display.get_enc_count())
                    {
                        switch (display.get_current_window())
                        {
                        case POS_EDIT_HORIZONTAL:
                            eixo_x.set_dir_state(FORWARD);
                            eixo_x.set_speed(10);
                            eixo_x.set_timer_speed();
                            while (display.get_adjust_menu())
                            {
                                display.set_menu_content(POS_EDIT_HORIZONTAL, String(eixo_x.get_speed()));
                                if (eixo_x.end_switch())
                                {
                                    display.set_adjust_menu(false);
                                    break;
                                }
                                if (display.get_enc_direction() == 1)
                                {
                                    eixo_x.set_speed(eixo_x.get_speed()+10);
                                }
                                else if(display.get_enc_direction() == -1)
                                {
                                    eixo_x.set_speed(eixo_x.get_speed()-10);
                                    if (eixo_x.get_speed() < 0)
                                    {
                                        eixo_x.set_speed(10);
                                        eixo_x.set_dir_state(!eixo_x.get_dir_state());
                                        eixo_x.set_timer_speed();
                                    }
                                    else
                                    {
                                        display.set_adjust_menu(false);
                                        break;
                                    }
                                }
                                display.button_press();
                            }
                            break;
                        case POS_EDIT_VERTICAL:
                            eixo_z.set_dir_state(FORWARD);
                            eixo_z.set_speed(10);
                            eixo_z.set_timer_speed();
                            while (display.get_adjust_menu())
                            {
                                display.set_menu_content(POS_EDIT_VERTICAL, String(eixo_z.get_speed()));
                                if (eixo_z.end_switch())
                                {
                                    display.set_adjust_menu(false);
                                    break;
                                }
                                if (display.get_enc_direction() == 1)
                                {
                                    eixo_z.set_speed(eixo_z.get_speed()+10);
                                }
                                else if(display.get_enc_direction() == -1)
                                {
                                    eixo_z.set_speed(eixo_z.get_speed()-10);
                                    if (eixo_z.get_speed() < 0)
                                    {
                                        eixo_z.set_speed(10);
                                        eixo_z.set_dir_state(!eixo_z.get_dir_state());
                                        eixo_z.set_timer_speed();
                                    }
                                    else
                                    {
                                        display.set_adjust_menu(false);
                                        break;
                                    }
                                }
                                display.button_press();
                            }
                            break;
                        case SPEED_EDIT_HORIZONTAL:
                            eixo_x.set_speed(eixo_x.get_speed() + display.get_enc_direction());
                            display.set_menu_content(SPEED_EDIT_HORIZONTAL, String(eixo_x.get_speed()));
                            break;
                        case SPEED_EDIT_VERTICAL:
                            eixo_z.set_speed(eixo_z.get_speed() + display.get_enc_direction());
                            display.set_menu_content(SPEED_EDIT_VERTICAL, String(eixo_z.get_speed()));
                            break;
                        case ARC_GAIN_EDIT:
                            eixo_z.set_arc_controller_gain(eixo_z.get_arc_controller_gain()+display.get_enc_direction());
                            display.set_menu_content(eixo_z.get_arc_controller_gain());
                            break;
                        case ARC_SHORT_CIRCUIT_VOLTAGE_EDIT:
                            eixo_z.set_arc_short_circuit_voltage(eixo_z.get_arc_short_circuit_voltage()+display.get_enc_direction());
                            display.set_menu_content(eixo_z.get_arc_short_circuit_voltage());
                            break;
                        default:
                            break;
                        }
                        display.update_display();
                        enc_count = display.get_enc_count();
                    }
                    display.button_press();
                }
            }
            
        }
        enc_count = 0;
        display.set_enc_count(0);
        isr_enc_flag = false;
    }
    if (display.get_init_process())
    {
        display.countdown_window();
        display.process_window();
        eixo_x.start_process();
        eixo_z.start_process(CORRECT_HEIGHT);
        // eixo_z.change_speed_while_running();
        display.set_init_process(false);
    }
    if (display.get_return_home())
    {
        display.process_window();
        eixo_x.return_home();
        delay(200);
        eixo_z.return_home();
        display.set_return_home(false);
    }
    // FIXME: 
    // if (!eixo_x.get_en_state() && !eixo_z.get_en_state())
    // {
    //     display.set_current_window(0);
    //     display.update_display();
    // } 
    // Serial.println("..");
}