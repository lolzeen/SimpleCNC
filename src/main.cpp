#define VERBOSE_ 1
#include <Arduino.h>
#include "MotorController.hpp"
#include "DisplayController.hpp"

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
const uint8_t encoder_a = 3; //3;
const uint8_t encoder_b = 2;// 25;
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
int16_t enc_count = 0;
/* ----- ISRs ----- */

void isr_encoder()
{
    // Serial.println("isr_encoder");
    
    isr_enc_flag = true;
}

void setup ()
{
    Serial.begin(9600);
}

void loop ()
{
    eixo_x.run();
    if (eixo_x.get_close_arc()) eixo_z.close_arc();
    eixo_z.run(true);
    display.monitor_user_input();
    // if (isr_enc_flag)
    // {
        // Serial.println("Adjust Menu: "+String(display.get_adjust_menu()));
        if (!display.get_adjust_menu())
        {
            if (display.get_enc_direction() == 1) display.next_window();
            else if (display.get_enc_direction() == -1) display.previous_window();
        }
        else
        {
            switch (display.get_current_window())
            {
                case EDIT_POS_HORIZONTAL:
                    eixo_x.set_speed(10);
                    eixo_x.set_timer_speed();
                    if (display.get_enc_direction() == 1) eixo_x.set_dir_state(FORWARD);
                    else eixo_x.set_dir_state(BACKWARD);
                    eixo_x.set_en_state(HIGH);
                    display.set_menu_content(EDIT_POS_HORIZONTAL, eixo_x.get_speed());
                    while (display.get_adjust_menu())
                    {
                        eixo_x.run();
                        if (enc_count != display.get_enc_count() && eixo_x.get_en_state())
                        {
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
                                    eixo_x.set_en_state(LOW);
                                    display.set_adjust_menu(false);
                                    break;
                                }
                            }
                            display.set_menu_content(EDIT_POS_HORIZONTAL, eixo_x.get_speed());
                            enc_count = display.get_enc_count();
                        }
                        display.monitor_user_input();
                    }
                    break;
                case EDIT_POS_VERTICAL:
                    eixo_z.set_speed(10);
                    eixo_z.set_timer_speed();
                    if (display.get_enc_direction() == 1) eixo_z.set_dir_state(FORWARD);
                    else eixo_z.set_dir_state(BACKWARD);
                    eixo_z.set_en_state(HIGH);
                    display.set_menu_content(EDIT_POS_VERTICAL, eixo_z.get_speed());
                    while (display.get_adjust_menu())
                    {
                        eixo_z.run();
                        if (enc_count != display.get_enc_count() && eixo_z.get_en_state())
                        {
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
                                    eixo_z.set_en_state(LOW);
                                    display.set_adjust_menu(false);
                                    break;
                                }
                            }
                            display.set_menu_content(EDIT_POS_VERTICAL, eixo_z.get_speed());
                            enc_count = display.get_enc_count();
                        }
                        display.monitor_user_input();
                    }
                    break;
                default:
                    while (display.get_adjust_menu())
                    {
                        if (display.get_enc_count() != enc_count)
                        {
                            switch (display.get_current_window())
                            {
                                case EDIT_SPEED_FORW:
                                    eixo_x.set_speed(eixo_x.get_speed() + display.get_enc_direction());
                                    display.set_menu_content(EDIT_SPEED_FORW, eixo_x.get_speed());
                                    break;
                                case EDIT_SPEED_DIVE:
                                    eixo_z.set_speed(eixo_z.get_speed() + display.get_enc_direction());
                                    display.set_menu_content(EDIT_SPEED_DIVE, eixo_z.get_speed());
                                    break;
                                case EDIT_ARC_GAIN:
                                    eixo_z.set_arc_controller_gain(eixo_z.get_arc_controller_gain()+display.get_enc_direction());
                                    display.set_menu_content(EDIT_ARC_GAIN, eixo_z.get_arc_controller_gain());
                                    break;
                                case EDIT_ARC_SHORT_CIRCUIT_VOLTAGE:
                                    eixo_z.set_arc_short_circuit_voltage(eixo_z.get_arc_short_circuit_voltage()+display.get_enc_direction());
                                    display.update_display_dynamic(EDIT_ARC_SHORT_CIRCUIT_VOLTAGE, eixo_z.get_arc_short_circuit_voltage());
                                    break;
                                case EDIT_WELDING_VOLTAGE:
                                    eixo_z.set_welding_voltage(eixo_z.get_welding_voltage() + display.get_enc_direction());
                                    display.update_display_dynamic(EDIT_WELDING_VOLTAGE, eixo_z.get_welding_voltage());
                                    break;
                                case EDIT_VOLTAGE_TOLERANCE:
                                    eixo_z.set_voltage_tolerance(eixo_z.get_voltage_tolerance() + display.get_enc_direction());
                                    display.update_display_dynamic(EDIT_VOLTAGE_TOLERANCE, eixo_z.get_voltage_tolerance());
                                    break;
                                case EDIT_DELAY_INIT_FORWARD_MOVE:
                                    eixo_x.set_delay_init_forward_move(eixo_x.get_delay_init_forward_move() + display.get_enc_direction());
                                    display.update_display_dynamic(EDIT_DELAY_INIT_FORWARD_MOVE, eixo_x.get_delay_init_forward_move());
                                    break;
                                default:
                                    break;
                            }
                            enc_count = display.get_enc_count();
                        }
                        display.monitor_user_input();
                    }
            }
        }
        enc_count = 0;
        display.set_enc_count(0);
        // isr_enc_flag = false;
    // }
    if (display.get_init_process())
    {
        display.countdown_window();
        display.process_window();
        eixo_z.start_process();
        eixo_x.start_process();
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
}