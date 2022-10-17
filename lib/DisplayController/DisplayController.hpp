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
        // delay before process start in seconds
        #ifndef PROCESS_START_DELAY
            #define PROCESS_START_DELAY 5
        #endif
        #ifndef DISPLAY_RS
            #define DISPLAY_RS 13
        #endif
        #ifndef DISPLAY_EN
            #define DISPLAY_EN 12
        #endif
        #ifndef DISPLAY_D4
            #define DISPLAY_D4 11
        #endif
        #ifndef DISPLAY_D5
            #define DISPLAY_D5 10
        #endif
        #ifndef DISPLAY_D6
            #define DISPLAY_D6 9
        #endif
        #ifndef DISPLAY_D7
            #define DISPLAY_D7 8
        #endif
        LiquidCrystal _lcd = LiquidCrystal(DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

        #ifndef NUM_CASES
            #define NUM_CASES 5
            #define CASE0 "Iniciar Processo"
            #define CASE1 "Retornar"
            #define CASE2 "Vel. Avanço"
            #define CASE3 "Vel. Mergulho"
            #define CASE4 "Temp. Decorri."
            String _content_menus[NUM_CASES][2] = {{CASE0, ""}, {CASE1, ""}, {CASE2, " cm/min"}, {CASE3, " cm/min"}, {CASE4, " s"}};
        #endif
        int _current_window = 0;
        

        // String _content_menus[NUM_CASES][2] = {{"Iniciar Processo", ""}, {"Retornar", ""}, {"Vel. Avanco", "0 cm/min"}, {"Vel. Mergulho", "0 cm/min"}};
        // uint16_t dive_speed;
        
    public:
        DisplayController();
        DisplayController(const uint8_t& feed_speed, const uint8_t& dive_speed);
        DisplayController(const uint8_t& feed_speed, const uint8_t& dive_speed, const uint8_t process_start_delay);
        ~DisplayController();
        int get_current_window();
        // uint8_t get_dive_speed();

        void set_menu_content(const uint8_t& content);
        void set_menu_content(uint8_t* initial_values, uint8_t num_values);
        void set_current_window(uint8_t new_window);

        void next_window();
        void previous_window();
        void initialize_display();
        void initialize_display(bool has_init_speeds);
        void update_display();
        void process_window();
        void countdown_window();
};

#endif // DISPLAYCONTROLLER_H