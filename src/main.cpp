#include <Arduino.h>
#include "motorcontroller.hpp"

const int ENX = 13, DIRX = 12, STEPX = 11, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21, OUTX = 22;

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

void es_1()
{
    digitalWrite(ENX, LOW);
}
void es_2()
{
    digitalWrite(ENX, LOW);
}

void setup ()
{
    // pinMode(ENX, OUTPUT);
    // pinMode(DIRX, OUTPUT);
    // pinMode(STEPX, OUTPUT);
    // pinMode(ENZ, OUTPUT);
    // pinMode(DIRZ, OUTPUT);
    // pinMode(STEPZ, OUTPUT);
    // pinMode(ESX1, INPUT_PULLUP);
    // pinMode(ESX2, INPUT_PULLUP);
    // pinMode(ESZ1, INPUT_PULLUP);
    // pinMode(ESZ2, INPUT_PULLUP);
    // attachInterrupt(digitalPinToInterrupt(ESX1), esxR, FALLING);
    // attachInterrupt(digitalPinToInterrupt(ESX2), esxL, FALLING);
    // attachInterrupt(digitalPinToInterrupt(ESZ1), eszU, FALLING);
    // attachInterrupt(digitalPinToInterrupt(ESZ2), eszD, FALLING);
    Serial.begin(9600);
    // using namespace HardwareLeo;
    MotorController eixo_x = MotorController();
    eixo_x.setEsPins(ESX1, ESX2);
    eixo_x.setDriPins(DIRX, ENX, STEPX, OUTX);

    attachInterrupt(digitalPinToInterrupt(ESX1), es_1, FALLING);
    attachInterrupt(digitalPinToInterrupt(ESX2), es_2, FALLING);
    eixo_x.change_dir_state();
    eixo_x.change_en_state();

}

void loop ()
{
    delayMicroseconds(1);
    digitalWrite(STEPX, HIGH);
    delayMicroseconds(1);
    digitalWrite(STEPX, LOW);
}