#include "MotorController.hpp"
uint8_t MotorController::runningProcess = 0;
MotorController::MotorController()
{
    // Intentionally Empty;
}
MotorController::MotorController(const DriverPins &pins)
{
    io_setup(pins);
    pulsesPerRevolution =  20000;
    setEnableMovement(LOW);
}
MotorController::MotorController(const DriverPins &pins, const uint16_t &driver_pul_rev, const uint8_t &id, uint8_t dis)
{
    io_setup(pins);
    pulsesPerRevolution = driver_pul_rev;
    maxDistance = dis;
    _id = id;
}
MotorController::~MotorController()
{
    // Intentionally Empty;
    // IMPROVEMENT: write settings on memory before turning off
}
void MotorController::calcFreq()
{
    // FIXME
    if (speed < 0) movementDirection = BACKWARD;
    stepFrequency = 2*abs(speed)*(pulsesPerRevolution/0.008)/(60*100);
}
void MotorController::calcOcr()
{
    uint16_t newOcr = 8e6 / stepFrequency;
    if (newOcr <= 65535 && newOcr > 0) 
        ocr =  newOcr;
}
void MotorController::releaseEndSwitch()
{
    if (movementDirection == FORWARD)
    {
        setMovementDirection(BACKWARD);
    }
    else if (movementDirection == BACKWARD)
    {
        setMovementDirection(FORWARD);
    }
    setSpeed(100*maxDistance/MIN_TIME);
    setProcess();
    setEnableMovement(HIGH);
    delay(200);
    setEnableMovement(LOW);
}
void MotorController::closeArc()
{
    // TODO recuar o eixo_z 5 cm
    setMovementDirection(BACKWARD);
    setSpeed(100*maxDistance/MIN_TIME);
    setProcess();
    setEnableMovement(HIGH);
    delay(500);
    setEnableMovement(LOW);
}
void MotorController::correctHeight()
{
    if (int delta = readVoltage() - weldingVoltage)
    {
        setSpeed(abs(delta) * speed * arcControllerGain);
        setProcess();
        if (delta < 0) setMovementDirection(BACKWARD);
        else setMovementDirection(FORWARD);
        setEnableMovement(HIGH);
    }
    else setEnableMovement(LOW);
}
void MotorController::processEndSwitch(bool activate_releaseEndSwitch)
{
    if (activate_releaseEndSwitch)
    {
        if(_end_switch1.debounce())
        {
            // home
            if (movementDirection == BACKWARD)
            {
                setEnableMovement(LOW);
                releaseEndSwitch();
                set_pos(HOME);
            }
            // Serial.print("Id: ");
            // Serial.print(_id);
            // Serial.println(" endswitch: HOME");
        }
        else if(_end_switch2.debounce())
        {
            // finish
            if (_id == 4) closeArc();
            else if (movementDirection == FORWARD)
            {
                setEnableMovement(LOW);
                releaseEndSwitch();
                set_pos(FINISH);
                setIsArcOpen(false);
            }
            // Serial.print("Id: ");
            // Serial.print(_id);
            // Serial.println(" endswitch: FINISH");
        }
    }
}
void MotorController::io_setup(const DriverPins &pins)
{
    _driver_pins = pins;
    _end_switch1.begin(_driver_pins._ES1, true);
    _end_switch2.begin(_driver_pins._ES2, true);
    pinMode(_driver_pins._DIR, OUTPUT);
    pinMode(_driver_pins._EN, OUTPUT);
    setEnableMovement(LOW);
    pinMode(_driver_pins._STEP, OUTPUT);
    digitalWrite(_driver_pins._STEP, LOW);
    pinMode(_driver_pins._OUT, INPUT);

}
double MotorController::readVoltage()
{
    return analogRead(A0) * INP_VOLTAGE_TO_REAL_VOLTAGE_MULTIPLIER;
}
void MotorController::returnHome()
{
    if (!enableMovement)
    {
        
        setMaxDistance(maxDistance);
        setMovementDirection(BACKWARD);
        setProcessDuration(MIN_TIME*2); // previous setting MIN_TIME*8
        setSpeed(100*maxDistance/MIN_TIME);
        setProcess();
        setEnableMovement(HIGH);
    }
    // tone(_driver_pins._STEP, 15000);  
}
void MotorController::run()
{
    processEndSwitch(true);
    verifyDistance();
}
void MotorController::run(bool activate_correct_height)
{
    run();
    if (activate_correct_height)
    {
        correctHeight();
    }
}
void MotorController::run(MotorController &xAxis, MotorController &zAxis)
{
    switch (runningProcess)
    {
    case WELD:
        xAxis.processEndSwitch(true);
        zAxis.processEndSwitch(true);
        if (xAxis.getIsArcOpen())
        {
            zAxis.closeArc();
        }
        else if (zAxis.isHeightControllerActive)
        {
            zAxis.correctHeight();
            zAxis.toggleCorrectHeight();
        }
        break;
    case RETURN:
        xAxis.processEndSwitch(true);
        zAxis.processEndSwitch(true);
        break;
    case MANUAL_POSITIONING:
        xAxis.processEndSwitch(true);
        zAxis.processEndSwitch(true);
        break;
    default:
        break;
    }
    if (!xAxis.getEnableMovement() && !zAxis.getEnableMovement())
    {
        MotorController::setRunningProcess(IDDLE);
    }
}
void MotorController::setMovementDirection(const uint8_t state)
{
    movementDirection = state;
    digitalWrite(_driver_pins._DIR, movementDirection);
}
void MotorController::setEnableMovement(const uint8_t  state)
{
    enableMovement = state;
    digitalWrite(_driver_pins._EN, enableMovement);
}
void MotorController::setProcess()
{
    setDistance(0);
    calcFreq();
    calcOcr();
    setTimers();
}
void MotorController::setTimers()
{
    noInterrupts();
    switch (_id)
    {
    case 4:
        TCCR4A = _BV(COM4A0) | _BV(COM4B0) | _BV(COM4C0) | _BV(WGM40); // 01010101
        TCCR4B = _BV(WGM43) | _BV(CS40); //00010001
        OCR4A = ocr;
        break;

    case 3:    
        TCCR3A =  _BV(COM3A0) | _BV(COM3B0) | _BV(COM3C0) | _BV(WGM30); // 01010101
        TCCR3B = _BV(WGM33) | _BV(CS30); //00010001
        OCR3A = ocr;
        break;
    default:
        break;
    }
    interrupts();
}
void MotorController::setRunningProcess(uint8_t process)
{
    runningProcess = process;
}
void MotorController::startProcess()
{
    if (!enableMovement)
    {
        setMaxDistance(maxDistance);
        setProcess();
        setMovementDirection(FORWARD);
        if (_id == 3) delay(delayInitTravel);
        setEnableMovement(HIGH);
    }
}
void MotorController::startProcess(uint8_t mode)
{
    startProcess();
}
void MotorController::stopTimers()
{
    noInterrupts();
    // TCCRA = _BV(COMA) | _BV(COMB) | _BV(COMC) | _BV(WGM0); // 01010101
    // TCCRB = _BV(WGM3) | _BV(CS0);
    // OCR = _ocr;
    switch (_id)
    {
    case 4:
        TCCR4A = _BV(COM4A0) | _BV(COM4B0) | _BV(COM4C0) | _BV(WGM40); // 01010101
        TCCR4B = _BV(WGM43); //00010000
        break;
    
    case 3:
        TCCR3A =  _BV(COM3A0) | _BV(COM3B0) | _BV(COM3C0) | _BV(WGM30); // 01010101
        TCCR3B = _BV(WGM33); //00010000
        break;

    default:
        break;
    }
    interrupts();
}
void MotorController::verifyDistance()
{
    // TODO:missing implementation
    // how
    // count pulses / get tach signal from driver
}
