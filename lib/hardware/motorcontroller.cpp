#include "motorcontroller.hpp"

// namespace HardwareLeo
// {
    // Controller::Controller(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d) : es_pin_x_r(pin_x_r), es_pin_x_l(pin_x_l), es_pin_z_u(pin_z_u), es_pin_z_d(pin_z_d);

    MotorController::MotorController()
    {
        // Intentionally Empty;
    }

    MotorController::MotorController(const DriverPins &pins)
    {
        MotorController::_pins = pins;
        pinMode(MotorController::_pins._ES1, INPUT_PULLUP);
        pinMode(MotorController::_pins._ES2, INPUT_PULLUP);
        Serial.println("End Switches Pins are set!");
        pinMode(MotorController::_pins._DIR, OUTPUT);
        pinMode(MotorController::_pins._EN, OUTPUT);
        pinMode(MotorController::_pins._STEP, OUTPUT);
        pinMode(MotorController::_pins._OUT, INPUT);
        Serial.println("Driver Pins are set!");

    }

    MotorController::~MotorController()
    {
        // Intentionally Empty;
    }

    void MotorController::change_dir_state()
    {
        if (digitalRead(MotorController::_pins._DIR))
        {
            digitalWrite(MotorController::_pins._DIR, LOW);
        }
        else
        {
            digitalWrite(MotorController::_pins._DIR, HIGH);
        }
    }

    void MotorController::change_en_state()
    {
        if (digitalRead(MotorController::_pins._EN))
        {
            digitalWrite(MotorController::_pins._EN, LOW);
        }
        else
        {
            digitalWrite(MotorController::_pins._EN, HIGH);
        }
    }
// } //HardwareLeo