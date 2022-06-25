#include "motorcontroller.hpp"

// namespace HardwareLeo
// {
    // Controller::Controller(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d) : es_pin_x_r(pin_x_r), es_pin_x_l(pin_x_l), es_pin_z_u(pin_z_u), es_pin_z_d(pin_z_d);

    MotorController::MotorController()
    {
        // Intentionally Empty;
    }

    MotorController::~MotorController()
    {
        // Intentionally Empty;
    }

    //

    // void MotorController::es_interrupts()
    // {
    //     attachInterrupt(digitalPinToInterrupt(MotorController::es_inp.pin_1), es_1, FALLING);
    //     attachInterrupt(digitalPinToInterrupt(MotorController::es_inp.pin_2), MotorController::es_2(), FALLING);
    // }

    // void es_1()
    // {
    //     digitalWrite(MotorController::es_inp.pin_1, LOW);
    // }
    // void MotorController::es_2()
    // {
    //     digitalWrite(MotorController::es_inp.pin_2, LOW);
    // }

    void MotorController::setEsPins(int pin_1, int pin_2)
    {
        MotorController::es_inp.pin_1 = pin_1;
        MotorController::es_inp.pin_2 = pin_2;
        pinMode(MotorController::es_inp.pin_1, INPUT_PULLUP);
        pinMode(MotorController::es_inp.pin_2, INPUT_PULLUP);
        Serial.print("End Switches Pins are set!");
    }

    void MotorController::setDriPins(int pin_dir, int pin_enable, int pin_step, int pin_output)
    {
        MotorController::dri_io.dir = pin_dir;
        MotorController::dri_io.enable = pin_enable;
        MotorController::dri_io.step = pin_step;
        MotorController::dri_io.output = pin_output;
        pinMode(MotorController::dri_io.dir, OUTPUT);
        pinMode(MotorController::dri_io.enable, OUTPUT);
        pinMode(MotorController::dri_io.step, OUTPUT);
        pinMode(MotorController::dri_io.output, INPUT);
        Serial.print("Driver Pins are set!");
    }

    void MotorController::change_dir_state()
    {
        if (digitalRead(MotorController::dri_io.dir))
        {
            digitalWrite(MotorController::dri_io.dir, LOW);
        }
        else
        {
            digitalWrite(MotorController::dri_io.dir, HIGH);
        }
    }

    void MotorController::change_en_state()
    {
        if (digitalRead(MotorController::dri_io.enable))
        {
            digitalWrite(MotorController::dri_io.enable, LOW);
        }
        else
        {
            digitalWrite(MotorController::dri_io.enable, HIGH);
        }
    }
// } //HardwareLeo