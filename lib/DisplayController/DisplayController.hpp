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
enum content_descriptors {EDIT_POS_HORIZONTAL=200,
                        EDIT_POS_VERTICAL=210,
                        EDIT_SPEED_FORW=3100,
                        EDIT_SPEED_DIVE=3110,
                        EDIT_VOLTAGE_TOLERANCE=3020, 
                        EDIT_ARC_GAIN=3030,
                        EDIT_ARC_SHORT_CIRCUIT_VOLTAGE=3000,
                        EDIT_WELDING_VOLTAGE=3010,
                        EDIT_DELAY_INIT_FORWARD_MOVE=3040};

class DisplayController 
{
    private:
        const int valid_window_ids[32] = {0,1,2,3,20,21,22,200,210,30,31,32,33,300,3000,301,3010,302,3020,303,3030,304,3040,305,306,31,310,3100,311,3110,312,313};
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

        #define MES_INIT "Iniciar Processo" // 0
        #define MES_RETU "Retornar" // 1
        #define MES_POS "Pos. Manual" // 2
        #define MES_POS_HORI "Horizontal" // 20
        #define MES_POS_VERT "Vertical"  // 21
        #define MES_POS_EDIT " cm/min" // 20-21
        #define MES_CONFIG "Configuracoes" // 3
        #define MES_SPEED "Velocidade" // 31
        #define MES_SPEED_FORW "Avanco" // 310
        #define MES_SPEED_DIVE "Mergulho" // 311
        #define MES_SPEED_EDIT " cm/min" // 3100-3110
        #define MES_ARC "Param. Soldagem" // 30
        #define MES_ARC_GAIN "Ganho do Control." // 303
        #define MES_ARC_TOL "Tolerancia" // 302
        #define MES_ARC_TOL_EDIT " V" // 3020
        #define MES_ARC_GAIN_EDIT "" // 3030
        #define MES_ARC_SHORT_CIRCUIT_VOLTAGE "Tensao de CC" // 300
        #define MES_ARC_VOLTAGE "Tensao Sold." // 301
        #define MES_ARC_SHORT_CIRCUIT_VOLTAGE_EDIT " V" // 3000-3010
        #define MES_DELAY_INIT_FOWARD_MOVE "Delay Avanco" // 304
        #define MES_EDIT_DELAY_INIT_FOWARD_MOVE " s" // 3040
        #define MES_SAVE "Salvar Confg." // 32
        #define MES_PRESS_CONFIRM "Press. p. Confir." 
        #define MES_PRESS_EDIT "Press. p. Editar"
        #define MES_RETURN_PREVIOUS_MENU "Menu Anterior" // 305-312
        #define MES_RETURN_MAIN_MENU "Menu Principal" // 22-33-306-313
            // String _content_menus[NUM_CASES][2] = {{CASE0, ""}, {CASE1, ""}, {CASE2, " cm/min"}, {CASE3, " cm/min"}, {CASE4, " mm"}};
        int _current_window = 0;
        int8_t _enc_direction;
        volatile int16_t _enc_count = 0;
        bool _button_state = false;
        bool _adjust_menu = false;
        bool _init_process = false;
        bool _return_home = false;
        
    public:
        DisplayController();
        DisplayController(const InputPins& in_pins);
        ~DisplayController();
        const int get_current_window() {return _current_window;};
        const bool get_init_process() {return _init_process;};
        const bool get_return_home() {return _return_home;};
        const bool get_adjust_menu() {return _adjust_menu;};
        const int8_t get_enc_direction() {return _enc_direction;};
        const int8_t get_enc_count() {return _enc_count;};

        void set_menu_content(String lower);
        void set_menu_content(const char* upper, const char* lower);
        void set_menu_content(int content_descriptor, String content);
        void set_menu_content(int content_descriptor, int content);
        void set_current_window(uint16_t new_window) {_current_window = new_window;};
        void set_init_process(bool var) {_init_process = var;};
        void set_return_home(bool var) {_return_home = var;};
        void set_adjust_menu(bool var) {_adjust_menu = var;};
        void set_enc_count(int16_t num) {_enc_count = num;};

        void button_press();
        void button_press(bool activate_update_display);
        void countdown_window();
        void initialize_display();
        void initialize_display(bool has_init_speeds);
        void monitor_user_input() {read_enc_values();button_press();};
        void next_window();
        void next_option();
        void previous_window();
        void previous_option();
        void process_window();
        void read_enc_values();
        void update_display_static();
        void update_display_dynamic(int content_descriptor, String content);
        void update_display_dynamic(int content_descriptor, uint8_t content);
        bool validateWindow(int id);
        // void encoder_action();
        // bool validate_enc_values();
};

#endif // DISPLAYCONTROLLER_H