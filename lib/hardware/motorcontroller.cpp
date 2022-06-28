#include "motorcontroller.hpp"


MotorController::MotorController()
{
    // Intentionally Empty;
}

MotorController::MotorController(const DriverPins &pins)
{
    MotorController::io_setup(pins);
    MotorController::driver_params =  {27500};
}

MotorController::MotorController(const DriverPins &pins, const DriverParameters &params_driver)
{
    MotorController::io_setup(pins);
    MotorController::driver_params = params_driver;
}

void MotorController::io_setup(const DriverPins &pins)
{
    MotorController::driver_pins = pins;
    pinMode(MotorController::driver_pins._ES1, INPUT_PULLUP);
    pinMode(MotorController::driver_pins._ES2, INPUT_PULLUP);
    Serial.println("End Switches Pins are set!");
    pinMode(MotorController::driver_pins._DIR, OUTPUT);
    pinMode(MotorController::driver_pins._EN, OUTPUT);
    pinMode(MotorController::driver_pins._STEP, OUTPUT);
    pinMode(MotorController::driver_pins._OUT, INPUT);
    Serial.println("Driver Pins are set!");
}

MotorController::~MotorController()
{
    // Intentionally Empty;
}

void MotorController::change_dir_state()
{
    if (digitalRead(MotorController::driver_pins._DIR))
    {
        digitalWrite(MotorController::driver_pins._DIR, LOW);
    }
    else
    {
        digitalWrite(MotorController::driver_pins._DIR, HIGH);
    }
}

void MotorController::change_en_state()
{
    if (digitalRead(MotorController::driver_pins._EN))
    {
        digitalWrite(MotorController::driver_pins._EN, LOW);
    }
    else
    {
        digitalWrite(MotorController::driver_pins._EN, HIGH);
    }
}

void MotorController::calc_num_pulses()
{
    
    MotorController::process_params._num_pulses = MotorController::driver_params._pulses_per_rev * MotorController::process_params._distance;
}

void MotorController::calc_freq()
{
    MotorController::process_params._frequency = MotorController::process_params._distance / (MotorController::process_params._time * 60);
}

// FIXME: calculate frequency based on the selected speed (user input)
// void MotorController::calc_freq()
// {
//     MotorController::process_params._frequency = MotorController::process_params._speed / 60;
// }

/* IMPROVEMENT
void MotorController::set_units(char* dist_unit, char* time_unit)
{
    MotorController::set_dist_unit(dist_unit);
    MotorController::set_time_unit(time_unit);
}

void MotorController::set_time_unit(char* time_unit)
{
    switch (*time_unit)
    {
    case MotorController::dist_unit[0]:
        Serial.println("Time unit is defined to SECONDS.");
        break;
    case 2:
        Serial.println("Time unit is defined to MINUTES.");
        MotorController::process_params._time_unit *=60;
        break;
    case 3:
        Serial.println("Time unit is defined to MILISECONDS.");
        MotorController::process_params._time_unit *=1e-3;
        break;
    case 4:
        Serial.println("Time unit is defined to MICROSECONDS.");
        MotorController::process_params._time_unit *=1e-6;
        break;
    
    default:
        break;
    }
}

void MotorController::set_dist_unit(char* dist_unit)
{
    switch (MotorController::process_params._dist_unit)
    {
    case 1:
        Serial.println("Distance unit is set to METERS.");
        break;
    case 2:
        Serial.println("Distance unit is set to CENTIMETERS.");
        MotorController::process_params._dist_unit *=1e-2;
        break;
    case 3:
        Serial.println("Distance unit is set to MILIMETERS.");
        MotorController::process_params._dist_unit *=1e-3;
        break;
    case 4:
        Serial.println("Distance unit is set to INCHES.");
        MotorController::process_params._dist_unit *= 39.37008;
        break;
    case 5:
        Serial.println("Distance unit is set to FEET.");
        MotorController::process_params._dist_unit *= 3.28084;
        break;
    default:
        break;
    }
}
*/

