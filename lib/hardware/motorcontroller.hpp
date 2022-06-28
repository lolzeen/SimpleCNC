#ifndef HARDWARE_W
#define HARDWARE_W

const int CLOSE = 0;
const int FAR = 1;

#include <Arduino.h>

// namespace HardwareLeo
// {
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

        DriverPins driver_pins;
        DriverParameters driver_params;
        ProcessParameters process_params;

        // IMPROVEMENT void set_dist_unit(char* dist_unit);
        // IMPROVEMENT void set_time_unit(char* time_unit);
        void calc_freq();
        void calc_num_pulses();
        void io_setup(const DriverPins &pins);
        

    public:
        MotorController();
        MotorController(const DriverPins &pins);
        MotorController(const DriverPins &pins,  const DriverParameters &params_driver);
        ~MotorController();

        void change_en_state();
        void change_dir_state();

        // IMPROVEMENT void set_units(char* dist_unit, char* time_unit);



        
};
#endif // HARDWARE_W