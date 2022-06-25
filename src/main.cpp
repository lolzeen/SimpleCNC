#include <Arduino.h>
#include "motorcontroller.hpp"

const int ENX = 13, DIRX = 12, STEPX = 11, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21, OUTX = 22, OUTZ = 23;

DriverPins driver_x_pins = {ESX1, ESX2, DIRX, ENX, STEPX, OUTX};
// DriverPins driver_z_pins = {ESZ1, ESZ2, DIRZ, ENZ, STEPZ, OUTZ};

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

// ISRs
MotorController eixo_x(driver_x_pins);
// MotorController eixo_z(driver_z_pins);

void es_x()
{
    // digitalWrite(ENX, LOW);
    eixo_x.change_en_state();
    eixo_x.change_dir_state();
}
// void es_z()
// {
//     // digitalWrite(ENX, LOW);
//     eixo_z.change_en_state();
    // eixo_z.change_dir_state();
// }

void setup ()
{
    Serial.begin(9600);

    eixo_x.change_en_state();
    // eixo_z.change_en_state();

    attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES1), es_x, FALLING);
    attachInterrupt(digitalPinToInterrupt(driver_x_pins._ES2), es_x, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES1), es_z, FALLING);
    // attachInterrupt(digitalPinToInterrupt(driver_z_pins._ES2), es_z, FALLING);

}

void loop ()
{
    delayMicroseconds(1);
    digitalWrite(STEPX, HIGH);
    delayMicroseconds(1);
    digitalWrite(STEPX, LOW);
}