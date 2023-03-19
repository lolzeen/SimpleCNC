#ifndef MAIN_H
#define MAIN_H

#include <Arduino.h>
#include "MotorController.hpp"
#include "MemoryController.hpp"
#include "DisplayController.hpp"
/* ----- Driver Pins ----- */
// azul = EN, verde = DIR, amarelo = STEP
const int ENX = 23,
         DIRX = 25,
         STEPX = 5,
         ESX1 = 20, 
         ESX2 = 21,
         OUTX = 33,
          ENZ = 29,
         DIRZ = 27,
         STEPZ = 6,
         ESZ1 = 19,
         ESZ2 = 18,
         OUTZ = 35;
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
const uint8_t EIXO_X_DIS = 34; // cm
const uint8_t EIXO_Z_DIS = 33; // cm
const uint8_t CORRECT_HEIGHT = 1;
#endif // MAIN_H