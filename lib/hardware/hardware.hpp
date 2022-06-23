#ifndef HARDWARE_W
#define HARDWARE_W

#include <Arduino.h>

namespace HardwareLeo
{
    struct IoPins 
    {
        IoPins()
        {
            // default I/Os
            const int ENX = 11, DIRX = 12, STEPX = 13, ENZ = 8, DIRZ = 9, STEPZ = 10, ESX1 = 18, ESX2 = 19, ESZ1 = 20, ESZ2 = 21;
        }
        // IMPROVEMENT: alternative constructor
    }io_pins;

    class Controller
    {
        private:
            struct EsPin
            // End Siwtch Pins
            {
                EsPin();
                int pin_1 = 0;
                int pin_2 = 0;
            }es_inp;
            
            struct DriPin
            // Driver Pins
            {
                int dir = 0;
                int enable = 0;
                int step = 0;
                int output = 0;
            }dri_io;

        // sensor reading
            // TODO: interrupts

        //responses to readings (ISRs)
            void es_1();
            void es_2();

        public:
            Controller();
            ~Controller();

            void setEsPins(int pin_1, int pin_2);
            void setDriPins(int pin_dir, int pin_enable, int pin_step, int pin_output);

    };
} // HardwareLeo
#endif //HARDWARE_W