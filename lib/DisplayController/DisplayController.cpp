#include "DisplayController.hpp"


DisplayController::DisplayController()
{
    initializeDisplay();
}
void DisplayController::constructor() {
    noInterrupts();
    TCCR5A = 0; // 00000000
    TCCR5B = _BV(CS51) | _BV(CS50); // normal mode, prescaler = 64
    OCR5A = 65535;
    OCR5B = 32768;
    TIMSK5 = _BV(OCIE5A) | _BV(OCIE5B); // Output compare A and B match interrupt enable
    interrupts();
    _button.begin(_input_pins.button, true);
    _encoder.begin(_input_pins.encoder_a, _input_pins.encoder_b);
    initializeDisplay();
}
DisplayController::DisplayController(const InputPins& in_pins) : _input_pins(in_pins)
{
    constructor();
}
DisplayController::DisplayController(MemoryController memoryController, const InputPins& in_pins): _input_pins(in_pins),  MEMORY_CONTROLLER(memoryController) {
    constructor();
}
DisplayController::~DisplayController()
{
    // intentionally empty
}

void DisplayController::displayPrint(int content_descriptor, String content)
{
    _lcd.setCursor(0,0);
    _lcd.print("               ");
    switch (content_descriptor)
    {
    case EDIT_POS_HORIZONTAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_POS_VERTICAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_TRAVEL_SPEED:
        _lcd.setCursor(0,0);
        _lcd.print(content+"cm/min");
        break;
    case EDIT_FEED_SPEED:
        _lcd.setCursor(0,0);
        _lcd.print(content+"cm/min");
        break;
    case EDIT_VOLTAGE_TOLERANCE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;
    case EDIT_ARC_GAIN:
        _lcd.setCursor(0,0);
        _lcd.print(content);
        break;
    case EDIT_SHORT_CIRCUIT_VOLTAGE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;        
    default:
        break;
    }
}
void DisplayController::displayPrint(int menuWindowSpecifier, int content)
{
    displayPrint(menuWindowSpecifier, String(content));
}
void DisplayController::displayPrint(const char* upper, const char* lower)
{
    _lcd.clear();
    _lcd.print(upper);
    _lcd.setCursor(0, 1);
    _lcd.print(lower);
}
void DisplayController::executeCountdownWindow()
{
    for (int i = 5; i > 0 ; i--)
    {
        _lcd.clear();
        _lcd.setCursor(0, 0);
        _lcd.print("Iniciando em ");
        _lcd.print(i);
        _lcd.print("s");
        delay(1000);
    }
}
void DisplayController::executeProcessWindow()
{
    _lcd.clear();
    _lcd.setCursor(0,0);
    _lcd.print("Executando");
    _lcd.setCursor(1,0);
    _lcd.print("Processo");
}
void DisplayController::initializeDisplay()
{
    _lcd.begin(16,2);
    _lcd.clear();
    setCurrentWindow(0);
    updateDisplay();
}
void DisplayController::liveEditPosition(MotorController &axis) {
    axis.setSpeed(0);
    display.displayPrint(EDIT_POS_HORIZONTAL, axis.getSpeed());
    MotorController::setRunningProcess(MANUAL_POSITIONING);
    while (display.getAdjustMenu())
    {
        axis.run();
        if (enc_count != display.getEncoderCount()) // IMPROVEMENT: after merging enc_count this condition must be redefined
        {
            if (display.getEncoderMovementDirection() == 1) axis.setSpeed(axis.getSpeed()+10);
            else axis.setSpeed(axis.getSpeed()-10);
            axis.setProcess();
            if (axis.getSpeed() == 0) axis.setEnableMovement(LOW);
            else
            {
                if (axis.getSpeed() > 0) axis.setMovementDirection(FORWARD);
                else axis.setMovementDirection(BACKWARD); 
                axis.setEnableMovement(HIGH);
            }
            display.displayPrint(EDIT_POS_HORIZONTAL, axis.getSpeed());
            enc_count = display.getEncoderCount(); // IMPROVEMENT: after merging enc_count this line must be deleted
        }
        display.monitorUserInput();
    }
    axis.setEnableMovement(LOW);
}
void DisplayController::moveToNextWindow()
{
    if (validateWindow(currentWindow+1))
    {
        currentWindow++;
        updateDisplay();
    }
}
void DisplayController::moveToInnerWindow()
{
    if (validateWindow(currentWindow*10))
    {
        currentWindow *= 10;
        updateDisplay();
    }
}
void DisplayController::moveToOuterWindow()
{
    if (validateWindow(currentWindow/10))
    {
        currentWindow /= 10;
        updateDisplay();
    }
}
void DisplayController::moveToPreviousWindow()
{
    if (validateWindow(currentWindow-1))
    {
        currentWindow--;
        updateDisplay();
    }
}
bool DisplayController::navigateThroughParallelWindows() {
    if (!display.getAdjustMenu())
    {
        if (display.getEncoderMovementDirection() == 1) display.moveToNextWindow();
        else if (display.getEncoderMovementDirection() == -1) display.moveToPreviousWindow();
        return true;
    }
    return false;
}
void DisplayController::processButtonInput()
{
    if (_button.debounce())
    {
        switch (currentWindow)
        {
            case 0:
                if (!getInitProcess()) setInitProcess(true);
                else setInitProcess(false);
                updateDisplay();
                break;
            case 1:
                if (!getReturnHome()) setReturnHome(true);
                else setReturnHome(false);
                updateDisplay();
                break;
            case 2: case 3: case 30: case 31:
                currentWindow *= 10;
                updateDisplay();
                break;
            case 20: case 21:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow,"");
                }
                break;
            case EDIT_SHORT_CIRCUIT_VOLTAGE/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getShortCircuitVoltage());
                }
                break;
            case EDIT_WELDING_VOLTAGE/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getWeldingVoltage());
                }
                break;
            case EDIT_VOLTAGE_TOLERANCE/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getVoltageTolerance());
                }
                break;
            case EDIT_ARC_GAIN/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getArcControllerGain());
                }
                break;
            case EDIT_DELAY_INIT_TRAVEL/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getDelayInitTravel());
                }
                break;
            case EDIT_TRAVEL_SPEED/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getTravelSpeed());
                }
                break;
            case EDIT_FEED_SPEED/10:
                if (!getAdjustMenu())
                {
                    currentWindow *= 10;
                    setAdjustMenu(true);
                    updateDisplay(currentWindow, MEMORY_CONTROLLER.getFeedSpeed());
                }
                break;
            case 22: case 305: case 312:
                currentWindow /= 10;
                updateDisplay();
                break;
            case SAVE_SETTINGS:
                MEMORY_CONTROLLER.updateEepromFromWeldingParameters();
                // EEPROM.put(MEMORY_ADDRESS.SHORT_CIRCUIT_VOLTAGE_ADDR, MEMORY_CONTROLLER.getShortCircuitVoltage());
                break;
            default:
                if (currentWindow == 200 ||
                    currentWindow == 210 ||
                    currentWindow >= 3000)
                {
                    currentWindow /= 10;
                    setAdjustMenu(false);
                    updateDisplay();
                }
                else
                {
                    currentWindow = 0;
                    updateDisplay();
                }
                break;
        }
    }
    delayMicroseconds(500);
}
void DisplayController::processEncoderInput()
{
    if (abs(encoderCount)>120) encoderCount = 0;
    encoderMovementDirection =_encoder.process();
    encoderCount += encoderMovementDirection;
}
void DisplayController::updateDisplay()
{
    switch (getCurrentWindow())
    {
        case 0:
            displayPrint(MES_INIT, MES_PRESS_CONFIRM);
            break;
        case 1:
            displayPrint(MES_RETU, MES_PRESS_CONFIRM);
            break;
        case 2:
            displayPrint(MES_POS, MES_PRESS_EDIT);
            break;
        case 20:
            displayPrint(MES_POS_HORI, MES_PRESS_EDIT);
            break;
        case 21:
            displayPrint(MES_POS_VERT, MES_PRESS_EDIT);
            break;
        case 3:
            displayPrint(MES_CONFIG, MES_PRESS_EDIT);
            break;
        case 30:
            displayPrint(MES_ARC, MES_PRESS_EDIT);
            break;
        case 300:
            displayPrint(MES_ARCshortCircuitVoltage, MES_PRESS_EDIT);
            break;
        case 301:
            displayPrint(MES_ARC_VOLTAGE, MES_PRESS_EDIT);
            break;
        case 302:
            displayPrint(MES_ARC_TOL, MES_PRESS_EDIT);
            break;
        case 303:
            displayPrint(MES_ARC_GAIN, MES_PRESS_EDIT);
            break;
        case 304:
            displayPrint(MES_DELAY_INIT_TRAVEL, MES_PRESS_EDIT);
            break;
        case 31:
            displayPrint(MES_SPEED, MES_PRESS_EDIT);
            break;
        case 310:
            displayPrint(MES_TRAVEL_SPEED, MES_PRESS_EDIT);
            break;
        case 311:
            displayPrint(MES_FEED_SPEED, MES_PRESS_EDIT);
            break;
        case 32:
            displayPrint(MES_SAVE, MES_PRESS_CONFIRM);
            break;
        case 22: case 33: case 313: case 306:
            displayPrint(MES_RETURN_MAIN_MENU, MES_PRESS_CONFIRM);
            break;
        case 305: case 312:
            displayPrint(MES_RETURN_PREVIOUS_MENU, MES_PRESS_CONFIRM);
            break;
        default:
            displayPrint("Erro!", "Reinicie!");
            break;
    }
}
void DisplayController::updateDisplay(int menuWindowSpecifier, String content)
{
    _lcd.clear();
    switch (menuWindowSpecifier)
    {
    case EDIT_POS_HORIZONTAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_POS_VERTICAL:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_TRAVEL_SPEED:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_FEED_SPEED:
        _lcd.setCursor(0,0);
        _lcd.print("Vel: "+content+"cm/min");
        break;
    case EDIT_VOLTAGE_TOLERANCE:
        _lcd.setCursor(0,0);
        _lcd.print(content+"V");
        break;
    case EDIT_ARC_GAIN:
        _lcd.setCursor(0,0);
        _lcd.print("Ganho: "+content);
        break;
    case EDIT_SHORT_CIRCUIT_VOLTAGE:
        _lcd.setCursor(0,0);
        _lcd.print(content+" V");
        break;
    case EDIT_DELAY_INIT_TRAVEL:
        _lcd.setCursor(0,0);
        _lcd.print("Tempo: "+content+" ms");
        break;
    case EDIT_WELDING_VOLTAGE:
        _lcd.setCursor(0,0);
        _lcd.print(content+" V");
        break;
    default:
        break;
    }
    _lcd.setCursor(0,1);
    _lcd.print(MES_PRESS_CONFIRM);
    // Serial.println("Current. Window: "+String(currentWindow));
}
void DisplayController::updateDisplay(int menuWindowSpecifier,uint8_t content)
{
    updateDisplay(menuWindowSpecifier, String(content));
}
bool DisplayController::validateWindow(int id)
{
    for (int valid_id : valid_window_ids)
    {
        if (valid_id == id)
        {
            // Serial.println("Valid Window");
            return true;
        }
    }
    // Serial.println("Window id: "+String(id));
    // Serial.println("Invalid Window");
    return false;
}
