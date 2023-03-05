#ifndef DISPLAYCONTROLLER_H
#define DISPLAYCONTROLLER_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include "Button.hpp"
#include "Encoder.hpp"
#include "MemoryController.hpp"

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
enum menuWindowSpecifier {EDIT_POS_HORIZONTAL=200,
                        EDIT_POS_VERTICAL=210,
                        EDIT_TRAVEL_SPEED=3100,
                        EDIT_FEED_SPEED=3110,
                        EDIT_VOLTAGE_TOLERANCE=3020, 
                        EDIT_ARC_GAIN=3030,
                        EDIT_SHORT_CIRCUIT_VOLTAGE=3000,
                        EDIT_WELDING_VOLTAGE=3010,
                        EDIT_DELAY_INIT_TRAVEL=3040,
                        SAVE_SETTINGS=32};

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
        MemoryController MEMORY_CONTROLLER;
        volatile bool buttonPressedFlag = false;

        #define MES_INIT "Iniciar Processo" // 0
        #define MES_RETU "Retornar" // 1
        #define MES_POS "Pos. Manual" // 2
        #define MES_POS_HORI "Horizontal" // 20
        #define MES_POS_VERT "Vertical"  // 21
        #define MES_POS_EDIT " cm/min" // 20-21
        #define MES_CONFIG "Configuracoes" // 3
        #define MES_SPEED "Velocidade" // 31
        #define MES_TRAVEL_SPEED "Avanco" // 310
        #define MES_FEED_SPEED "Mergulho" // 311
        #define MES_SPEED_EDIT " cm/min" // 3100-3110
        #define MES_ARC "Param. Soldagem" // 30
        #define MES_ARC_GAIN "Ganho do Control." // 303
        #define MES_ARC_TOL "Tolerancia" // 302
        #define MES_ARC_TOL_EDIT " V" // 3020
        #define MES_ARC_GAIN_EDIT "" // 3030
        #define MES_ARCshortCircuitVoltage "Tensao de CC" // 300
        #define MES_ARC_VOLTAGE "Tensao Sold." // 301
        #define MES_ARCshortCircuitVoltage_EDIT " V" // 3000-3010
        #define MES_DELAY_INIT_TRAVEL "Delay Avanco" // 304
        #define MES_EDIT_DELAY_INIT_TRAVEL " s" // 3040
        #define MES_SAVE "Salvar Confg." // 32
        #define MES_PRESS_CONFIRM "Press. p. Confir." 
        #define MES_PRESS_EDIT "Press. p. Editar"
        #define MES_RETURN_PREVIOUS_MENU "Menu Anterior" // 305-312
        #define MES_RETURN_MAIN_MENU "Menu Principal" // 22-33-306-313
            // String _content_menus[NUM_CASES][2] = {{CASE0, ""}, {CASE1, ""}, {CASE2, " cm/min"}, {CASE3, " cm/min"}, {CASE4, " mm"}};
        int currentWindow = 0;
        volatile int8_t encoderMovementDirection;
        volatile int8_t encoderCount = 0;
        volatile int8_t lastEncoderCount = 0;
        uint64_t lastButtonPress = 0;
        // bool buttonState = false;
        bool adjustMenu = false;
        bool initProcess = false;
        bool returnHome = false;
        bool enableMonitorUserInput = false;

        void constructor();

    public:
        DisplayController();
        DisplayController(const InputPins& in_pins);
        DisplayController(MemoryController& memoryController, const InputPins& in_pins);
        ~DisplayController();
        const int getCurrentWindow() {return currentWindow;}
        const bool getInitProcess() {return initProcess;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        const bool getReturnHome() {return returnHome;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        const bool getAdjustMenu() {return adjustMenu;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        bool getButtonPressedFlag() {return buttonPressedFlag;};
        const int8_t getEncoderMovementDirection() {return encoderMovementDirection;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 2)
        const int8_t getEncoderCount() {return encoderCount;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 2)
        bool checkEncoderMovement();
        void displayPrint(const char* upper, const char* lower);
        void displayPrint(int menuWindowSpecifier, String content);
        void displayPrint(int menuWindowSpecifier, int content);
        void executeCountdownWindow();// TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 1)
        void initializeDisplay();
        void liveEditPosition(MotorController &axis);
        void monitorUserInput() {processEncoderInput();processButtonInput();}
        void moveToNextWindow();// TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 3) 
        void moveToInnerWindow(); // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 3) 
        void moveToPreviousWindow();// TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 3) 
        void moveToOuterWindow(); // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 3) 
        bool navigateThroughParallelWindows();
        /**
         * @brief If the button was pressed, performs an action acording to the current window.
         * 
         */
        void processButtonInput(); // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 2)
        void run();
        void resetEconderCount();
        void setButtonPressedFlag(bool newState) {buttonPressedFlag = newState;}
        void setCurrentWindow(uint16_t new_window) {
            currentWindow = new_window;
        } // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        void setInitProcess(bool var) {initProcess = var;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        void setReturnHome(bool var) {returnHome = var;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        void setAdjustMenu(bool var) {adjustMenu = var;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        void setEncoderCount(int16_t num) {encoderCount = num;} // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 4)
        void executeProcessWindow();// TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 1)
        void executeButtonAction();
        void processEncoderInput(); // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 2)
        /**
         * @brief Update display with PREDEFINED information. Reads the data stored on the FLASH memory, if this data is not null print on the lcd display. If the data stored on the FLASH is null then searches the EPROM memory and print its content.
         * 
         */
        void updateDisplay();
        /**
         * @brief Update display with ACQUIRED DATA information. Intended for all transitions that print acquired data.
         * 
         * @param menuWindowSpecifier 
         * @param content 
         */
        void updateDisplay(int menuWindowSpecifier, String content);
        /**
         * @brief Update display with ACQUIRED DATA information. Intended for all transitions that print acquired data.
         * 
         * @param menuWindowSpecifier 
         * @param content 
         */
        void updateDisplay(int menuWindowSpecifier, uint8_t content);
        void updateLastEncoderCount() {
            lastEncoderCount = encoderCount;
        }
        bool validateWindow(int id);
        bool verifyIfDataIsNull(); // TODO: REDUCE RESPONSIBILITY this should be in a different class (Classe 5)
};
#endif // DISPLAYCONTROLLER_H