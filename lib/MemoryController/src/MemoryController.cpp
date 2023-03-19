#include "MemoryController.hpp"
template <typename T>
MemoryController<T>::MemoryController() {
    updateWeldingParametersFromEeprom();
}

template <typename T>
MemoryController<T>::~MemoryController() {
    // intentionally empty
}

template <typename T>
T MemoryController<T>::getValueFromAddress(int memoryAddres) {
    T val = 0;
    EEPROM.get(memoryAddres, val);
    return val;
}

template <typename T>
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

template <typename T>
void MemoryController<T>::updateEepromFromWeldingParameters() {
    T temp = 0;
    temp = getArcControllerGain();
    EEPROM.put(static_cast<int>(Address::ARC_CONTROLLER_GAIN_ADDR), temp);
    temp = getShortCircuitVoltage();
    EEPROM.put(static_cast<int>(Address::SHORT_CIRCUIT_VOLTAGE_ADDR), temp);
    temp = getFeedSpeed();
    EEPROM.put(static_cast<int>(Address::FEED_SPEED_ADDR), temp);
    temp = getWeldingVoltage();
    EEPROM.put(static_cast<int>(Address::WELDING_VOLTAGE_ADDR), temp);
    temp = getVoltageTolerance();
    EEPROM.put(static_cast<int>(Address::VOLTAGE_TOLERANCE_ADDR), temp);
    temp = getTravelSpeed();
    EEPROM.put(static_cast<int>(Address::TRAVEL_SPEED_ADDR), temp);
    temp = getDelayInitTravel();
    EEPROM.put(static_cast<int>(Address::DELAY_INIT_TRAVEL_ADDR), temp);
}

template <typename T>
void MemoryController<T>::updateWeldingParametersFromEeprom() {
    T temp = 0;
    EEPROM.get(static_cast<int>(Address::ARC_CONTROLLER_GAIN_ADDR), temp);
    setArcControllerGain(temp);
    EEPROM.get(static_cast<int>(Address::SHORT_CIRCUIT_VOLTAGE_ADDR), temp);
    setShortCircuitVoltage(temp);
    EEPROM.get(static_cast<int>(Address::FEED_SPEED_ADDR), temp);
    setFeedSpeed(temp);
    EEPROM.get(static_cast<int>(Address::WELDING_VOLTAGE_ADDR), temp);
    setWeldingVoltage(temp);
    EEPROM.get(static_cast<int>(Address::VOLTAGE_TOLERANCE_ADDR), temp);
    setVoltageTolerance(temp);
    EEPROM.get(static_cast<int>(Address::TRAVEL_SPEED_ADDR), temp);
    setTravelSpeed(temp);
    EEPROM.get(static_cast<int>(Address::DELAY_INIT_TRAVEL_ADDR), temp);
    setDelayInitTravel(temp);
}

template <typename T>
bool MemoryController<T>::verifyParameterValue(const T value)
{
    return value != 0;
}
