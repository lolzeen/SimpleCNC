#include "MotorController.hpp"


MotorController::MotorController()
{
    // Intentionally Empty;
}
MotorController::MotorController(const DriverPins &pins)
{
    io_setup(pins);
    _pulses_per_rev =  20000;
    set_en_state(LOW);
}
// MotorController::MotorController(const DriverPins &pins, const DriverParameters &params_driver)
// {
//     io_setup(pins);
//     _pulses_per_rev = params_driver._pulses_per_rev;
//     set_en_state(LOW);
// }
MotorController::MotorController(const DriverPins &pins, const uint16_t &driver_pul_rev)
{
    io_setup(pins);
    _pulses_per_rev = driver_pul_rev;
}
MotorController::~MotorController()
{
    // Intentionally Empty;
    // IMPROVEMENT: write settings on memory before turning off
}
void MotorController::io_setup(const DriverPins &pins)
{
    _driver_pins = pins;
    pinMode(_driver_pins._ES1, INPUT_PULLUP);
    pinMode(_driver_pins._ES2, INPUT_PULLUP);
    Serial.println("End Switches Pins are set!");
    pinMode(_driver_pins._DIR, OUTPUT);
    pinMode(_driver_pins._EN, OUTPUT);
    set_en_state(LOW);
    pinMode(_driver_pins._STEP, OUTPUT);
    digitalWrite(_driver_pins._STEP, LOW);
    pinMode(_driver_pins._OUT, INPUT);
    Serial.println("Driver Pins are set!");
}
void MotorController::set_process()
{
    calc_freq();
    // set_ocr(calc_ocr());
    // Serial.print("OCR: ");
    // Serial.println(_ocr);
    // set_timers();
}
// void MotorController::set_process(uint8_t mode) // TODO
// {
//     switch (mode)
//     {
//     case 1:
//         calc_freq();
//         uint64_t ini = micros();
//         break;
//     default:
//         break;
//     }
// }

// void MotorController::set_timers()
// {
//     cli();
//     switch (_driver_pins._STEP)
//     {
//     case 6:
//         // timer 4
//         // pinMode(11, OUTPUT);
//         TCCR4A = _BV(COM4A0) | _BV(COM4B0) | _BV(COM4C0) | _BV(WGM40); // 01010101
//         TCCR4B = _BV(WGM43)| _BV(CS42) | _BV(CS40); //00010001
//         OCR4A = _ocr;
//         // TIMSK4 |= (1 << OCIE4A);
//         break;
//     case 5:    
//         // timer 3
//         // pinMode(5, OUTPUT);
//         TCCR3A =  _BV(COM3A0) | _BV(COM3B0) | _BV(COM3C0) | _BV(WGM30); // 01010101
//         TCCR3B = _BV(WGM33) | _BV(CS32) | _BV(CS30); //00010001
//         OCR3A = _ocr;
//         // TIMSK3 |= (1 << OCIE3A);
//         break;
//     default:
//         break;
//     }
//     sei();
// }

// void MotorController::stop_timers(uint8_t id)
// {
//     switch (id)
//     {
//     case 4:
//         TCCR4A = _BV(COM4A0) | _BV(WGM40); // 01010101
//         TCCR4B = _BV(WGM43); //00010000
//         break;
//     case 3:
//         TCCR3A = _BV(COM3A0) | _BV(WGM30); // 01010101
//         TCCR3B = _BV(WGM33); //00010000
//         break;
//     default:
//         break;
//     }
// }
void MotorController::start_process()
{
    if (!_en_state)
    {
        set_process();
        set_dir_state(FORWARD);
        set_en_state(HIGH);
    }
//     Serial.print("Freq: ");
//     Serial.println(_frequency);
//     tone(_driver_pins._STEP, _frequency);
}
void MotorController::return_home()
{
    if (!_en_state)
    {
        set_dir_state(BACKWARD);
        set_distance(MAX_DISTANCE);
        set_time(MIN_TIME*8);
        set_speed(MAX_DISTANCE/MIN_TIME);
        set_process();
        set_en_state(HIGH);
    }
    // tone(_driver_pins._STEP, 15000);  
}

void MotorController::set_last_pos(const uint8_t pos)
{
    _last_pos = pos;
}
void MotorController::set_dir_state(const uint8_t state)
{
    _dir_state = state;
    digitalWrite(_driver_pins._DIR, _dir_state);
}
void MotorController::set_en_state(const uint8_t  state)
{
    _en_state = state;
    digitalWrite(_driver_pins._EN, _en_state);
}
void MotorController::set_freq(const long freq)
{
    _frequency = freq;
    // Serial.print("set Freq: ");
    // Serial.println(freq);
}
void MotorController::set_num_pulses(const uint64_t num)
{
    _num_pulses = num;
}
void MotorController::set_distance(const uint8_t dist)
{
    _distance = dist;
}
void MotorController::set_time(const uint8_t time)
{
    _time = time;
}
void MotorController::set_speed(const uint8_t speed)
{
    _speed = speed;
}
void MotorController::set_pos(uint8_t pos)
{
    // change_en_state(LOW);
    set_last_pos(pos);
}
void MotorController::set_ocr(const uint16_t ocr_top)
{
    _ocr = ocr_top;
}

const uint8_t MotorController::get_dir_state()
{
    return _dir_state;
}
const uint8_t MotorController::get_en_state()
{
    return _en_state;
}
const long MotorController::get_freq()
{
    return _frequency;
}
const uint8_t MotorController::get_distance()
{
    return _distance;
}
const uint8_t MotorController::get_time()
{
    return _time;
}
const uint8_t MotorController::get_speed()
{
    return _speed;
}
const uint16_t MotorController::get_ocr()
{
    return _ocr;
}
const uint8_t MotorController::get_pos()
{
    return _last_pos;
}

void MotorController::calc_freq()
{
    _frequency = _speed*(_pulses_per_rev/0.008)/(60*100);
    Serial.print("Freq: ");
    Serial.println(_frequency);
}
// void MotorController::calc_freq(const int val)
// {
//     _frequency = val*_pulses_per_rev/48;
// }
uint16_t MotorController::calc_ocr()
{
    return 16e6 / (2 * _frequency * 1024);
}
// uint8_t MotorController::conv_pot_speed(const int pot_reading)
// {
//   uint8_t _in_min = 0;
//   uint16_t _in_max = 1023;
//   uint8_t _out_min = 90;
//   uint8_t _out_max = 6;
//   return map(pot_reading, _in_min, _in_max, _out_min, _out_max);
// }
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