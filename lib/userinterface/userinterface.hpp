#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <Arduino.h>
#include "motorcontroller.hpp"
#include "Debounce.hpp"
#include <LiquidCrystal.h>


struct InputPins
{
    InputPins()
    {
        // intentionally empty
    }
    InputPins(const uint8_t& b1, const uint8_t& b2, const uint8_t& pot)
    {
        button_1 = b1;
        button_2 = b2;
        potentiometer = pot;
    }
    InputPins(const InputPins& input_pins)
    {
        button_1 = input_pins.button_1;
        button_2 = input_pins.button_2;
        potentiometer = input_pins.potentiometer;
    }
    // button change
    uint8_t button_1;
    // buton select
    uint8_t button_2;
    uint8_t potentiometer;
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

class UserInterface
{
private:

    InputPins _input_pins;
    DisplayPins _display_pins;
    Debounce _button_change, _button_select;
    
    uint8_t _pot_pin = A0;
    int _pot_value = 0;

    // LiquidCrystal _lcd;
    
    // LiquidCrystal _lcd = LiquidCrystal(_display_pins.RS, _display_pins.EN, _display_pins.D4, _display_pins.D5, _display_pins.D6, _display_pins.D7);
    const uint8_t display_rs = 13;
    const uint8_t display_en = 12;
    const uint8_t display_d4 = 11;
    const uint8_t display_d5 = 10;
    const uint8_t display_d6 = 9;
    const uint8_t display_d7 = 8; 
    LiquidCrystal _lcd = LiquidCrystal(display_rs, display_en, display_d4, display_d5, display_d6, display_d7);

    const uint8_t _num_windows = 3;
    uint8_t _cursor_position = 0;
    int _current_window = 0;
    float _velocidade_avanco = 0.;
    float _velocidade_mergulho = 0.;

    
    void set_current_window(int new_window);
    void set_cursor_position(uint8_t new_cur_pos);
    void set_menu_content();

public:
    UserInterface();
    UserInterface(const InputPins& in_pins, const DisplayPins& disp_pins);
    ~UserInterface();

    String content_menus[3][2] = {{"Iniciar Processo", "Ajustes ->"}, {"Vel. Avanco", "cm/min"}, {"Vel. Mergulho", "cm/min"}};

    int get_pot_input();
    void get_button_input(const int& button);
    int get_current_window();
    uint8_t get_cursor_position();
    void initialize_display();

    void display_menu();
    // TODO: function initiate process
};

#endif //UserInterface_H