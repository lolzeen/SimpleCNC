#include "main.hpp"
// TODO: extinguir arco antes do soltar o endswitch (colocar o endswitch mais para frente e acionar o fechamento do arco antes de releaseEndSwitch)
// TODO: atualizar display quando enswitch for acionado

MemoryController MEMORY_CONTROLLER;
MotorController eixo_x(driver_x_pins, driver_params, EIXO_X_ID, EIXO_X_DIS);
MotorController eixo_z(driver_z_pins, driver_params, EIXO_Z_ID, EIXO_Z_DIS);
DisplayController display(MEMORY_CONTROLLER, input_pins);

int16_t enc_count = 0;

ISR(TIMER5_COMPA_vect)
{
    eixo_z.toggleCorrectHeight();
}
ISR(TIMER5_COMPB_vect)
{
    display.monitorUserInput();
}
void setup ()
{
    Serial.begin(9600);
    MEMORY_CONTROLLER.updateWeldingParametersFromEeprom();
    Serial.print("Memoria:\n");
    Serial.println(MEMORY_CONTROLLER.toString());
    // Serial.println(MemoryController<int>::)
}
void loop ()
{
    MotorController::run(eixo_x, eixo_z);
    
    if (!display.navigateThroughParallelWindows()) {
        enc_count = 0; // IMPROVEMENT: create a static variable in oder to merge enc_count and display.enc_count
        display.setEncoderCount(0); // IMPROVEMENT: create a static variable in oder to merge enc_count and display.enc_count
        switch (display.getCurrentWindow())
        {
            case EDIT_POS_HORIZONTAL:
                // IMPROVEMENT: all the code inside this case could be a fuction that recives an axis parameter
                eixo_x.setSpeed(0);
                display.displayPrint(EDIT_POS_HORIZONTAL, eixo_x.getSpeed());
                MotorController::setRunningProcess(MANUAL_POSITIONING);
                while (display.getAdjustMenu())
                {
                    eixo_x.run();
                    if (enc_count != display.getEncoderCount()) // IMPROVEMENT: after merging enc_count this condition must be redefined
                    {
                        if (display.getEncoderMovementDirection() == 1) eixo_x.setSpeed(eixo_x.getSpeed()+10);
                        else eixo_x.setSpeed(eixo_x.getSpeed()-10);
                        eixo_x.setProcess();
                        if (eixo_x.getSpeed() == 0) eixo_x.setEnableMovement(LOW);
                        else
                        {
                            if (eixo_x.getSpeed() > 0) eixo_x.setMovementDirection(FORWARD);
                            else eixo_x.setMovementDirection(BACKWARD); 
                            eixo_x.setEnableMovement(HIGH);
                        }
                        display.displayPrint(EDIT_POS_HORIZONTAL, eixo_x.getSpeed());
                        enc_count = display.getEncoderCount(); // IMPROVEMENT: after merging enc_count this line must be deleted
                    }
                    display.monitorUserInput();
                }
                eixo_x.setEnableMovement(LOW);
                break;
            case EDIT_POS_VERTICAL:
                // IMPROVEMENT: all the code inside this case could be a fuction that recives an axis parameter
                eixo_z.setSpeed(0);
                display.displayPrint(EDIT_POS_VERTICAL, eixo_z.getSpeed());
                MotorController::setRunningProcess(MANUAL_POSITIONING);
                while (display.getAdjustMenu())
                {
                    eixo_z.run();
                    if (enc_count != display.getEncoderCount()) // IMPROVEMENT: after merging enc_count this condition must be redefined
                    {
                        if (display.getEncoderMovementDirection() == 1) eixo_z.setSpeed(eixo_z.getSpeed()+10);
                        else eixo_z.setSpeed(eixo_z.getSpeed()-10);
                        eixo_z.setProcess();
                        if (eixo_z.getSpeed() == 0) eixo_z.setEnableMovement(LOW);
                        else
                        {
                            if (eixo_z.getSpeed() > 0) eixo_z.setMovementDirection(FORWARD);
                            else eixo_z.setMovementDirection(BACKWARD); 
                            eixo_z.setEnableMovement(HIGH);
                        }
                        display.displayPrint(EDIT_POS_VERTICAL, eixo_z.getSpeed());
                        enc_count = display.getEncoderCount(); // IMPROVEMENT: after merging enc_count this line must be deleted
                    }
                }
                eixo_z.setEnableMovement(LOW);
                break;
            default:
                while (display.getAdjustMenu())
                {
                    if (display.getEncoderCount() != enc_count)
                    {
                        switch (display.getCurrentWindow())
                        {
                            case EDIT_TRAVEL_SPEED:
                                MEMORY_CONTROLLER.setTravelSpeed(MEMORY_CONTROLLER.getTravelSpeed() + display.getEncoderMovementDirection()); // IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.displayPrint(EDIT_TRAVEL_SPEED, MEMORY_CONTROLLER.getTravelSpeed());
                                eixo_x.setSpeed(MEMORY_CONTROLLER.getTravelSpeed());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            case EDIT_FEED_SPEED:
                                MEMORY_CONTROLLER.setFeedSpeed(MEMORY_CONTROLLER.getFeedSpeed() + display.getEncoderMovementDirection()); // IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.displayPrint(EDIT_FEED_SPEED, MEMORY_CONTROLLER.getFeedSpeed());
                                eixo_z.setSpeed(MEMORY_CONTROLLER.getFeedSpeed());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            case EDIT_ARC_GAIN:
                                MEMORY_CONTROLLER.setArcControllerGain(MEMORY_CONTROLLER.getArcControllerGain() + display.getEncoderMovementDirection());// IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.displayPrint(EDIT_ARC_GAIN, MEMORY_CONTROLLER.getArcControllerGain());
                                eixo_z.setarcControllerGain(MEMORY_CONTROLLER.getArcControllerGain());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            case EDIT_SHORT_CIRCUIT_VOLTAGE:
                                MEMORY_CONTROLLER.setShortCircuitVoltage(MEMORY_CONTROLLER.getShortCircuitVoltage() + display.getEncoderMovementDirection()); // IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.updateDisplay(EDIT_SHORT_CIRCUIT_VOLTAGE, MEMORY_CONTROLLER.getShortCircuitVoltage());
                                eixo_z.setShortCircuitVoltage(MEMORY_CONTROLLER.getShortCircuitVoltage());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            case EDIT_WELDING_VOLTAGE:
                                MEMORY_CONTROLLER.setWeldingVoltage(MEMORY_CONTROLLER.getWeldingVoltage() + display.getEncoderMovementDirection()); // IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.updateDisplay(EDIT_WELDING_VOLTAGE, MEMORY_CONTROLLER.getWeldingVoltage()); // IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                eixo_z.setWeldingVoltage(MEMORY_CONTROLLER.getWeldingVoltage());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            case EDIT_VOLTAGE_TOLERANCE:
                                MEMORY_CONTROLLER.setVoltageTolerance(MEMORY_CONTROLLER.getVoltageTolerance() + display.getEncoderMovementDirection()); // IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.updateDisplay(EDIT_VOLTAGE_TOLERANCE, MEMORY_CONTROLLER.getVoltageTolerance()); // IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                eixo_z.setVoltageTolerance(MEMORY_CONTROLLER.getVoltageTolerance());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            case EDIT_DELAY_INIT_TRAVEL:
                                MEMORY_CONTROLLER.setDelayInitTravel(MEMORY_CONTROLLER.getDelayInitTravel() + display.getEncoderMovementDirection()); // IMPROVEMENT: this could be a method from memoria that recieves a int8_t
                                display.updateDisplay(EDIT_DELAY_INIT_TRAVEL, MEMORY_CONTROLLER.getDelayInitTravel()); // IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                eixo_z.setDelayInitTravel(MEMORY_CONTROLLER.getDelayInitTravel());// IMPROVEMENT: EIXO_X should have a access to memoria so the data is not saved two times
                                break;
                            default:
                                break;
                        }
                        Serial.print("Memoria:\n\n");
                        Serial.println(MEMORY_CONTROLLER.toString());
                        enc_count = display.getEncoderCount();
                        display.monitorUserInput();
                    }
                }
        }
        enc_count = 0;
        display.setEncoderCount(0);
    }
    if (display.getInitProcess())
    {
        display.executeCountdownWindow();
        display.executeProcessWindow();
        eixo_z.startProcess();
        eixo_x.startProcess();
        display.setInitProcess(false);
        MotorController::setRunningProcess(WELD);
    }
    if (display.getReturnHome())
    {
        display.executeProcessWindow();
        eixo_x.returnHome();
        delay(200);
        eixo_z.returnHome();
        display.setReturnHome(false);
        MotorController::setRunningProcess(RETURN);
    }
    if (!eixo_x.getEnableMovement() && !eixo_z.getEnableMovement() && MotorController::getRunningProcess() != IDDLE)
    {
        MotorController::setRunningProcess(IDDLE);
        display.updateDisplay();
    }
}