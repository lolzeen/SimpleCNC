#include <Arduino.h>
#include "motorcontroller.hpp"
#include "userinterface.hpp"
#include <LiquidCrystal.h>

/* ----- Driver Pins ----- */
// const int ENX = 13, DIRX = 12, STEPX = 11, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21, OUTX = 22, OUTZ = 23;
const int ENX = 53, DIRX = 52, STEPX = 51, ENZ = 36, DIRZ = 38, STEPZ = 400, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21, OUTX = 22, OUTZ = 23; // testing only
DriverPins driver_x_pins = {ESX1, ESX2, DIRX, ENX, STEPX, OUTX};
// DriverPins driver_z_pins = {ESZ1, ESZ2,  DIRZ, ENZ, STEPZ, OUTZ};

/* ----- Display Pins ----- */
const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8;

/* ----- Display Object ----- */
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

/* ---- Input Pins ----- */
InputPins input_pins = {47, 49, A0};

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
MotorController eixo_x(driver_x_pins);
// MotorController eixo_z(driver_z_pins);

/* ----- User Interface Object ----- */
UserInterface interface = UserInterface(input_pins);

/* ----- ISRs ----- */
void isr_x1()
{
    eixo_x.change_en_state();
    eixo_x.change_dir_state();
}
// void isr_z()
// {
//     eixo_z.change_en_state();
    // eixo_z.change_dir_state();
// }

/* ----- Input Pins ----- */
// const int button_pin_1 = 47, button_pin_2 = 49, pot_pin = A0;
// int button_state_1, button_state_2, pot_value = 0;             // the current reading from the input pin

/* ----- Buttons State ----- */
// int last_state_button_1 = LOW;   // the previous reading from the input pin
// int last_state_button_2 = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
// unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
// unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

/* ----- Display Info ----- */


void setup ()
{
    Serial.begin(9600);

    eixo_x.change_en_state();
    // eixo_z.change_en_state();

    attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES1), isr_x1, FALLING);
    attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES2), isr_x1, FALLING);


    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES1), isr_z, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES2), isr_z, FALLING);


    

    lcd.begin(16,2);
    lcd.clear();
    lcd.print("     LASIN");
    delay(2000);
    interface.display_menu(lcd);
}

void loop ()
{
    // read the state of the switch into a local variable:
    // int reading1 = digitalRead(button_pin_1);
    // int reading2 = digitalRead(button_pin_2);
    // check to see if you just pressed the button
    // (i.e. the input went from LOW to HIGH), and you've waited long enough
    // since the last press to ignore any noise:

    // If the switch changed, due to noise or pressing:
    if (reading1 != last_state_button_1)
    {
    // reset the debouncing timer
    lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading1 != button_state_1)
        {
            button_state_1 = reading1;

            // only toggle the LED if the new button state is HIGH
            if (button_state_1 == HIGH)
            {
                current_menu = current_menu + 1;
                interface.display_menu(lcd, current_menu);
                Serial.println(current_menu);
            }
        }
    }
    // If the switch changed, due to noise or pressing:
    if (reading2 != last_state_button_2)
    {
    // reset the debouncing timer
    lastDebounceTime = millis();
    }

    if ((millis() - lastDebounceTime) > debounceDelay)
    {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

        // if the button state has changed:
        if (reading2 != button_state_2)
        {
            button_state_2 = reading2;

            // only toggle the LED if the new button state is HIGH
            if (button_state_2 == HIGH)
            {
                interface.adjust_item(lcd, current_menu);
            }
        }
    }
    // save the reading. Next time through the loop, it'll be the lastButtonState:
    last_state_button_1 = reading1;
    last_state_button_2 = reading2;
    
    // delay(2000);
}