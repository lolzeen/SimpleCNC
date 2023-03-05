#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H
#include <Arduino.h>
#include <EEPROM.h>
#include "MotorController.hpp"

class MemoryController
{
public:
    MemoryController();
    ~MemoryController();
    int16_t getShortCircuitVoltage() {return weldingParameters.shortCircuitVoltage.value;};
    int16_t getWeldingVoltage() {return weldingParameters.weldingVoltage.value;};
    int16_t getArcControllerGain() {return weldingParameters.arcControllerGain.value;};
    int16_t getVoltageTolerance() {return weldingParameters.voltageTolerance.value;};
    int16_t getDelayInitTravel() {return weldingParameters.delayInitTravel.value;};
    int16_t getTravelSpeed() {return weldingParameters.travelSpeed.value;};
    int16_t getFeedSpeed() {return weldingParameters.feedSpeed.value;};
    int16_t getValueFromAddress(int16_t memoryAddres);
    
    void setShortCircuitVoltage(int16_t val) {weldingParameters.shortCircuitVoltage.value = val;};
    void setWeldingVoltage(int16_t val) {weldingParameters.weldingVoltage.value = val;};
    void setArcControllerGain(int16_t val) {weldingParameters.arcControllerGain.value  = val;};
    void setVoltageTolerance(int16_t val) {weldingParameters.voltageTolerance.value = val;};
    void setDelayInitTravel(int16_t val) {weldingParameters.delayInitTravel.value = val;};
    void setTravelSpeed(int16_t val) {weldingParameters.travelSpeed.value  = val;};
    void setFeedSpeed(int16_t val) {weldingParameters.feedSpeed.value  = val;};
    String toString();
    void updateWeldingParametersFromEeprom();
    void updateEepromFromWeldingParameters();
    bool verifyParameterValue(const int value);

    struct ParameterIdAndData {
        int16_t identifier = 0;
        int16_t value = 0;
    };

    struct WeldingParameters {
        ParameterIdAndData shortCircuitVoltage;
        ParameterIdAndData weldingVoltage;
        ParameterIdAndData arcControllerGain;
        ParameterIdAndData voltageTolerance;
        ParameterIdAndData delayInitTravel;
        ParameterIdAndData feedSpeed;
        ParameterIdAndData travelSpeed;
    };


    enum MemoryAddress : int16_t {SHORT_CIRCUIT_VOLTAGE_ADDR=0,
                WELDING_VOLTAGE_ADDR=sizeof(int16_t),
                ARC_CONTROLLER_GAIN_ADDR=sizeof(int16_t)*2,
                VOLTAGE_TOLERANCE_ADDR=sizeof(int16_t)*3,
                DELAY_INIT_TRAVEL_ADDR=sizeof(int16_t)*4,
                FEED_SPEED_ADDR=sizeof(int16_t)*5,
                TRAVEL_SPEED_ADDR=sizeof(int16_t)*6,
                LAST};
private:
    WeldingParameters weldingParameters;
};

#endif // MEMORY_CONTROLLER_H