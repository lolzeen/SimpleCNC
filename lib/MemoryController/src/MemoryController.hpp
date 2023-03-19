#ifndef MEMORY_CONTROLLER_H
#define MEMORY_CONTROLLER_H
#include <Arduino.h>
#include <EEPROM.h>
#include "MotorController.hpp"

template <typename T>
class MemoryController
{
public:
    MemoryController();
    ~MemoryController();
    T getShortCircuitVoltage() {return weldingParameters.shortCircuitVoltage.value;};
    T getWeldingVoltage() {return weldingParameters.weldingVoltage.value;};
    T getArcControllerGain() {return weldingParameters.arcControllerGain.value;};
    T getVoltageTolerance() {return weldingParameters.voltageTolerance.value;};
    T getDelayInitTravel() {return weldingParameters.delayInitTravel.value;};
    T getTravelSpeed() {return weldingParameters.travelSpeed.value;};
    T getFeedSpeed() {return weldingParameters.feedSpeed.value;};
    T getValueFromAddress(int memoryAddres);
    
    void setShortCircuitVoltage(T val) {weldingParameters.shortCircuitVoltage.value = val;};
    void setWeldingVoltage(T val) {weldingParameters.weldingVoltage.value = val;};
    void setArcControllerGain(T val) {weldingParameters.arcControllerGain.value  = val;};
    void setVoltageTolerance(T val) {weldingParameters.voltageTolerance.value = val;};
    void setDelayInitTravel(T val) {weldingParameters.delayInitTravel.value = val;};
    void setTravelSpeed(T val) {weldingParameters.travelSpeed.value  = val;};
    void setFeedSpeed(T val) {weldingParameters.feedSpeed.value  = val;};
    String toString();
    void updateWeldingParametersFromEeprom();
    void updateEepromFromWeldingParameters();
    bool verifyParameterValue(const T value);

    struct ParameterIdAndData {
        int identifier = 0;
        T value = 0;
    };

    struct WeldingParameters {
        ParameterIdAndData shortCircuitVoltage;
        ParameterIdAndData weldingVoltage;
        ParameterIdAndData arcControllerGain;
        ParameterIdAndData voltageTolerance;
        ParameterIdAndData delayInitTravel;
        ParameterIdAndData feedSpeed;
        ParameterIdAndData travelSpeed;
    }weldingParameters;

    // TODO: save the values on variables in order to observe the response
    enum class MemoryAddress : int {SHORT_CIRCUIT_VOLTAGE_ADDR=0,
                WELDING_VOLTAGE_ADDR=sizeof(T),
                ARC_CONTROLLER_GAIN_ADDR=sizeof(T)*2,
                VOLTAGE_TOLERANCE_ADDR=sizeof(T)*3,
                DELAY_INIT_TRAVEL_ADDR=sizeof(T)*4,
                FEED_SPEED_ADDR=sizeof(T)*5,
                TRAVEL_SPEED_ADDR=sizeof(T)*6,
                LAST};
};
typedef typename MemoryController<int>::MemoryAddress Address;
static MemoryController<int> MEMORY_CONTROLLER;

#endif // MEMORY_CONTROLLER_H