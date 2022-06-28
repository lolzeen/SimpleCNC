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


class DisplayController
{
    private:
        DisplayPins display_pins;
        // TODO unpack display_pins on lcd conctructor
        LiquidCrystal lcd(display_pins.rs, display_pins.enable, display_pins.d4, display_pins.d5,display_pins.d6, display_pins.d7);
    public:
        DisplayController();
        DisplayController(const DisplayPins& pins);
        ~DisplayController();

        void show_main_menu();
        void show_speed_menu();
        void show_distance_menu();
        void show_time_menu();
        

};


#endif //DISPLAYCONTROLLER_H