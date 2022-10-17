#define VERBOSE_ 1
#include <Arduino.h>
#include "MotorController.hpp"
#include "UserInterface.hpp"
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
MotorController eixo_x(driver_x_pins, driver_params, EIXO_X_ID, EIXO_X_DIS);
MotorController eixo_z(driver_z_pins, driver_params, EIXO_Z_ID, EIXO_Z_DIS);
UserInterface interface(input_pins);
DisplayController display;

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
    interface.read_enc_values();
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
    eixo_z.run();
    interface.button_press(display.get_current_window());
    if (isr_enc_flag)
    {
        // if (interface.validate_enc_values())
        if (enc_count != interface.get_enc_count())
        {
            if (!interface.get_adjust_menu())
            {
                if (interface.get_enc_direction() == 1)
                {
                    display.next_window();
                    // Serial.println("Display next window");
                }
                else if (interface.get_enc_direction() == -1)
                {
                    display.previous_window();
                    // Serial.println("Display previous window");
                }
            }
            while (interface.get_adjust_menu())
            {
                if (enc_count != interface.get_enc_count())
                {
                    if (display.get_current_window() == 2)
                    {
                        eixo_x.set_speed(eixo_x.get_speed() + interface.get_enc_direction());
                        display.set_menu_content(eixo_x.get_speed());
                    }
                    else if (display.get_current_window() == 3)
                    {
                        eixo_z.set_speed(eixo_z.get_speed() + interface.get_enc_direction());
                        display.set_menu_content(eixo_z.get_speed());
                    }
                    display.update_display();
                    enc_count = interface.get_enc_count();
                }
                interface.button_press(display.get_current_window());
            }
        }
        enc_count = 0;
        interface.set_enc_count(0);
        isr_enc_flag = false;
    }
    if (interface.get_init_process())
    {
        display.countdown_window();
        display.process_window();
        eixo_x.start_process();
        eixo_z.start_process();
        interface.set_init_process(false);
    }
    if (interface.get_return_home())
    {
        display.process_window();
        eixo_x.return_home();
        delay(200);
        eixo_z.return_home();
        interface.set_return_home(false);
    }
    // FIXME: 
    // if (!eixo_x.get_en_state() && !eixo_z.get_en_state())
    // {
    //     display.set_current_window(0);
    //     display.update_display();
    // } 
    // Serial.println("..");
}