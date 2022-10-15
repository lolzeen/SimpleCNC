#ifndef HARDWARE_W
#define HARDWARE_W

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
        float _speed; // cm/min
        uint16_t _ocr; 
        uint16_t _pulses_per_rev;
        uint8_t _id; // timer identifier

        DriverPins _driver_pins;
        Button _end_switch1, _end_switch2;
       
        // uint64_t calc_num_pulses();
        void io_setup(const DriverPins &pins);
        void set_process();
        void set_process(uint8_t mode);
        void set_timers();
        void calc_freq();
        void calc_freq(const int pot_val);
        void calc_ocr();
        // uint8_t conv_pot_speed(const int pot_reading);

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

        const uint8_t get_dir_state();
        const uint8_t get_en_state();
        const long get_freq();
        const uint8_t get_distance();
        const uint8_t get_max_distance();
        const uint8_t get_time();
        const uint8_t get_speed();
        const uint16_t get_ocr();
        const uint8_t get_pos();
        void return_home();
        void start_process();
        void start_process(uint8_t mode);
        void stop_timers();

        void cartrige_return();
        void end_switch();
        void verify_distance();
        void run();
        
        // IMPROVEMENT void set_units(char* dist_unit, char* time_unit);
    
};
#endif // HARDWARE_W