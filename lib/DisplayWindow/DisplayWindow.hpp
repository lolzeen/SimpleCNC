#ifndef DISPLAYWINDOW_H
#define DISPLAYWINDOW_H

#include <Arduino.h>

enum PtrId {NEXT_PTR=1, PREV_PTR=2, INNE_PTR=3, OUTT_PTR=4};
typedef DisplayWindow* dispWindPtr;

class DisplayWindow
{
private:
    dispWindPtr next = nullptr;
    dispWindPtr previous = nullptr;
    dispWindPtr inner = nullptr;
    dispWindPtr outter = nullptr;
    String content = "";
    const char MES_PRESS_OR_TURN[16] = {'P','r','e','s','s','.',251,' ',124,' ','G','i','r','e',60,62};
    bool perform_action = false;

public:
    DisplayWindow();
    DisplayWindow(dispWindPtr& ptr, uint8_t ptr_id);
    DisplayWindow(dispWindPtr& ptr1, uint8_t ptr_id1, dispWindPtr& ptr2, uint8_t ptr_id2);
    DisplayWindow(dispWindPtr& ptr1, uint8_t ptr_id1, dispWindPtr& ptr2, uint8_t ptr_id2, dispWindPtr& ptr3, uint8_t ptr_id3);
    DisplayWindow(dispWindPtr& ptr1, dispWindPtr& ptr2, dispWindPtr& ptr3, dispWindPtr& ptr4);
    ~DisplayWindow();

    String getContent() const {return content;}; 
    bool getAction() const {return perform_action;};
    
    void setContent(String cont) {content=cont;};
    void setAction(bool act) {perform_action=act;};

    bool hasNextWind() {return next != nullptr;};
    bool hasPrevWind() {return previous != nullptr;};
    bool hasInWind() {return inner != nullptr;};
    bool hasOutWind() {return outter != nullptr;};
};

#endif // DIPLAYWINDOW_H