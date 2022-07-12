#include "motorcontroller.hpp"


MotorController::MotorController()
{
    // Intentionally Empty;
}
MotorController::MotorController(const DriverPins &pins)
{
    io_setup(pins);
    _driver_params =  {27500};
    process_setup();
}
MotorController::MotorController(const DriverPins &pins, const DriverParameters &params_driver)
{
    io_setup(pins);
    _driver_params = params_driver;
    process_setup();
}
MotorController::~MotorController()
{
    // Intentionally Empty;
}
void MotorController::io_setup(const DriverPins &pins)
{
    _driver_pins = pins;
    pinMode(_driver_pins._ES1, INPUT_PULLUP);
    pinMode(_driver_pins._ES2, INPUT_PULLUP);
    Serial.println("End Switches Pins are set!");
    pinMode(_driver_pins._DIR, OUTPUT);
    pinMode(_driver_pins._EN, OUTPUT);
    pinMode(_driver_pins._STEP, OUTPUT);
    pinMode(_driver_pins._OUT, INPUT);
    Serial.println("Driver Pins are set!");
}
void MotorController::process_setup()
{
    set_last_pos(HOME);
    set_dir_state(FORWARD);
    set_en_state(LOW);
    set_distance(MAX_DISTANCE);
    set_time(MIN_TIME);
    set_speed(MAX_DISTANCE/MIN_TIME);
    set_freq(calc_freq());
    set_num_pulses(calc_num_pulses());
    // TODO: call return home
}
void MotorController::return_home()
{
    TODO:
}
void MotorController::change_dir_state()
{
    // TODO: substitute this digital read for a software verification
    if (digitalRead(_driver_pins._DIR))
    {
        digitalWrite(_driver_pins._DIR, LOW);
    }
    else
    {
        digitalWrite(_driver_pins._DIR, HIGH);
    }
}
void MotorController::change_en_state()
{
    // TODO: substitute this digital read for a software verification
    if (digitalRead(_driver_pins._EN))
    {
        digitalWrite(_driver_pins._EN, LOW);
    }
    else
    {
        digitalWrite(_driver_pins._EN, HIGH);
    }
}
uint64_t MotorController::calc_num_pulses()
{
    _process_params._num_pulses = _driver_params._pulses_per_rev * _process_params._distance;
}
float MotorController::calc_freq()
{
    // TODO:  calc based on speed
    _process_params._frequency = _process_params._distance / (_process_params._time * 60);
}
void MotorController::set_last_pos(const uint8_t pos)
{
    _process_params._last_pos = pos;
}
void MotorController::set_dir_state(const uint8_t state)
{
    _process_params._dir_state = state;
}
void MotorController::set_en_state(const uint8_t  state)
{
    _process_params._en_state = state;
}
void MotorController::set_freq(const uint8_t freq)
{
    _process_params._frequency = freq;
}
void MotorController::set_num_pulses(const uint64_t num)
{
    _process_params._num_pulses = num;
}
void MotorController::set_distance(const uint8_t dist)
{
    _process_params._distance = dist;
}
void MotorController::set_time(const uint8_t time)
{
    _process_params._time = time;
}
void MotorController::set_speed(const uint8_t speed)
{
    _process_params._speed = speed;
}
const ProcessParameters MotorController::get_process_params()
{
    return _process_params;
}

/* IMPROVEMENT
void set_units(char* dist_unit, char* time_unit)
{
    set_dist_unit(dist_unit);
    set_time_unit(time_unit);
}

void set_time_unit(char* time_unit)
{
    switch (*time_unit)
    {
    case dist_unit[0]:
        Serial.println("Time unit is defined to SECONDS.");
        break;
    case 2:
        Serial.println("Time unit is defined to MINUTES.");
        process_params._time_unit *=60;
        break;
    case 3:
        Serial.println("Time unit is defined to MILISECONDS.");
        process_params._time_unit *=1e-3;
        break;
    case 4:
        Serial.println("Time unit is defined to MICROSECONDS.");
        process_params._time_unit *=1e-6;
        break;
    
    default:
        break;
    }
}

void set_dist_unit(char* dist_unit)
{
    switch (process_params._dist_unit)
    {
    case 1:
        Serial.println("Distance unit is set to METERS.");
        break;
    case 2:
        Serial.println("Distance unit is set to CENTIMETERS.");
        process_params._dist_unit *=1e-2;
        break;
    case 3:
        Serial.println("Distance unit is set to MILIMETERS.");
        process_params._dist_unit *=1e-3;
        break;
    case 4:
        Serial.println("Distance unit is set to INCHES.");
        process_params._dist_unit *= 39.37008;
        break;
    case 5:
        Serial.println("Distance unit is set to FEET.");
        process_params._dist_unit *= 3.28084;
        break;
    default:
        break;
    }
}
*/

