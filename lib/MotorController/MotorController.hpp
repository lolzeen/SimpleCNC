#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>

// #include "Calculator.hpp"
#include "Button.hpp"
const uint8_t HOME = 0;
const uint8_t FINISH = 1;
const uint8_t FORWARD = 1;
const uint8_t BACKWARD = 0;
const uint8_t MIN_TIME = 30; // seconds // TODO: confirm this with CAD model

struct DriverPins
{
    uint8_t _ES1;
    uint8_t _ES2;
    uint8_t _DIR;
    uint8_t _EN;
    uint8_t _STEP;
    uint8_t _OUT;
};
// struct DriverParameters
// {
//     uint16_t _pulses_per_rev;
// };
// struct ProcessParameters
// {
//     uint8_t _last_pos;
//     uint8_t _dir_state;
//     uint8_t _en_state;
//     long _frequency;
//     uint64_t _num_pulses;
//     float _distance; // cm
//     float _time; // min
//     float _speed; // cm/min
//     // IMPROVEMENT uint8_t _dist_unit = 1; // cm
//     // IMPROVEMENT uint8_t _time_unit = 1; // min
// };

class MotorController
{
    private:
        // IMPROVEMENT const char dist_unit[5] = { 'm', 'cm', 'mm', 'in', 'feet'};
        // IMPROVEMENT const char time_unit[4] = {'m', 's', 'ms', 'us'};
        uint8_t _last_pos;
        uint8_t _dir_state;
        uint8_t _en_state;
        long _frequency; // Hz
        uint64_t _num_pulses;
        uint8_t _max_distance; // cm
        uint8_t _distance; // cm
        float _time; // min
        uint8_t _speed; // cm/min
        uint16_t _ocr; 
        uint16_t _pulses_per_rev;
        uint8_t _id; // timer identifier
        uint16_t _arc_voltage;
        uint16_t _last_arc_voltage;
        uint8_t _arc_controller_gain = 0;
        uint8_t _welding_voltage = 0;
        uint8_t _short_circuit_voltage = 0;
        uint8_t _voltage_tolerance = 0;

        DriverPins _driver_pins;
        Button _end_switch1, _end_switch2;

        void io_setup(const DriverPins &pins);
        void set_process();
        void set_process(uint8_t mode);
        void set_timers();
        void stop_timers();
        void calc_freq();
        void calc_freq(const int pot_val);
        void calc_ocr();
        void cartrige_return();
        void end_switch(bool activate_cartrige_return);
        void verify_distance();
        

    public:
        MotorController();
        MotorController(const DriverPins &pins);
        MotorController(const DriverPins &pins, const uint16_t &driver_pul_rev, const uint8_t &id, uint8_t dis);
        ~MotorController();

        bool move = false;

        void set_dir_state(const uint8_t state);
        void set_en_state(const uint8_t  state);
        void set_distance(const uint8_t dist);
        void set_max_distance(const uint8_t dist);
        void set_time(const uint8_t time);
        void set_speed(const uint8_t speed);
        void set_ocr(const uint16_t ocr_top);
        void set_freq(const long freq); // TODO: review usability
        void set_num_pulses(const uint64_t num); // TODO: review usability
        void set_last_pos(const uint8_t pos);  // TODO: review usability
        void set_pos(uint8_t pos); // TODO: find better name for this function  // TODO: review usability
        void set_arc_controller_gain(uint8_t gain);
        void set_welding_voltage(uint8_t voltage);
        void set_arc_short_circuit_voltage(uint8_t voltage);
        void set_voltage_tolerance(uint8_t voltage);

        const uint8_t get_dir_state();
        const uint8_t get_en_state();
        const long get_freq();
        const uint8_t get_distance();
        const uint8_t get_max_distance();
        const uint8_t get_time();
        const uint8_t get_speed();
        const uint16_t get_ocr();
        const uint8_t get_pos();
        const uint8_t get_arc_controller_gain();
        const uint8_t get_welding_voltage();
        const uint8_t get_arc_short_circuit_voltage();
        const uint8_t get_voltage_tolerance();

        void return_home();
        void start_process();
        void start_process(uint8_t mode);
        bool end_switch();
        void set_timer_speed();
        void read_voltage();
        void correct_height();
        void run();
        void run(bool activate_correct_height);
        // void change_speed_while_running();
        
        // IMPROVEMENT void set_units(char* dist_unit, char* time_unit);
    
};
#endif // MOTORCONTROLLER_H