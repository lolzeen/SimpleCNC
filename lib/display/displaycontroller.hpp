#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

struct DisplayPins
{
    uint8_t rs;
    uint8_t enable;
    uint8_t d4;
    uint8_t d5;
    uint8_t d6;
    uint8_t d7;
};

class DisplayController : public LiquidCrystal
{
    private:
        
        
    public:
        const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
        // DisplayController(LiquidCrystal& liquidcrystal);
        DisplayController();
        // TODO unpack display_pins on lcd conctructor
        // DisplayController(DisplayPins display_pins);
        ~DisplayController();

        void show_main_menu();
        void show_speed_menu();
        void show_distance_menu();
        void show_time_menu();
        

};


#endif //DISPLAYCONTROLLER_H