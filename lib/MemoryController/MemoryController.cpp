#include "MemoryController.hpp"

template <class T>
MemoryController<T>::MemoryController() {
    WeldingParameters::arcControllerGain = {ARC_CONTROLLER_GAIN_ADDR, 0};
    WeldingParameters::shortCircuitVoltage = {SHORT_CIRCUIT_VOLTAGE_ADDR, 0};
    WeldingParameters::feedSpeed = {FEED_SPEED_ADDR, 0};
    WeldingParameters::weldingVoltage = {WELDING_VOLTAGE_ADDR, 0};
    WeldingParameters::voltageTolerance = {VOLTAGE_TOLERANCE_ADDR, 0};
    WeldingParameters::travelSpeed = {TRAVEL_SPEED_ADDR, 0};
    WeldingParameters::delayInitTravel = {DELAY_INIT_TRAVEL_ADDR, 0};
    updateWeldingParametersFromEeprom();
}
template <class T>
MemoryController<T>::~MemoryController() {
    // intentionally empty
}
template <class T>
T MemoryController<T>::getValueFromAddress(T memoryAddres) {
    T val = 0;
    EEPROM.get(memoryAddres, val);
    return val;
}
template <class T>
String MemoryController<T>::toString() {
    String str;
    str += "ArcShortVol.: " + (String)getShortCircuitVoltage();
    str += "\nWeldVol.: " + (String)getWeldingVoltage();
    str += "\nArcControlGain.: " + (String)getArcControllerGain();
    str += "\nVolTol.: " + (String)getVoltageTolerance();
    str += "\nDelay.: " + (String)getDelayInitTravel();
    str += "\nTravelSpeed.: " + (String)getTravelSpeed();
    str += "\nFeedSpeed.: " + (String)getFeedSpeed();
    return str;
}
template <class T>
void MemoryController<T>::updateEepromFromWeldingParameters() {
    EEPROM.put(ARC_CONTROLLER_GAIN_ADDR, WeldingParameters::arcControllerGain.value);
    EEPROM.put(SHORT_CIRCUIT_VOLTAGE_ADDR, WeldingParameters::shortCircuitVoltage.value);
    EEPROM.put(FEED_SPEED_ADDR, WeldingParameters::feedSpeed.value);
    EEPROM.put(WELDING_VOLTAGE_ADDR, WeldingParameters::weldingVoltage.value);
    EEPROM.put(VOLTAGE_TOLERANCE_ADDR, WeldingParameters::voltageTolerance.value);
    EEPROM.put(TRAVEL_SPEED_ADDR, WeldingParameters::travelSpeed.value);
    EEPROM.put(DELAY_INIT_TRAVEL_ADDR, WeldingParameters::delayInitTravel.value);
}
template <class T>
void MemoryController<T>::updateWeldingParametersFromEeprom() {
    T var;
    EEPROM.get(ARC_CONTROLLER_GAIN_ADDR, var);
    setArcControllerGain(var);
    EEPROM.get(SHORT_CIRCUIT_VOLTAGE_ADDR, WeldingParameters::shortCircuitVoltage.value);
    EEPROM.get(FEED_SPEED_ADDR, WeldingParameters::feedSpeed.value);
    EEPROM.get(WELDING_VOLTAGE_ADDR, WeldingParameters::weldingVoltage.value);
    EEPROM.get(VOLTAGE_TOLERANCE_ADDR, WeldingParameters::voltageTolerance.value);
    EEPROM.get(TRAVEL_SPEED_ADDR, WeldingParameters::travelSpeed.value);
    EEPROM.get(DELAY_INIT_TRAVEL_ADDR, WeldingParameters::delayInitTravel.value);
}
template <class T>
bool MemoryController<T>::verifyParameterValue(const int value)
{
    if (value != 0) return true;
    return false;
}