#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>

struct DisplayPins
{
    DisplayPins()
    {
        // intentionally empty
    }
    DisplayPins(const uint8_t& rs, const uint8_t& en, const uint8_t& d4, const uint8_t& d5, const uint8_t& d6, const uint8_t& d7)
    {
        RS = rs;
        EN = en;
        D4 = d4;
        D5 = d5;
        D6 = d6;
        D7 = d7;
    }
    DisplayPins(const DisplayPins& disp_pins)
    {
        RS = disp_pins.RS;
        EN = disp_pins.EN;
        D4 = disp_pins.D4;
        D5 = disp_pins.D5;
        D6 = disp_pins.D6;
        D7 = disp_pins.D7;
    }
    uint8_t RS;
    uint8_t EN;
    uint8_t D4;
    uint8_t D5;
    uint8_t D6;
    uint8_t D7;
};

class DisplayController 
{
    private:
        const uint8_t display_rs = 13;
        const uint8_t display_en = 12;
        const uint8_t display_d4 = 11;
        const uint8_t display_d5 = 10;
        const uint8_t display_d6 = 9;
        const uint8_t display_d7 = 8; 
        LiquidCrystal _lcd = LiquidCrystal(display_rs, display_en, display_d4, display_d5, display_d6, display_d7);

        static const uint8_t _num_windows = 4;
        int _current_window = 0;
        void set_current_window(uint8_t new_window);

        String _content_menus[_num_windows][2] = {{"Iniciar Processo", ""}, {"Retornar", ""}, {"Vel. Avanco", "cm/min"}, {"Vel. Mergulho", "cm/min"}};
        long _feed_speed; // TODO fix name
        long _dive_speed;
        // uint16_t dive_speed;
        void display_menu();
        
    public:
        DisplayController();
        ~DisplayController();
        int get_current_window();
        // uint8_t get_dive_speed();
        const long get_feed_speed(); // TODO fix name
        const long get_dive_speed();

        void set_feed_speed(long var);
        void set_dive_speed(long var);
        void set_menu_content(const long& content);
        void next_window();
        void initialize_display();
};

#endif // DISPLAYCONTROLLER_H