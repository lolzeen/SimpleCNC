#include <Arduino.h>
#include "MotorController.hpp"
#include "UserInterface.hpp"
#include "DisplayController.hpp"

/* ----- Driver Pins ----- */
// azul = EN, verde = DIR, amarelo = STEP
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
const uint8_t button = 2;
const uint8_t encoder_a = 3;
const uint8_t encoder_b = 24;
InputPins input_pins = {button, encoder_a, encoder_b};

/* ---- Driver Parameters ----- */
const uint16_t driver_params = 8000; // 8000 pulses per revolution

MotorController eixo_x(driver_x_pins, driver_params);
MotorController eixo_z(driver_z_pins, driver_params);
UserInterface interface(input_pins);
DisplayController display;

bool isrx_home_flag = false;
bool isrx_finish_flag = false;
bool isrz_home_flag = false;
bool isrz_finish_flag = false;
bool isr_enc_flag = false;
int8_t enc_count = 0;
/* ----- ISRs ----- */
void isr_x1()
{
    noInterrupts();
    eixo_x.set_en_state(false);
    isrx_home_flag = true;
    // Serial.println("isr_x1");
    interrupts();
}
void isr_x2()
{
    noInterrupts();
    eixo_x.set_en_state(false);
    isrx_finish_flag = true;
    // Serial.println("isr_x2");
    interrupts();
}
void isr_z1()
{
    noInterrupts();
    eixo_z.set_en_state(false);
    isrz_home_flag = true;
    // Serial.println("isr_z1");
    interrupts();
}
void isr_z2()
{
    noInterrupts();
    eixo_z.set_en_state(false);
    isrz_home_flag = true;
    // Serial.println("isr_z2");
    interrupts();
}

void isr_button()
{
    // TODO remove this code
    // this type of aproach should be implemented in the main loop or triggered by a timer interrupt
    static uint16_t state = 0;
    state = (state << 1) | !digitalRead(input_pins.button) | 0xe000;
    if (0xf000 == state)
    {
        interface.button_press(display.get_current_window());
    }
}
void isr_encoder()
{
    // Serial.println("isr_encoder");
    interface.read_enc_values();
    isr_enc_flag = true;
    // update the display from here or set a counter in order to keep up with the knob movment
    // TODO
}

void setup ()
{
    Serial.begin(9600);
    // attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES1), isr_x1, HIGH); // i0
    // attachInterrupt(INT3, isr_x1, HIGH); // i0
    // attachInterrupt(INT2, isr_x2, HIGH); // i1
    // attachInterrupt(digitalPinToInterrupt(ESZ1), isr_z1, HIGH); // i2
    // attachInterrupt(digitalPinToInterrupt(ESZ2), isr_z2, HIGH); // i0
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES2), isr_z2, LOW); // i3
    // attachInterrupt(digitalPinToInterrupt(input_pins.button), isr_button, CHANGE); // i2
    attachInterrupt(digitalPinToInterrupt(input_pins.encoder_a), isr_encoder, CHANGE);
    eixo_x.set_distance(30);
    eixo_x.set_speed(10);
    eixo_z.set_distance(30);
    eixo_z.set_speed(10);
    interface.read_enc_values();
}

void loop ()
{
    if(isrx_home_flag)
    {
        eixo_x.stop_timers(3);
        eixo_x.set_last_pos(HOME);
        isrx_home_flag = false;
        // Serial.println("isrx_home_flag: HOME");
    }
    else if (isrx_finish_flag)
    {
        eixo_x.stop_timers(3);
        eixo_x.set_last_pos(FINISH);
        isrx_finish_flag = false;
        // Serial.println("isrx_finish_flag: FINISH");
    }
    else if (isrz_home_flag)
    {
        eixo_z.stop_timers(4);
        eixo_z.set_last_pos(HOME);
        isrz_home_flag = false;
        // Serial.println("isrz_home_flag: HOME");
    }
    else if (isrz_finish_flag)
    {
        eixo_z.stop_timers(4);
        eixo_z.set_last_pos(FINISH);
        isrz_finish_flag = false;
        // Serial.println("isrz_finish_flag: FINISH");
    }
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
            }
        }
        enc_count = 0;
        interface.set_enc_count(0);
        isr_enc_flag = false;
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