#include "MemoryController.hpp"

MemoryController::MemoryController() {
    updateWeldingParametersFromEeprom();
}

MemoryController::~MemoryController() {
    // intentionally empty
}

int16_t MemoryController::getValueFromAddress(int16_t memoryAddres) {
    int16_t val = 0;
    EEPROM.get(memoryAddres, val);
    return val;
}

String MemoryController::toString() {
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

void MemoryController::updateEepromFromWeldingParameters() {
    Serial.print("WELDING_GAIN: ");
    Serial.println(weldingParameters.arcControllerGain.value);
    EEPROM.put(ARC_CONTROLLER_GAIN_ADDR, weldingParameters.arcControllerGain.value);
    EEPROM.put(SHORT_CIRCUIT_VOLTAGE_ADDR, weldingParameters.shortCircuitVoltage.value);
    EEPROM.put(FEED_SPEED_ADDR, weldingParameters.feedSpeed.value);
    EEPROM.put(WELDING_VOLTAGE_ADDR, weldingParameters.weldingVoltage.value);
    EEPROM.put(VOLTAGE_TOLERANCE_ADDR, weldingParameters.voltageTolerance.value);
    EEPROM.put(TRAVEL_SPEED_ADDR, weldingParameters.travelSpeed.value);
    EEPROM.put(DELAY_INIT_TRAVEL_ADDR, weldingParameters.delayInitTravel.value);
}

void MemoryController::updateWeldingParametersFromEeprom() {
    int16_t var;
    EEPROM.get(ARC_CONTROLLER_GAIN_ADDR, var);
    setArcControllerGain(var);
    EEPROM.get(SHORT_CIRCUIT_VOLTAGE_ADDR, weldingParameters.shortCircuitVoltage.value);
    EEPROM.get(FEED_SPEED_ADDR, weldingParameters.feedSpeed.value);
    EEPROM.get(WELDING_VOLTAGE_ADDR, weldingParameters.weldingVoltage.value);
    EEPROM.get(VOLTAGE_TOLERANCE_ADDR, weldingParameters.voltageTolerance.value);
    EEPROM.get(TRAVEL_SPEED_ADDR, weldingParameters.travelSpeed.value);
    EEPROM.get(DELAY_INIT_TRAVEL_ADDR, weldingParameters.delayInitTravel.value);
}

bool MemoryController::verifyParameterValue(const int value)
{
    if (value != 0) return true;
    return false;
}