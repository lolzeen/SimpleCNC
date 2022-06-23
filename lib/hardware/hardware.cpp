#include "hardware.hpp"

namespace HardwareLeo
{
    // Controller::Controller(int pin_x_r, int pin_x_l, int pin_z_u, int pin_z_d) : es_pin_x_r(pin_x_r), es_pin_x_l(pin_x_l), es_pin_z_u(pin_z_u), es_pin_z_d(pin_z_d);

    Controller::Controller()
    {
        // Intentionally Empty;
    }

    Controller::~Controller()
    {
        // Intentionally Empty;
    }

    void Controller::setEsPins(int pin_1, int pin_2)
    {
        Controller::es_inp.pin_1 = pin_1;
        Controller::es_inp.pin_2 = pin_2;
        pinMode(Controller::es_inp.pin_1, INPUT_PULLUP);
        pinMode(Controller::es_inp.pin_2, INPUT_PULLUP);
        // FIXME: attachInterrupt(digitalPinToInterrupt(Controller::es_inp.pin_1), Controller::es_1, FALLING);
        // FIXME: attachInterrupt(digitalPinToInterrupt(Controller::es_inp.pin_2), Controller::es_2, FALLING);
    }
    //

    void Controller::es_1()
    {
        digitalWrite(Controller::es_inp.pin_1, LOW);
    }
    void Controller::es_2()
    {
        digitalWrite(Controller::es_inp.pin_2, LOW);
    }

    void Controller::setEsPins(int pin_1, int pin_2)
    {
        Controller::es_inp.pin_1 = pin_1;
        Controller::es_inp.pin_2 = pin_2;
    }

    void Controller::setDriPins(int pin_dir, int pin_enable, int pin_step, int pin_output)
    {
        Controller::dri_io.dir = pin_dir;
        Controller::dri_io.enable = pin_enable;
        Controller::dri_io.step = pin_step;
        Controller::dri_io.output = pin_output;
        pinMode(Controller::dri_io.dir, OUTPUT);
        pinMode(Controller::dri_io.enable, OUTPUT);
        pinMode(Controller::dri_io.step, OUTPUT);
        pinMode(Controller::dri_io.output, INPUT);
    }


} //HardwareLeo