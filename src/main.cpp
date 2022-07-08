#include <Arduino.h>
#include "motorcontroller.hpp"
#include "userinterface.hpp"
#include <LiquidCrystal.h>

/* ----- Driver Pins ----- */
// const int ENX = 13, DIRX = 12, STEPX = 11, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21, OUTX = 22, OUTZ = 23;
const int ENX = 53, DIRX = 52, STEPX = 51, ENZ = 37, DIRZ = 36, STEPZ = 35, ESX1 = 24, ESX2 = 25, ESZ1 = 26, ESZ2 = 27, OUTX = 28, OUTZ = 29; // testing only
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
const uint8_t button_change = 47;
const uint8_t button_select = 49;
const uint8_t potentiometer = A0;
InputPins input_pins = {button_change, button_select, potentiometer};

// TODO: move to movements lib
/*
void moveLeft()
{
    digitalWrite(ENX, HIGH);
    digitalWrite(DIRX, HIGH);
}
void moveRight()
{
    digitalWrite(ENX, HIGH);
    digitalWrite(DIRX, LOW);
}
void moveUp()
{
    digitalWrite(ENZ, HIGH);
    digitalWrite(DIRZ, HIGH);
}
void moveDown()
{
    digitalWrite(ENZ, HIGH);
    digitalWrite(DIRZ, LOW);
}

void returnHome()
{
    if (ax != 1)
    {
        moveLeft();
        // call speed function set to high
    }
    if (az != 1)
    {
        
        // call speed function set to high
    }
}

void routine(float x_speed, float y_speed)
{
    // execute routine acording to desired speeds
}
*/

/* ----- Axis Objects ----- */
// MotorController eixo_x(driver_x_pins);
// MotorController eixo_z(driver_z_pins);

/* ----- User Interface Object ----- */
UserInterface interface = UserInterface(input_pins, display_pins);

/* ----- ISRs ----- */
// void isr_x1()
// {
//     eixo_x.change_en_state();
//     eixo_x.change_dir_state();
// }
// void isr_z()
// {
//     eixo_z.change_en_state();
    // eixo_z.change_dir_state();
// }

void setup ()
{
    Serial.begin(9600);
    interface.initialize_display();

    // eixo_x.change_en_state();
    // eixo_z.change_en_state();

    // attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES1), isr_x1, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES2), isr_x1, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES1), isr_z, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES2), isr_z, FALLING);
    
}

const uint8_t button_ch = 1;
const uint8_t button_se = 2;

void loop ()
{
    Serial.println(".");
    interface.get_button_input(button_ch);
    interface.get_button_input(button_se);
    delay(100);
    Serial.println(".");
    // interface.display_menu();
}

/* OLD VOID LOOP
void loop ()
{
    // read the state of the switch into a local variable:
    // int reading1 = digitalRead(button_pin_1);
    // int reading2 = digitalRead(button_pin_2);
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    // if (reading1 != last_state_button_1)
    {
    // reset the debouncing timer
    // lastDebounceTime = millis();
    }

    // if ((millis() - lastDebounceTime) > debounceDelay)
    {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

        // if the button state has changed:
    //     if (reading1 != button_state_1)
    //     {
    //         button_state_1 = reading1;

    //         // only toggle the LED if the new button state is HIGH
    //         if (button_state_1 == HIGH)
    //         {
    //             current_menu = current_menu + 1;
    //             interface.display_menu(lcd, current_menu);
    //             Serial.println(current_menu);
    //         }
    //     }
    // }
    // // If the switch changed, due to noise or pressing:
    // if (reading2 != last_state_button_2)
    // {
    // // reset the debouncing timer
    // lastDebounceTime = millis();
    // }

    // if ((millis() - lastDebounceTime) > debounceDelay)
    // {
    // // whatever the reading is at, it's been there for longer than the debounce
    // // delay, so take it as the actual current state:

    //     // if the button state has changed:
    //     if (reading2 != button_state_2)
    //     {
    //         button_state_2 = reading2;

    //         // only toggle the LED if the new button state is HIGH
    //         if (button_state_2 == HIGH)
    //         {
    //             interface.adjust_item(lcd, current_menu);
    //         }
    //     }
    // }
    // // save the reading. Next time through the loop, it'll be the lastButtonState:
    // last_state_button_1 = reading1;
    // last_state_button_2 = reading2;
    
    // delay(2000);
}
*/