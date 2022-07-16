#ifndef HARDWARE_W
#define HARDWARE_W

#include <Arduino.h>
#include "Movements.hpp"

const uint8_t HOME = 0;
const uint8_t FINISH = 1;
const uint8_t FORWARD = 0; // TODO: confirm this with driver 
const uint8_t BACKWARD = 1; // TODO: confirm this with driver 
const uint8_t MAX_DISTANCE = 34; // cm // TODO: confirm this with CAD model
const double MIN_TIME = 0.5; // minutes // TODO: confirm this with CAD model

struct DriverPins
{
    uint8_t _ES1;
    uint8_t _ES2;
    uint8_t _DIR;
    uint8_t _EN;
    uint8_t _STEP;
    uint8_t _OUT;
};
struct DriverParameters
{
    uint16_t _pulses_per_rev;
};
struct ProcessParameters
{
    uint8_t _last_pos;
    uint8_t _dir_state;
    uint8_t _en_state;
    float _frequency;
    uint64_t _num_pulses;
    float _distance; // cm
    float _time; // min
    float _speed; // cm/min
    

    // IMPROVEMENT uint8_t _dist_unit = 1; // cm
    // IMPROVEMENT uint8_t _time_unit = 1; // min
};

class MotorController
{
    private:
        // IMPROVEMENT const char dist_unit[5] = { 'm', 'cm', 'mm', 'in', 'feet'};
        // IMPROVEMENT const char time_unit[4] = {'m', 's', 'ms', 'us'};

        DriverPins _driver_pins;
        DriverParameters _driver_params;
        ProcessParameters _process_params;

        // IMPROVEMENT void set_dist_unit(char* dist_unit);
        // IMPROVEMENT void set_time_unit(char* time_unit);
        float calc_freq();
        uint64_t calc_num_pulses();
        void io_setup(const DriverPins &pins);
        void process_setup();
        

    public:
        MotorController();
        MotorController(const DriverPins &pins);
        MotorController(const DriverPins &pins,  const DriverParameters &params_driver);
        ~MotorController();

        bool move = false;

        void set_last_pos(const uint8_t pos);
        void set_dir_state(const uint8_t state);
        void set_en_state(const uint8_t  state);
        void set_freq(const uint8_t freq);
        void set_num_pulses(const uint64_t num);
        void set_distance(const uint8_t dist);
        void set_time(const uint8_t time);
        void set_speed(const uint8_t speed);

        const ProcessParameters get_process_params();

        void change_en_state();
        void change_en_state(uint8_t state);
        void change_dir_state();
        void change_dir_state(uint8_t state);
        void return_home();
        void set_pos(uint8_t pos); // TODO: find better name for this function

        // IMPROVEMENT void set_units(char* dist_unit, char* time_unit);
    
};
#endif // HARDWARE_W