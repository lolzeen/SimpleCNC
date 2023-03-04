#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H
#include <Arduino.h>
#include <EEPROM.h>
#include "MotorController.hpp"

template <class T>
class MemoryController
{
public:
    MemoryController();
    ~MemoryController();
    T getShortCircuitVoltage() const {return WeldingParameters::shortCircuitVoltage.value;};
    T getWeldingVoltage() const {return WeldingParameters::weldingVoltage.value;};
    T getArcControllerGain() const {return WeldingParameters::arcControllerGain.value;};
    T getVoltageTolerance() const {return WeldingParameters::voltageTolerance.value;};
    T getDelayInitTravel() const {return WeldingParameters::delayInitTravel.value;};
    T getTravelSpeed() const {return WeldingParameters::travelSpeed.value;};
    T getFeedSpeed() const {return WeldingParameters::feedSpeed.value;};
    T getValueFromAddress(T memoryAddres);

    
    void setShortCircuitVoltage(T val) {WeldingParameters::shortCircuitVoltage.value = val;};
    void setWeldingVoltage(T val) {WeldingParameters::weldingVoltage.value = val;};
    void setArcControllerGain(T val) {WeldingParameters::arcControllerGain.value  = val;};
    void setVoltageTolerance(T val) {WeldingParameters::voltageTolerance.value = val;};
    void setDelayInitTravel(T val) {WeldingParameters::delayInitTravel.value = val;};
    void setTravelSpeed(T val) {WeldingParameters::travelSpeed.value  = val;};
    void setFeedSpeed(T val) {WeldingParameters::feedSpeed.value  = val;};
    String toString();
    void updateWeldingParametersFromEeprom();
    void updateEepromFromWeldingParameters();
    bool verifyParameterValue(const int value);

    struct ParameterIdAndData {
        T identifier;
        T value;
    };

    struct WeldingParameters {
        static ParameterIdAndData shortCircuitVoltage;
        static ParameterIdAndData weldingVoltage;
        static ParameterIdAndData arcControllerGain;
        static ParameterIdAndData voltageTolerance;
        static ParameterIdAndData delayInitTravel;
        static ParameterIdAndData feedSpeed;
        static ParameterIdAndData travelSpeed;
    };

    enum MemoryAddress : T {SHORT_CIRCUIT_VOLTAGE_ADDR=0,
                WELDING_VOLTAGE_ADDR=sizeof(T),
                ARC_CONTROLLER_GAIN_ADDR=sizeof(T)*2,
                VOLTAGE_TOLERANCE_ADDR=sizeof(T)*3,
                DELAY_INIT_TRAVEL_ADDR=sizeof(T)*4,
                FEED_SPEED_ADDR=sizeof(T)*5,
                TRAVEL_SPEED_ADDR=sizeof(T)*6,
                LAST};
};
static MemoryController<int16_t> MEMORY_CONTROLLER;
#endif // MEMORY_CONTROLLER_H