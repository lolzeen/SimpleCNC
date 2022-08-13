#include <Arduino.h>
#include "MotorController.hpp"
#include "UserInterface.hpp"
#include "DisplayController.hpp"


/* ----- Driver Pins ----- */
const int ENX = 38, DIRX = 41, STEPX = 5, ENZ = 32, DIRZ = 35, STEPZ = 6, ESX1 = 20, ESX2 = 21, ESZ1 = 19, ESZ2 = 18, OUTX = 28, OUTZ = 29;
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
const uint8_t button_change = 24;
const uint8_t button_select = 25;
const uint8_t potentiometer = A0;
InputPins input_pins = {button_change, button_select, potentiometer};

/* ---- Driver Parameters ----- */
const uint16_t driver_params = 8000;
// bool step_x_state = LOW;
// bool step_z_state = LOW;
//FIXME

MotorController eixo_x(driver_x_pins, driver_params);
MotorController eixo_z(driver_z_pins, driver_params);
UserInterface interface(input_pins);
DisplayController display;


bool isrx_1 = false;
bool isrx_2 = false;
bool isrz_1 = false;
bool isrz_2 = false;
/* ----- ISRs ----- */
void isr_x1()
{
    noInterrupts();
    digitalWrite(driver_x_pins._EN, LOW);
    // digitalWrite(driver_x_pins._STEP, LOW);
    isrx_1 = true;
    Serial.println("isrx1");
    interrupts();
}
// void isr_x2()
// {
    // noInterrupts();
//     digitalWrite(driver_x_pins._EN, LOW);
//     isrx_2 = true;
// interrupts();
// }
void isr_z1()
{
    noInterrupts();
    digitalWrite(driver_z_pins._EN, LOW);
    // digitalWrite(driver_z_pins._STEP, LOW);
    isrz_1 = true;
    Serial.println("isrz1");
    interrupts();
}
// void isr_z2()
// {
    // noInterrupts();
//     digitalWrite(driver_z_pins._EN, LOW);
//     isrz_1 = true;
// interrupts();
// }

void setup ()
{
    Serial.begin(9600);
    attachInterrupt(INT3, isr_x1, HIGH); // i0
    // attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES2), isr_x2, LOW); // i1
    attachInterrupt(INT4, isr_z1, HIGH); // i2
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES2), isr_z2, LOW); // i3
    eixo_x.set_distance(30);
    eixo_z.set_distance(30);
    
}

void loop ()
{
    if(isrx_1)
    {
        eixo_x.stop_timers(3);
        eixo_x.set_en_state(false);
        eixo_x.set_last_pos(HOME);
        Serial.println("isrx_1: HOME");
        isrx_1 = false;

    }
    else if (isrx_2)
    {
        eixo_x.stop_timers(3);
        eixo_x.set_en_state(false);
        eixo_x.set_last_pos(FINISH);
        Serial.println("isrx_2: FINISH");
        isrx_2 = false;
    }
    else if (isrz_1)
    {
        eixo_z.stop_timers(4);
        eixo_z.set_en_state(false);
        eixo_z.set_last_pos(HOME);
        Serial.println("isrz_1: HOME");
        isrz_1 = false;
    }
    else if (isrz_2)
    {
        eixo_z.stop_timers(4);
        eixo_z.set_en_state(false);
        eixo_z.set_last_pos(FINISH);
        Serial.println("isrz_2: FINISH");
        isrz_2 = false;
    }
    
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
        else if (display.get_current_window() == 1)
        {
            interface.set_return_home(true);
            interface.set_change_menu(false);
        }
        else if (display.get_current_window() == 2)
        {
            interface.get_pot_input();
            if (interface.get_adjust_menu())
            {
                eixo_x.set_speed(interface.get_pot_value());
                display.set_feed_speed(eixo_x.get_speed()); // IMPROVEMENT: same value stored 2 times
                
            }
            interface.get_button_input();
        }
        else if (display.get_current_window() == 3)
        {
            interface.get_pot_input();
            if (interface.get_adjust_menu())
            {
                eixo_z.set_speed(interface.get_pot_value());
                display.set_dive_speed(eixo_z.get_speed());
            }
            interface.get_button_input();
        }
    }
    if (interface.get_init_process())
    {
        eixo_x.start_process();
        eixo_z.start_process();
        interface.set_init_process(false);
    }
    if (interface.get_return_home())
    {
        eixo_x.return_home();
        eixo_z.return_home();
        interface.set_return_home(false);
    }
}

// {
//     digitalWrite(driver_x_pins._STEP, step_x_state);
//     step_x_state = !step_x_state;
// }
// ISR(TIMER4_COMPA_vect)
// {
//     digitalWrite(driver_z_pins._STEP, step_z_state);
//     step_z_state = !step_z_state;
// }
// FIXME