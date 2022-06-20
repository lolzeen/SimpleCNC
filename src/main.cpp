#include <Arduino.h>

const int ENX = 11, DIRX = 12, STEPX = 13, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21;
volatile int ax = 0, az = 0;


// ISR
void esxR()
{
    digitalWrite(ENX, LOW);
    ax = 1;
}
void esxL()
{
    digitalWrite(ENX, LOW);
    ax = -1;
}
void eszU()
{
    digitalWrite(ENZ, LOW);
    az = 1;
}
void eszD()
{
    digitalWrite(ENZ, LOW);
    az = -1;
}

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

void setup ()
{
    pinMode(ENX, OUTPUT);
    pinMode(DIRX, OUTPUT);
    pinMode(STEPX, OUTPUT);
    pinMode(ENZ, OUTPUT);
    pinMode(DIRZ, OUTPUT);
    pinMode(STEPZ, OUTPUT);
    pinMode(ESX1, INPUT_PULLUP);
    pinMode(ESX2, INPUT_PULLUP);
    pinMode(ESZ1, INPUT_PULLUP);
    pinMode(ESZ2, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(ESX1), esxR, FALLING);
    attachInterrupt(digitalPinToInterrupt(ESX2), esxL, FALLING);
    attachInterrupt(digitalPinToInterrupt(ESZ1), eszU, FALLING);
    attachInterrupt(digitalPinToInterrupt(ESZ2), eszD, FALLING);
}

void loop ()
{

}