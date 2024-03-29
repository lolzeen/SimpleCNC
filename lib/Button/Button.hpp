#ifndef BUTTON_H
#define BUTTON_H

#include "Arduino.h"

class Button
{
  private:
    uint8_t _btn_pin;
    uint16_t _state;
    static unsigned long _last_debounce;
  public:
    void begin(uint8_t pin);
    void begin(uint8_t pin, bool pull_up);
    bool debounce();
    bool debounce_l();
    void set_last_debounce(unsigned long last_db);
};
#endif // BUTTON_H