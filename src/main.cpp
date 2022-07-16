#include <Arduino.h>
#include "MotorController.hpp"
#include "UserInterface.hpp"
#include "DisplayController.hpp"
#include "Calculator.hpp"

/* ----- Driver Pins ----- */
// const int ENX = 13, DIRX = 12, STEPX = 11, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21, OUTX = 22, OUTZ = 23;
const int ENX = 38, DIRX = 41, STEPX = 39, ENZ = 37, DIRZ = 36, STEPZ = 35, ESX1 = 18, ESX2 = 19, ESZ1 = 26, ESZ2 = 27, OUTX = 28, OUTZ = 29; // testing only
DriverPins driver_x_pins = {ESX1, ESX2, DIRX, ENX, STEPX, OUTX};
// DriverPins driver_z_pins = {ESZ1, ESZ2,  DIRZ, ENZ, STEPZ, OUTZ};

/* ----- Display Pins ----- */
const uint8_t display_rs = 13;
const uint8_t display_en = 12;
const uint8_t display_d4 = 11;
const uint8_t display_d5 = 10;
const uint8_t display_d6 = 9;
const uint8_t display_d7 = 8; 
DisplayPins display_pins = {display_rs, display_en, display_d4, display_d5, display_d6, display_d7};

/* ---- Input Pins ----- */
const uint8_t button_change = 4;
const uint8_t button_select = 5;
const uint8_t potentiometer = A0;
InputPins input_pins = {button_change, button_select, potentiometer};

/* ---- Driver Parameters ----- */
const DriverParameters driver_params = {20000};

MotorController eixo_x(driver_x_pins, driver_params);
// MotorController eixo_z(driver_z_pins, driver_params);

UserInterface interface(input_pins);
DisplayController display;

/* ----- ISRs ----- */
void isr_x1()
{
    digitalWrite(driver_x_pins._EN, LOW);
    // eixo_x.move = false;
    eixo_x.set_en_state(false);
    noTone(driver_x_pins._STEP);
    eixo_x.set_pos(HOME);
    interface.set_init_process(false);
}
void isr_x2()
{
    digitalWrite(driver_x_pins._EN, LOW);
    eixo_x.set_en_state(false);
    noTone(driver_x_pins._STEP);
    // eixo_x.move = false;
    eixo_x.set_pos(FINISH);
    interface.set_init_process(false);
    Serial.println("interrupt");
}
// void isr_z1()
// {
//     eixo_x.set_pos(HOME);
// }
// void isr_z2()
// {
//     eixo_x.set_pos(FINISH);
// }

void setup ()
{
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES1), isr_x1, FALLING);
    attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES2), isr_x2, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES1), isr_z1, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES2), isr_z2, FALLING);
    eixo_x.set_distance(30);
    // eixo_z.set_distance(30);
    
}

void loop ()
{
    Serial.println(".");
    interface.get_button_input();
    if (interface.get_change_window())
    {
        display.next_window();
        interface.set_change_window(false);
    }
    while (interface.get_change_menu())
    {
        if (display.get_current_window() == 0)
        {
            interface.set_init_process(true);
            interface.set_change_menu(false);
        }
        else
        {
            interface.get_pot_input();
            if (interface.get_adjust_menu())
            {
                display.set_menu_content(conv_pot_speed(interface.get_pot_value()));
            }
            interface.get_button_input();
        }
    }
    if (interface.get_init_process())
    {
        Serial.println("Processsing!");
        eixo_x.set_freq(calc_freq(display.get_feed_speed(), driver_params));
        eixo_x.set_en_state(true);
        digitalWrite(driver_x_pins._EN, HIGH);
        // eixo_x.move = true;
        tone(driver_x_pins._STEP, eixo_x.get_process_params()._frequency);

    //     // while pos < max_dist
    //     // todo: verify if all process parameters are denifed
    //     // todo: start routine
    //     // todo: return home when both buttons are pressed
    //     // while (eixo_x.move)
    //     // {
    //     //     analogWrite(3, 20);
    //     // }
    }
    // delay(200);
}

