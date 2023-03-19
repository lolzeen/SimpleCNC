#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include "Button.hpp"
const uint8_t HOME = 0;
const uint8_t FINISH = 1;
const uint8_t FORWARD = 1;
const uint8_t BACKWARD = 0;
const uint8_t MIN_TIME = 30; // seconds // TODO: confirm this with CAD model
const uint8_t IDDLE = 0;
const uint8_t WELD = 1;
const uint8_t RETURN = 2;
const uint8_t MANUAL_POSITIONING = 3;
// const double INP_VOLTAGE_TO_REAL_VOLTAGE_MULTIPLIER = 0.05865102639296188; 
const double INP_VOLTAGE_TO_REAL_VOLTAGE_MULTIPLIER = 5./1023.; 
// Microchip ATmega2560 DataSheet p.151 freq = clk_freq/(2 * PreScaler * TOP) clk_fre=16MHz PreScaler=64 TOP = OCR_Value // TODO fix this description since this formula is only the begining of the calculation
const float STEP_GENERATOR_FREQ_MULTIPLIER = 0.041664; // TODO corrigir essa merda

struct DriverPins
{
    uint8_t _ES1;
    uint8_t _ES2;
    uint8_t _DIR;
    uint8_t _EN;
    uint8_t _STEP;
    uint8_t _OUT;
};
 
class MotorController
{
    private:
        uint8_t lastPosition;
        uint8_t movementDirection;
        uint8_t enableMovement;
        long stepFrequency; // Hz
        uint64_t numberOfPulses;
        uint8_t maxDistance; // cm
        uint8_t distance; // cm
        float processDuration; // min
        int16_t speed; // cm/min
        uint16_t ocr; 
        uint16_t pulsesPerRevolution;
        uint8_t _id; // timer identifier
        uint8_t arcControllerGain = 0;
        uint8_t weldingVoltage = 0;
        uint8_t shortCircuitVoltage = 0;
        uint8_t voltageTolerance = 0;
        uint8_t delayInitTravel = 0; // milliseconds
        bool isArcOpen = false;
        bool isHeightControllerActive = false;
        static uint8_t runningProcess;

        DriverPins _driver_pins;
        Button _end_switch1, _end_switch2;
        /**
         * @brief 
         * 
         */
        void calcFreq();
        /**
         * @brief 
         * 
         */
        void calcOcr();
        void releaseEndSwitch();
        /**
         * @brief 
         * 
         * @param releaseEndSwitch 
         */
        void processEndSwitch(bool releaseEndSwitch);
        /**
         * @brief 
         * 
         * @param pins 
         */
        void io_setup(const DriverPins &pins);
        /**
        * @brief Compute equivalent voltage based on analoread() value. Assuming input values 0-1023 and output 0-60V
        * 
        */
        double readVoltage();
        /**
         * @brief Set the Timers attribute
         * 
         */
        void setTimers();
        /**
         * @brief 
         * 
         */
        void stopTimers();
        /**
         * @brief 
         * 
         */
        void verifyDistance();
        /**
         * @brief 
         * 
         */
        void saveParameters();

    public:
        MotorController();
        MotorController(const DriverPins &pins);
        MotorController(const DriverPins &pins, const uint16_t &driver_pul_rev, const uint8_t &id, uint8_t dis);
        ~MotorController();
        
        void setDistance(const uint8_t dist) {distance = dist;}
        void setMaxDistance(const uint8_t dist) {maxDistance = dist;}
        void setProcessDuration(const uint8_t time) {processDuration = time;}
        void setSpeed(const int16_t newSpeed) {speed = newSpeed;}
        void setOcr(const uint16_t ocr_top) {ocr = ocr_top;}
        void setFreq(const long freq) {stepFrequency = freq;} // TODO: review usability
        void setNumberOfPulses(const uint64_t num) {numberOfPulses = num;} // TODO: review usability
        void setLastPosition(const uint8_t pos) {lastPosition = pos;}  // TODO: review usability
        void set_pos(uint8_t pos) {setLastPosition(pos);} // TODO: find better name for this function  // TODO: review usability
        void setarcControllerGain(uint8_t gain) {arcControllerGain = gain;}
        void setWeldingVoltage(uint8_t voltage) {weldingVoltage = voltage;}
        void setShortCircuitVoltage(uint8_t voltage) {shortCircuitVoltage = voltage;}
        void setDelayInitTravel(uint8_t ms) {delayInitTravel = ms;}
        void setIsArcOpen(bool val) {isArcOpen = val;}
        static void setRunningProcess(uint8_t process);
        void setVoltageTolerance(uint8_t voltage) {voltageTolerance = voltage;}

        const uint8_t getMovementDirection() {return movementDirection;}
        const uint8_t getEnableMovement() {return enableMovement;}
        const long get_freq() {return stepFrequency;}
        const uint8_t getDistance() {return distance;}
        const uint8_t getMaxDistance() {return maxDistance;}
        const uint8_t getProcessDuration() {return processDuration;}
        const int16_t getSpeed() {return speed;}
        const uint16_t getOcr() {return ocr;}
        const uint8_t getPos() {return lastPosition;}
        const uint8_t getArcControllerGain() {return arcControllerGain;}
        const uint8_t getWeldingVoltage() {return weldingVoltage;}
        const uint8_t getShortCircuitVoltage() {return shortCircuitVoltage;}
        const uint8_t getVoltageTolerance() {return voltageTolerance;}
        const uint8_t getDelayInitTravel() {return delayInitTravel;}
        const bool getIsArcOpen() {return isArcOpen;}
        const static uint8_t getRunningProcess() {return runningProcess;};
        /**
         * @brief Ceases the arc by pully the z axxis upwards.
         * 
         */
        void closeArc();
        /**
         * @brief Proportional controller that ajdusts arc lenght based on arc voltage. The error is calculated by converting the measured voltage (0-1023) to the equivalent arc voltage (assuming maximum arc voltage is 60V and it is equivalent to 5V, 60/1023=0.05865) minus the desired voltage. The error is then multiplied by the actual speed and the controller gain, if it overshoots the movementDirection is reversed.
         */
        void correctHeight();
        void returnHome();
        void setMovementDirection(const uint8_t state);
        void setEnableMovement(const uint8_t  state);
        void setProcess();
        void startProcess();
        void startProcess(uint8_t mode);
        void run();
        void run(bool activate_correct_height);
        static void run(MotorController& xAxis, MotorController& zAxis);
        void toggleCorrectHeight() {isHeightControllerActive = !isHeightControllerActive;}
};
#endif // MOTORCONTROLLER_H