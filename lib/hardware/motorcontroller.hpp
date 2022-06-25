#ifndef HARDWARE_W
#define HARDWARE_W

#include <Arduino.h>

// namespace HardwareLeo
// {
    class MotorController
    {
        private:
            struct EsPin
            // End Siwtch Pins
            {
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
            void es_interrupts();

        //responses to readings (ISRs)
            

        public:
            MotorController();
            ~MotorController();

            void setEsPins(int pin_1, int pin_2);
            void setDriPins(int pin_dir, int pin_enable, int pin_step, int pin_output);

            static void es_1();
            static void es_2();

            void change_en_state();
            void change_dir_state();

    };
// } // HardwareLeo
#endif //HARDWARE_W