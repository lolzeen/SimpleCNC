#ifndef HARDWARE_W
#define HARDWARE_W

#include <Arduino.h>

// namespace HardwareLeo
// {
struct DriverPins
{
    int _ES1;
    int _ES2;
    int _DIR;
    int _EN;
    int _STEP;
    int _OUT;
};
class MotorController
{
    private:
        DriverPins _pins;

    // sensor reading
        // TODO: interrupts
        void es_interrupts();

    //responses to readings (ISRs)
        

    public:
        MotorController();
        MotorController(const DriverPins &pins);
        ~MotorController();

        void change_en_state();
        void change_dir_state();
};
#endif // HARDWARE_W