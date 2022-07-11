#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button
{
  private:
    uint8_t _btn_pin;
    uint16_t _state;
  public:
    void begin(uint8_t pin);
    bool debounce();
};
#endif // BUTTON_H