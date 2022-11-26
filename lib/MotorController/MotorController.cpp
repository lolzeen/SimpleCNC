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
MotorController::MotorController(const DriverPins &pins, const uint16_t &driver_pul_rev, const uint8_t &id, uint8_t dis)
{
    io_setup(pins);
    _pulses_per_rev = driver_pul_rev;
    _max_distance = dis;
    _id = id;
}
MotorController::~MotorController()
{
    // Intentionally Empty;
    // IMPROVEMENT: write settings on memory before turning off
}
void MotorController::io_setup(const DriverPins &pins)
{
    _driver_pins = pins;
    _end_switch1.begin(_driver_pins._ES1, true);
    _end_switch2.begin(_driver_pins._ES2, true);
    pinMode(_driver_pins._DIR, OUTPUT);
    pinMode(_driver_pins._EN, OUTPUT);
    set_en_state(LOW);
    pinMode(_driver_pins._STEP, OUTPUT);
    digitalWrite(_driver_pins._STEP, LOW);
    pinMode(_driver_pins._OUT, INPUT);

}

void MotorController::set_process()
{
    set_distance(0);
    calc_freq();
    calc_ocr();
    set_timers();
}
void MotorController::set_timers()
{
    noInterrupts();
    switch (_id)
    {
    case 4:
        TCCR4A = _BV(COM4A0) | _BV(COM4B0) | _BV(COM4C0) | _BV(WGM40); // 01010101
        TCCR4B = _BV(WGM43) | _BV(CS40); //00010001
        OCR4A = _ocr;
        break;

    case 3:    
        TCCR3A =  _BV(COM3A0) | _BV(COM3B0) | _BV(COM3C0) | _BV(WGM30); // 01010101
        TCCR3B = _BV(WGM33) | _BV(CS30); //00010001
        OCR3A = _ocr;
        break;
    default:
        break;
    }
    interrupts();
}
void MotorController::stop_timers()
{
    noInterrupts();
    // TCCRA = _BV(COMA) | _BV(COMB) | _BV(COMC) | _BV(WGM0); // 01010101
    // TCCRB = _BV(WGM3) | _BV(CS0);
    // OCR = _ocr;
    switch (_id)
    {
    case 4:
        TCCR4A = _BV(COM4A0) | _BV(COM4B0) | _BV(COM4C0) | _BV(WGM40); // 01010101
        TCCR4B = _BV(WGM43); //00010000
        break;
    
    case 3:
        TCCR3A =  _BV(COM3A0) | _BV(COM3B0) | _BV(COM3C0) | _BV(WGM30); // 01010101
        TCCR3B = _BV(WGM33); //00010000
        break;

    default:
        break;
    }
    interrupts();
}
void MotorController::start_process()
{
    if (!_en_state)
    {
        set_max_distance(_max_distance);
        set_process();
        set_dir_state(FORWARD);
        set_en_state(HIGH);
    }
}
void MotorController::start_process(uint8_t mode)
{
    start_process();
}
void MotorController::return_home()
{
    if (!_en_state)
    {
        
        set_max_distance(_max_distance);
        set_dir_state(BACKWARD);
        set_time(MIN_TIME*2); // previous setting MIN_TIME*8
        set_speed(100*_max_distance/MIN_TIME);
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
void MotorController::set_max_distance(const uint8_t max_dist)
{
    _max_distance = max_dist;
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
void MotorController::set_timer_speed()
{
    calc_freq();
    calc_ocr();
    // OCR = _ocr;
    switch (_id)
    {
    case 4:
        OCR4A = _ocr;
        break;
    case 3:
        OCR3A = _ocr;
        break;
    default:
        break;
    }
}
void MotorController::set_arc_controller_gain(uint8_t gain)
{
    _arc_controller_gain = gain;
}
void MotorController::set_welding_voltage(uint8_t voltage)
{
    _welding_voltage = voltage;
}
void MotorController::set_arc_short_circuit_voltage(uint8_t voltage)
{
    _short_circuit_voltage = voltage;
}
void MotorController::set_voltage_tolerance(uint8_t voltage)
{
    _voltage_tolerance = voltage;
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
const uint8_t MotorController::get_max_distance()
{
    return _max_distance;
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
const uint8_t MotorController::get_arc_short_circuit_voltage()
{
    return _short_circuit_voltage;
}
const uint8_t MotorController::get_arc_controller_gain()
{
    return _arc_controller_gain;
}
const uint8_t MotorController::get_welding_voltage()
{
    return _welding_voltage;
}
const uint8_t MotorController::get_voltage_tolerance()
{
    return _voltage_tolerance;
}

void MotorController::cartrige_return()
{
    // FIXME
    Serial.println("Cartrige Return");
    if (_dir_state == FORWARD)
    {
        set_dir_state(BACKWARD);
    }
    else if (_dir_state == BACKWARD)
    {
        set_dir_state(FORWARD);
    }
    set_speed(100*_max_distance/MIN_TIME);
    set_timer_speed();
    set_en_state(HIGH);
    delay(200);
    set_en_state(LOW);
}
void MotorController::calc_freq()
{
    // FIXME
    _frequency = 2*_speed*(_pulses_per_rev/0.008)/(60*100);
    // Serial.print("Freq: ");
    // Serial.println(_frequency);
}
void MotorController::calc_ocr()
{
    uint16_t ocr = 8e6 / _frequency;
    if (ocr <= 65535 && ocr > 0) 
        _ocr =  ocr;
}
void MotorController::correct_height()
{
    read_voltage();
    int delta = _arc_voltage - _last_arc_voltage;
    if (abs(delta) > 0)
    {
        set_speed(abs(delta) * _speed * _arc_controller_gain);
        set_timer_speed();
        if (delta < 0)
        {
            set_dir_state(BACKWARD);
        }
        else
        {
            set_dir_state(FORWARD);
        }
    }
    _last_arc_voltage = _arc_voltage;
}
void MotorController::end_switch(bool activate_cartrige_return)
{
    if (activate_cartrige_return)
    {
        if(_end_switch1.debounce())
        {
            // home
            if (_dir_state == BACKWARD)
            {
                set_en_state(LOW);
                cartrige_return();
                set_pos(HOME);
            }
            // Serial.print("Id: ");
            // Serial.print(_id);
            // Serial.println(" endswitch: HOME");
        }
        else if(_end_switch2.debounce())
        {
            // finish
            if (_dir_state == FORWARD)
            {
                set_en_state(LOW);
                cartrige_return();
                set_pos(FINISH);
            }
            // Serial.print("Id: ");
            // Serial.print(_id);
            // Serial.println(" endswitch: FINISH");
        }
    }
}
bool MotorController::end_switch()
{
    if(_end_switch1.debounce())
    {
        // home
        if (_dir_state == BACKWARD)
        {
            set_en_state(LOW);
            set_pos(HOME);
            return true;
        }
    }
    else if(_end_switch2.debounce())
    {
        // finish
        if (_dir_state == FORWARD)
        {
            set_en_state(LOW);
            set_pos(FINISH);
            return true;
        }
    }
    return false;
}
void MotorController::read_voltage()
{
    _arc_voltage = analogRead(A0);
}
void MotorController::run()
{
    end_switch();
    verify_distance();
}
void MotorController::run(bool activate_correct_height)
{
    end_switch();
    verify_distance();
    if (activate_correct_height)
    {
        correct_height();
    }
}
void MotorController::verify_distance()
{
    // how
    // count pulses / get tach signal from driver
}
// void MotorController::change_speed_while_running()
// {
//     delay(200);
//     for (int i = 0; i < 20; i ++)
//     {
//         if(i%2 == 0)
//         {
//             set_dir_state(!_dir_state);
//         }
//         set_speed(10*i);
//         calc_freq();
//         calc_ocr();
//         delay(250);
//     }
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