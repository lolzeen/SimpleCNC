#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Button.hpp"
#include "Encoder.hpp"

struct InputPins
{
    InputPins()
    {
        // intentionally empty
    }
    InputPins(const uint8_t& b, const uint8_t& enc_a, const uint8_t& enc_b)
    {
        button = b;
        encoder_a = enc_a;
        encoder_b = enc_b;
    }
    InputPins(const InputPins& input_pins)
    {
        button = input_pins.button;
        encoder_a = input_pins.encoder_a;
        encoder_b = input_pins.encoder_b;
    }
    uint8_t button;
    uint8_t encoder_a;
    uint8_t encoder_b;
};
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
    enum content_descriptors {POS_EDIT_HORIZONTAL=200, POS_EDIT_VERTICAL=210, SPEED_EDIT_HORIZONTAL=300, SPEED_EDIT_VERTICAL=310, VOLTAGE_TOLERANCE=400, ARC_GAIN_EDIT=410, ARC_SHORT_CIRCUIT_VOLTAGE_EDIT=420, WELDING_VOLTAGE=430};

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
        Button _button;
        Encoder _encoder;
        InputPins _input_pins;

        // #ifndef NUM_CASES
        //     #define NUM_CASES 5
        //     #define CASE0 "Iniciar Processo"
        //     #define CASE1 "Retornar"
        //     #define CASE2 "Vel. Avanço"
        //     #define CASE3 "Vel. Mergulho"
        //     #define CASE4 "Temp. Decorri."
        //     String _content_menus[NUM_CASES][2] = {{CASE0, ""}, {CASE1, ""}, {CASE2, " cm/min"}, {CASE3, " cm/min"}, {CASE4, " s"}};
        // #endif
        #ifndef NUM_CASES
            #define NUM_CASES 20
            #define MES_INIT "Iniciar Processo" // 0
            #define MES_RETU "Retornar" // 1
            #define MES_POS "Pos. Manual" // 2
            #define MES_POS_HORI "Horizontal"
            #define MES_POS_VERT "Vertical" 
            #define MES_POS_EDIT "Vel: --- cm/min  "
            #define MES_SPEED "Velocidade" // 3
            #define MES_SPEED_FORW "Avanço" 
            #define MES_SPEED_DIVE "Mergulho"
            #define MES_SPEED_EDIT "--- cm/min       "
            #define MES_ARC "Param. Arco" // 4
            #define MES_ARC_GAIN "Ganho do Control."
            #define MES_ARC_GAIN_EDIT "mutiplicador: ---"
            #define MES_ARC_SHORT_CIRCUIT_VOLTAGE "Tensão de CC"
            #define MES_ARC_SHORT_CIRCUIT_VOLTAGE_EDIT "--- V"
            #define MES_SAVE "Salvar Confg." // 5
            #define MES_PRESS_CONFIRM "Press. p. Confir."
            #define MES_PRESS_EDIT "Press. p. Editar"
            #define MES_RETURN_PREVIOUS_MENU "Menu Anterior"
            #define MES_RETURN_MAIN_MENU "Menu Principal"
            // String _content_menus[NUM_CASES][2] = {{CASE0, ""}, {CASE1, ""}, {CASE2, " cm/min"}, {CASE3, " cm/min"}, {CASE4, " mm"}};
        #endif
        int _current_window = 0;
        int _speed_value = 10; // TODO: to definindo a vlocidade la no setup, tem que combinar essas duas
        int8_t _enc_direction;
        volatile int8_t _enc_count = 0;
        bool _button_state = false;
        bool _change_menu = false;
        bool _adjust_menu = false;
        bool _change_window = false;
        bool _init_process = false;
        bool _return_home = false;
        uint8_t _initial_arc_height = 0; // mm

        // String _content_menus[NUM_CASES][2] = {{"Iniciar Processo", ""}, {"Retornar", ""}, {"Vel. Avanco", "0 cm/min"}, {"Vel. Mergulho", "0 cm/min"}};
        // uint16_t dive_speed;
        
    public:
        DisplayController();
        DisplayController(const InputPins& in_pins);
        DisplayController(const InputPins& in_pins, const uint8_t& feed_speed, const uint8_t& dive_speed);
        // DisplayController(const uint8_t& feed_speed, const uint8_t& dive_speed, const uint8_t process_start_delay);
        ~DisplayController();
        const int get_current_window();
        const bool get_init_process();
        const bool get_return_home();
        const bool get_change_menu();
        const bool get_adjust_menu();
        const bool get_change_window();
        const int get_speed_value();
        const int8_t get_enc_direction();
        const int8_t get_enc_count();
        const uint8_t get_arc_height();
        // uint8_t get_dive_speed();

        void set_menu_content(const uint8_t& content);
        void set_menu_content(uint8_t* initial_values, uint8_t num_values);
        void set_menu_content(String lower);
        void set_menu_content(const char* upper, const char* lower);
        void set_menu_content(int content_descriptor, String content);
        void set_current_window(uint8_t new_window);
        void set_init_process(bool var);
        void set_return_home(bool var);
        void set_change_menu(bool var);
        void set_adjust_menu(bool var);
        void set_change_window(bool var);
        void set_enc_count(int8_t num);
        void set_arc_height(uint8_t height);

        void next_window();
        void next_option();
        void previous_window();
        void previous_option();
        void initialize_display();
        void initialize_display(bool has_init_speeds);
        void update_display();
        void process_window();
        void countdown_window();
        void button_press();
        void button_press(bool activate_update_display);
        void read_enc_values();
        // void encoder_action();
        // bool validate_enc_values();
};

#endif // DISPLAYCONTROLLER_H