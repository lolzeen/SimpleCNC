#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

#include "DisplayWindow.hpp"

class DisplayManager
{
private:
    DisplayWindow windows[30] = {};
    dispWindPtr current_window;

public:
    DisplayManager(/* args */);
    ~DisplayManager();

    dispWindPtr getCurWind() const {return current_window;};

    void setCurWind(dispWindPtr& ptr) {current_window=ptr;};

    void goNext();
    void goPrev();
    void goIn();
    void goOut();
};

#endif // DISPLAYMANAGER_H